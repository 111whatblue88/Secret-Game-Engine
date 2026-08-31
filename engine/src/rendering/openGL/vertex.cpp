#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "vertex.hpp"

#include "../../../vendored/glew/include/GL/glew.h"
#include <filesystem>
#include <format>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <unordered_map>

using namespace secret;
using namespace rend;

VertexBuffer::VertexBuffer(const void* data, const unsigned int dataSize) {
  GLCheck(glGenBuffers(1, &ID));
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
  GLCheck(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer() {

}
void VertexBuffer::FillData(const void* data, const unsigned int dataSize) {
  GLCheck(glGenBuffers(1, &ID));
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
  GLCheck(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));
}

void VertexBuffer::VertexBuffer::Bind() const {
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
}
void VertexBuffer::VertexBuffer::Unbind() const {
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

IndexBuffer::IndexBuffer(const void* data, const unsigned int count) {
  this->count=count;
  GLCheck(glGenBuffers(1, &ID));
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
  GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer() {
  count=0;
}

void IndexBuffer::FillData(const void* data, const unsigned int count) {
  this->count=count;
  GLCheck(glGenBuffers(1, &ID));
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
  GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const {
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}
void IndexBuffer::Unbind() const {
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const {
  return count;
}

VertexBufferAttribute::VertexBufferAttribute(unsigned int count, unsigned int type, bool normalized){
  this->count=count;
  this->type=type;
  this->normalized=normalized;
}

unsigned int VertexBufferAttribute::getSizeOfType(unsigned int type) {
  switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_INT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    default:
      return 4;
  }
}

VertexArray::VertexArray() {
  if (core::Engine::options.renderingAPI == core::RenderingAPIs::openGL) {
    GLCheck(glGenVertexArrays(1, &ID));
    GLCheck(glBindVertexArray(ID));
  }
}

void VertexArray::Bind() const {
  GLCheck(glBindVertexArray(ID));
}
void VertexArray::Unbind() const {
  GLCheck(glBindVertexArray(0));
}

void VertexArray::AddLayout(const VertexBuffer& vb, const VertexBufferLayout& layout) {

  Bind();
  vb.Bind();
  auto attributes = layout.getAttributes();
  unsigned int offset = 0;
 
  for (unsigned int i = 0; i < attributes.size(); i++) {
    const auto attribute = attributes[i];
    GLCheck(glEnableVertexAttribArray(i));
    if (attribute.normalized == GL_TRUE) {
      GLCheck(glVertexAttribPointer(i, attribute.count, attribute.type, 
      GL_TRUE, layout.getStride(), (const void*)offset));
    } else {
      GLCheck(glVertexAttribPointer(i, attribute.count, attribute.type, 
      GL_FALSE, layout.getStride(), (const void*)offset));
    }
    
    offset+=attribute.count*attribute.getSizeOfType(attribute.type);

  }
}

void VertexBufferLayout::Push(unsigned int count, unsigned int type, bool normalized) {
  switch (type) {
    case GL_FLOAT: {
      attributes.push_back(VertexBufferAttribute(count, GL_FLOAT, GL_FALSE));
      stride+=count*sizeof(float);
      break;
    }
    case GL_INT: {
      attributes.push_back(VertexBufferAttribute(count, GL_INT, GL_FALSE));
      stride+=count*sizeof(int);
      break;
    }
    case GL_UNSIGNED_INT: {
      attributes.push_back(VertexBufferAttribute(count, GL_UNSIGNED_INT, GL_FALSE));
      stride+=count*sizeof(unsigned int);
      break;
    }
  }
}

VertexBufferLayout::VertexBufferLayout() {
  attributes = {};
  stride = 0;
}
