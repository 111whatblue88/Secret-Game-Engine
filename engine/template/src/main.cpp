#include "../../../engine/src/HUGE.hpp"

int main() {

  using namespace huge;
  using ID = uint32_t;

  core::Engine::init(1600, 1000, "testgame");
  core::Engine::options.fpsCap = 60;

  // Update - Called every frame
  core::Engine::update = [&]() {

  };

  core::Engine::run();

}



