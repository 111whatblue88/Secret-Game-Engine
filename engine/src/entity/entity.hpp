#ifndef _ENTITY_HPP
#define _ENTITY_HPP


#include <SDL3/SDL.h>
#include <string>

namespace elo {

class elogine;


  class RenderingComp {
  friend class elogine;
  public:
    void changeImage(const elo::elogine& engine, const std::string imagePath);
    SDL_FRect m_imageLocation;
    ~RenderingComp();
  private:
    void render(SDL_Renderer* renderer);
    SDL_Texture* m_texture;
  };

  class Entity {
  friend class elogine;
  public:

  Entity(int x, int y);

  int x, y;

  //rendering
  bool rendEnabled;
  RenderingComp rendComp;


  };









};

#endif



