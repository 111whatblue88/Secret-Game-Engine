#ifndef _ELOGINE_HPP
#define _ELOGINE_HPP

#include "rendering/render.hpp"
#include "terminal/input.hpp"
#include "terminal/output.hpp"
#include "utils/utils.hpp"
#include "entity/entity.hpp"

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <vector>

namespace elo {

class elogine {
friend class RenderingComp;
public:

  elogine(std::string name, float width, float height);
  ~elogine();

  bool run();

  // FPS getter and setter
  void setTargetFPS(int inTargetFPS);
  int TargetFPS();

  void addEntity(std::unique_ptr<Entity> inEntity);

private:

  //main stuff
  bool m_quit;
  RenderContext m_mainContext;

  bool render();


  int targetFPS;
  float deltaTime;

  //entity related
  std::vector<std::unique_ptr<Entity>> entityVector;



};

} // namespace elo

#endif
