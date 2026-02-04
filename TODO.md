


namespace elo {

struct Vector2 {

  float x;
  float y;

  symbol functions,
  like for vector2+vector2


}

struct Color {
  
  int r
  int g
  int b

}

namespace core {



static class Engine {

  struct EngineOptions {


  }

  public:

  static bool update;

  static engineOptions m_options;

  static bool run(); 
  

}
}

namespace rend {

class Renderer {
  
  m_renderer
  m_window

  public:

  Renderer(windowname, width, height)

  bool renderSquare(Vector2, height, width)
  bool RenderSquareFill()

  bool renderLine()

  bool renderClear()

  bool setRenderColor()

  bool renderText()

}

static class RenderSys {

  public:

  static Renderer m_renderer;

  staic Render(Engine& engine);

} 

}

namespace ecs {

per component:
struct Transform {
  Vector2 m_pos;
  m_width
  m_height
  m_radius
}

static class TransformComponent {
  public:
  add()
  rem()
  get()
  has()

  private:

  std::map entityList

}

static class ECS {
  public:
  addEntity();
  remEntity()
  findEntity()

  private:

  std::vector m_validEntities;
  uint32 m_entityCount

}
}

namespace math {

  vector math
  static dot()

}

namespace input {
  
  static class InputSys

}










}

add a rigidBody component, add a player controller component
make sure to add the rigidbody update in the collision detection 








