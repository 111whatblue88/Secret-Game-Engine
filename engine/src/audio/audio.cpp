
#include "audio.hpp"
#include "../secret.hpp"

#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"

using namespace secret;
using namespace audio;

MIX_Mixer* AudioSys::mixer = NULL;

bool AudioSys::Init() {

  if (!MIX_Init()) {
    console::COutput::LogError("AUDIO", "failed to start SDL_mixer");
    console::COutput::LogSDLError();
    return false;
  } 

  mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (!mixer) {
    console::COutput::LogError("AUDIO", "failed to create audio mixer");
    console::COutput::LogSDLError();
    return false;
  }

  return true;
}

  MIX_Track* AudioSys::createAudioTrack() {
    MIX_Track* track = MIX_CreateTrack(mixer);
    if (!track) {
      console::COutput::LogError("AUDIO", "failed to create audio mixer");
      console::COutput::LogSDLError();
    }
    return track;
  }

  bool AudioSys::resumeTrack(MIX_Track* track) {
    if (MIX_ResumeTrack(track)) {
      return true;
    } else {
      console::COutput::LogError("AUDIO", "failed to resume audio track");
      console::COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::playTrack(MIX_Track* track) {
    if (MIX_PlayTrack(track, 0)) {
      return true;
    } else {
      console::COutput::LogError("AUDIO", "failed to play audio track");
      console::COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::pauseTrack(MIX_Track* track) {
    if (MIX_PauseTrack(track)) {
      return true;
    } else {
      console::COutput::LogError("AUDIO", "failed to pause audio track");
      console::COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::restartTrack(MIX_Track* track) {
    if (MIX_SetTrackPlaybackPosition(track, 1)) {
      return true;
    } else {
      console::COutput::LogError("AUDIO", "failed to restart audio track");
      console::COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::loadTrackAudio(MIX_Track* track, std::string audioFileLocation) {

    MIX_Audio* audio = MIX_LoadAudio(mixer, audioFileLocation.c_str(), true);
    if (!audio) {
      console::COutput::LogError("AUDIO", "failed to load audio file");
      console::COutput::LogSDLError();
      return false;
    }
    if (!MIX_SetTrackAudio(track, audio)) {
      console::COutput::LogError("AUDIO", "failed to set audio track");
      console::COutput::LogSDLError();
      return false;
    }
    return true;
  }

