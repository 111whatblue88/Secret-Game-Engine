
#include "audio.hpp"
#include "../secret.hpp"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>
#include <format>

using namespace secret;
using namespace audio;

MIX_Mixer* AudioSys::mixer = NULL;

bool AudioSys::Init() {

  if (!MIX_Init()) {
    COutput::LogError("AUDIO", "failed to start SDL_mixer");
    COutput::LogSDLError();
    return false;
  } 

  mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (!mixer) {
    COutput::LogError("AUDIO", "failed to create audio mixer");
    COutput::LogSDLError();
    return false;
  }

  return true;
}

  MIX_Track* AudioSys::createAudioTrack() {
    MIX_Track* track = MIX_CreateTrack(mixer);
    if (!track) {
      COutput::LogError("AUDIO", "failed to create audio mixer");
      COutput::LogSDLError();
    }
    return track;
  }

  bool AudioSys::resumeTrack(MIX_Track* track) {
    if (MIX_ResumeTrack(track)) {
      return true;
    } else {
      COutput::LogError("AUDIO", "failed to resume audio track");
      COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::playTrack(MIX_Track* track) {
    if (MIX_PlayTrack(track, 0)) {
      return true;
    } else {
      COutput::LogError("AUDIO", "failed to play audio track");
      COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::pauseTrack(MIX_Track* track) {
    if (MIX_PauseTrack(track)) {
      return true;
    } else {
      COutput::LogError("AUDIO", "failed to pause audio track");
      COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::restartTrack(MIX_Track* track) {
    if (MIX_SetTrackPlaybackPosition(track, 1)) {
      return true;
    } else {
      COutput::LogError("AUDIO", "failed to restart audio track");
      COutput::LogSDLError();
      return false;
    }
  }
  bool AudioSys::loadTrackAudio(MIX_Track* track, std::string audioFileLocation) {

    MIX_Audio* audio = MIX_LoadAudio(mixer, audioFileLocation.c_str(), true);
    if (!audio) {
      COutput::LogError("AUDIO", "failed to load audio track");
      COutput::LogSDLError();
      return false;
    }
    if (!MIX_SetTrackAudio(track, audio)) {
      COutput::LogError("AUDIO", "failed to set audio track");
      COutput::LogSDLError();
      return false;
    }
    return true;
  }

