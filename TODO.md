current ECS:

// for object creation
ID objID = EntitySys.createEntity(
  Transform(
    Vector2(20,20),
    20,
    20
));

// for component adding
auto& objComp EntitySys.*Comp.add(
  obj,
  *(
    *
    *
  )
)
objID AND variables for every component

It would be much better if it was something like: 

class Entity {
public: 

  const ID getID();

  Transform transform;
  Component<ImgRenderer> ImgRenderers;

private:
  
  template<typename T>
  struct Component<T> {
    auto& get(identifier);
    void remove(identifier);
  }

  ID m_ID;

}

USAGE:

Entity& e = EntitySys.createEntity(
  Transform(
    Vector2(20,20),
    20,
    20
));

EntitySys.Component<ImgRenderer>.add(
  e.ID;
  ImgRenderer(
    "imgforsomethingsomething",
    *,
    *
  ),
  ImgRenderer(
    "imgforsomethingelse",
    *,
    *
  )

)
e.TextRenderer.get("imgforsomethingelse").pos =+ {20,20};


this will be a bitch to implement but will greatly improve entity creation and usage

