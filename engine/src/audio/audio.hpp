#ifndef _AUDIO_HPP_
#define _AUDIO_HPP_

#include <SDL3/SDL_audio.h>
#include <string>
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"
#include "../general/general.hpp"

namespace secret {
namespace audio {

  class AudioSys {
  public:

    static bool Init();
  
    static MIX_Track* createAudioTrack();
    static bool playTrack(MIX_Track* track);
    static bool resumeTrack(MIX_Track* track);
    static bool pauseTrack(MIX_Track* track);
    static bool restartTrack(MIX_Track* track);

    static bool loadTrackAudio(MIX_Track* track, std::string audioFileLocation);


  private:
    static MIX_Mixer* mixer; 
  };

}
}

#endif



