#ifndef _AUDIO_HPP_
#define _AUDIO_HPP_

#include <SDL3/SDL_audio.h>
#include <string>
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../general/general.hpp"

namespace huge {
namespace audio {

  class AudioSys {
  public:

    struct audioStream {
      audioStream();
      ~audioStream();
      SDL_AudioStream* stream; 
      Uint8* audioData;
      Uint32 audioDataLen;
    };

    static bool Init();

    static audioStream* audioStreamFromWAV(std::string WAVLocation);
    

    static bool PlayAudio(SDL_AudioStream* stream);
    static bool PauseAudio(SDL_AudioStream* stream);

  private:
  

  };

}
}

#endif



