#include "../engine/src/ELOgine.hpp"

int main() {

  using namespace elo;
  using ID = uint32_t;

  core::Engine::init(1600, 1000, "testgame");
  core::Engine::options.fpsCap = 60;

  // Update - Called every frame
  core::Engine::update = [&]() {

  };

  core::Engine::run();

}



