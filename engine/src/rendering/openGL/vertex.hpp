#pragma once
#include <vector>
#include <GL/glew.h>

namespace secret {
namespace rend {

class VertexBuffer {
  private:

  unsigned int ID;

  public:

  VertexBuffer(const void* data, const unsigned int dataSize);

  void Bind() const;
  void Unbind() const;

};

class IndexBuffer {
  private:

  unsigned int ID;

  unsigned int count;

  public:

  IndexBuffer();
  IndexBuffer(const void* data, const unsigned int count);

  unsigned int getCount() const;

  void fillData(const void* data, const unsigned int count);

  void Bind() const;
  void Unbind() const;

};

struct VertexBufferAttribute {
  unsigned int count; 
  unsigned int type;
  bool normalized;

  VertexBufferAttribute(unsigned int count, unsigned int type, bool normalized);

  static unsigned int getSizeOfType(unsigned int type);
};

class VertexBufferLayout {
private:
  std::vector<VertexBufferAttribute> attributes; // all of the attributes
  unsigned int stride;
public:

  VertexBufferLayout();

  void Push(unsigned int count, unsigned int type, bool normalized);

  inline auto getAttributes() const {return attributes;};
  inline unsigned int getStride() const {return stride;};

};

class VertexArray {
  private:
    unsigned int ID;
  public:

    VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);

};

}
}





