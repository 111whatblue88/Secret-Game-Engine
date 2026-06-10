#include <string>

#include "../../../engine/src/secret.hpp"

int main() {

  using namespace secret;
  using namespace input;
  using namespace ecs;
  using namespace rend;
  using namespace console;
  using ID = uint32_t;

  const std::string GAMENAME = "template";

  core::Engine::init(500, 500, GAMENAME);
  core::Engine::options.fpsCap = 60;

  // Update - Called every frame
  core::Engine::update = [&]() {

  };

  core::Engine::run();

}
