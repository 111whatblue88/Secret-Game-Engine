#include "../engine/src/elogine.hpp"

int main() {
 
  using namespace engine;

  core::Elogine engine("engineTest", 1600, 1000);
  engine.setTargetFPS(120);

  engine.run();

}
