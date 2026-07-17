#include "../../../engine/src/secret.hpp"

int main() {

  using namespace secret;
  using namespace core;
  using namespace rend;
  using namespace ecs;
  using namespace console;
  using namespace audio;
  const std::string GAMENAME = "{{NAME}}";

  Engine::options.fpsCap = 60;
  Engine::options.renderingAPI = core::RenderingAPIs::SDL;
  Engine::init(500, 500, GAMENAME);

  // Update - Called every frame
  Engine::update = [&]() {

  };

  Engine::run();

}
