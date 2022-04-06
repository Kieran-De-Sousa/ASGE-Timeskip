#include "Scene.h"

Scene::Scene(ASGE::Renderer& rendererRef, ASGE::Input& inputRef) :
  renderer(&rendererRef), inputs(&inputRef)
{
}