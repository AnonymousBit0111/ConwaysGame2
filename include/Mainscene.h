#pragma once
#include "Cell.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/Ref.h"
#include "Hallucen/Scene.h"
#include "Hallucen/Scenerenderer.h"
#include <vector>

namespace Game {

class MainScene : public Hallucen::Scene {

private:
  Hallucen::GL::Camera2D cam;
  Hallucen::Ref<Hallucen::SceneRenderer> sceneRenderer;
  bool paused;
  std::vector<Cell> currentGen;
  std::vector<Cell> nextGen;

public:
  MainScene();

  void ImGuiLogic(float frametime) override;
  void render() override;
  void update(float deltaTime) override;
  void winSizeChanged(Hallucen::Vector2i newsize) override {}
  void handleKey(SDL_Keycode key) override;

  void onMouseDown() override;
};
} // namespace Game