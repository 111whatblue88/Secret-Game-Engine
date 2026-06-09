
#include "audio.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../general/general.hpp"
#include "../HUGE.hpp"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>

using namespace huge;
using namespace audio;

AudioSys::audioStream::audioStream() {
  this->audioDataLen = 0;
  this->audioData = 0;
  this->stream = {};
}
AudioSys::audioStream::~audioStream() {
  SDL_DestroyAudioStream(this->stream);
}

bool AudioSys::Init() {
  if (!SDL_WasInit(SDL_INIT_AUDIO)) {
    if (!SDL_Init(SDL_INIT_AUDIO)) {
      return false;
    } 
  }
  return true;
}

AudioSys::audioStream* AudioSys::audioStreamFromWAV(std::string WAVLocation) {
  
  AudioSys::audioStream* stream = new audioStream();

  SDL_AudioSpec spec = {};

  if (!SDL_LoadWAV(WAVLocation.c_str(), &spec,&stream->audioData, &stream->audioDataLen)) {
    console::COutput::logCustom("AUDIO", "failed to load WAV file", console::COutput::MsgColor::red);
    console::COutput::logSDLError();
    return {};
  }
  stream->stream = SDL_CreateAudioStream(NULL, &spec);
  if (!stream->stream) {
    console::COutput::logCustom("AUDIO", "failed to create audio stream", console::COutput::MsgColor::red);
    console::COutput::logSDLError();
    return {};
  }
  return stream;

}
bool AudioSys::PauseAudio(SDL_AudioStream* stream) {

  if (!stream) {
    console::COutput::logCustom("AUDIO", "faulty audio stream given", console::COutput::MsgColor::red);
    console::COutput::logSDLError();
    return false;
  }

  if (SDL_PauseAudioStreamDevice(stream)) {
    return true;
  } else {
    return false;
    // TODO: log error
  }

}
bool AudioSys::PlayAudio(SDL_AudioStream* stream) {

  if (!stream) {
    console::COutput::logCustom("AUDIO", "faulty audio stream given", console::COutput::MsgColor::red);
    console::COutput::logSDLError();
    return false;
  }

  if (SDL_ResumeAudioStreamDevice(stream)) {
    return true;
  } else {
    return false;
    // TODO: log error
  }

}


