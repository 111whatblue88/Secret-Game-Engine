current way of creating entities:
{
  ID entityID = ecs::EntitySys.createEntity(ecs::TranformComponent(
    Vector2(20,20), 20, 20
  ))

  auto& entityPB ecs::PhysicsBodyComponent.add(entityID, ecs::PhysicsBody())

}

it would be better if it was something like: 

{
  using namespace ecs;
  ID entityID = entitySys.createEntity(component<transform>())
  auto& textComponents = entitySys.addComponents(entityID, // returns a vector<component&>  
    component<textRenderer>(Vector2(20,20), "location.ttf", 24, "hello #1"),
    component<textRenderer>(Vector2(20,40), "location.ttf", 24, "hello #2"),
    component<textRenderer>(Vector2(20,60), "location.ttf", 24, "hello #3"),
    component<textRenderer>(Vector2(20,80), "location.ttf", 24, "hello #4")
  )
  // and then to edit one of the text components 

  textComponents[3].updateText("hello!")

}

template <typename t> component

vector<map<id, vector<component>>


