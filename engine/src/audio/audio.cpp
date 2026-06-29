
#include "audio.hpp"
#include "../secret.hpp"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>

using namespace secret;
using namespace audio;

MIX_Mixer* AudioSys::mixer = NULL;

bool AudioSys::Init() {

  if (!MIX_Init()) {
    console::COutput::logCustom("AUDIO ERROR", "failed to start SDL_mixer");
    console::COutput::logSDLError();
    return false;
  } 

  mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (!mixer) {
    console::COutput::logCustom("AUDIO ERROR", "failed to create audio mixer");
    console::COutput::logSDLError();
    return false;
  }

  return true;
}

  MIX_Track* AudioSys::createAudioTrack() {
    MIX_Track* track = MIX_CreateTrack(mixer);
    if (!track) {
      console::COutput::logCustom("AUDIO ERROR", "failed to create audio mixer");
      console::COutput::logSDLError();
    }
    return track;
  }

  bool AudioSys::resumeTrack(MIX_Track* track) {
    if (MIX_ResumeTrack(track)) {
      return true;
    } else {
      console::COutput::logCustom("AUDIO ERROR", "failed to resume audio track");
      console::COutput::logSDLError();
      return false;
    }
  }
  bool AudioSys::playTrack(MIX_Track* track) {
    if (MIX_PlayTrack(track, 0)) {
      return true;
    } else {
      console::COutput::logCustom("AUDIO ERROR", "failed to play audio track");
      console::COutput::logSDLError();
      return false;
    }
  }
  bool AudioSys::pauseTrack(MIX_Track* track) {
    if (MIX_PauseTrack(track)) {
      return true;
    } else {
      console::COutput::logCustom("AUDIO ERROR", "failed to pause audio track");
      console::COutput::logSDLError();
      return false;
    }
  }
  bool AudioSys::restartTrack(MIX_Track* track) {
    if (MIX_SetTrackPlaybackPosition(track, 1)) {
      return true;
    } else {
      console::COutput::logCustom("AUDIO ERROR", "failed to restart audio track");
      console::COutput::logSDLError();
      return false;
    }
  }
  bool AudioSys::loadTrackAudio(MIX_Track* track, std::string audioFileLocation) {

    MIX_Audio* audio = MIX_LoadAudio(mixer, audioFileLocation.c_str(), true);
    if (!audio) {
      console::COutput::logCustom("AUDIO ERROR", "failed to load audio file");
      console::COutput::logSDLError();
      return false;
    }
    if (!MIX_SetTrackAudio(track, audio)) {
      console::COutput::logCustom("AUDIO ERROR", "failed to set audio track");
      console::COutput::logSDLError();
      return false;
    }
    return true;
  }

