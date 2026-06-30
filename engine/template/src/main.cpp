#include "../../../engine/src/secret.hpp"

int main() {

  using namespace secret;
  const std::string GAMENAME = "{{NAME}}";

  core::Engine::init(500, 500, GAMENAME);
  core::Engine::options.fpsCap = 60;
  core::Engine::options.renderingAPI = core::RenderingAPIs::SDL;

  // Update - Called every frame
  core::Engine::update = [&]() {

  };

  core::Engine::run();

}
