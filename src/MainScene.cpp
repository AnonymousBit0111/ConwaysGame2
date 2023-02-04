
#include "Mainscene.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/Hallucen.h"
#include "Hallucen/Profile.h"
#include "Hallucen/Scenerenderer.h"
#include "SDL2/SDL_keycode.h"
#include "fwd.hpp"
#include <future>
#include <thread>
#include <vector>
using namespace Game;
using namespace Hallucen;

std::vector<Cell *> GetNeighbors(Cell cell, std::vector<Cell> &cells) {

  std::vector<Cell *> neighbors;

  neighbors.reserve(8);

  for (Cell &c : cells)

  {

    if (c.getGridPos() == cell.getGridPos())
      continue;

    else

    {

      if ((c.getGridPos().x == cell.getGridPos().x + 1 &&
           c.getGridPos().y == cell.getGridPos().y - 1) ||

          (c.getGridPos().x == cell.getGridPos().x - 1 &&
           c.getGridPos().y == cell.getGridPos().y) ||

          (c.getGridPos().x == cell.getGridPos().x + 1 &&
           c.getGridPos().y == cell.getGridPos().y) ||

          (c.getGridPos().x == cell.getGridPos().x &&
           c.getGridPos().y == cell.getGridPos().y + 1) ||

          (c.getGridPos().x == cell.getGridPos().x &&
           c.getGridPos().y == cell.getGridPos().y - 1) ||

          (c.getGridPos().x == cell.getGridPos().x - 1 &&
           c.getGridPos().y == cell.getGridPos().y + 1) ||

          (c.getGridPos().x == cell.getGridPos().x - 1 &&
           c.getGridPos().y == cell.getGridPos().y - 1) ||

          (c.getGridPos().x == cell.getGridPos().x + 1 &&
           c.getGridPos().y == cell.getGridPos().y + 1))

      {

        neighbors.push_back(&c);
      }
    }
  }

  return neighbors;
}

MainScene::MainScene() : cam(1000, 1000) {
  ProfileFunc;
  paused = true;
  sceneRenderer = SceneRenderer::create(nullptr);

  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {

      Cell c(glm::vec2{x * 10, y * 10}, glm::vec3{0, 0, 0});

      currentGen.push_back(c);
    }
  }
  for (auto &i : currentGen) {

    auto neighbors = GetNeighbors(i, currentGen);
    i.setNeighbors(neighbors);
    ;
  }
}
void MainScene::ImGuiLogic(float frametime) {}

void MainScene::render() {
  ProfileFunc;
  sceneRenderer->beginBatch();
  if (paused) {
    for (auto &i : currentGen) {
      sceneRenderer->addEntity(i);
    }
  } else {
    for (auto &cell : nextGen)

    {

      sceneRenderer->addEntity(cell);
    }

    currentGen = nextGen;

    nextGen.clear();
  }
  sceneRenderer->endBatch();
  sceneRenderer->flush(cam, false);
}

void MainScene::update(float deltaTime) {
  ProfileFunc;

  if (Engine::isKeyDown(SDLK_SPACE)) {
    paused = !paused;
  }
  if (Engine::isKeyDown(SDLK_UP)) {
    cam.move({0, 10});
  } else if (Engine::isKeyDown(SDLK_DOWN)) {

    cam.move({0, -10});
  } else if (Engine::isKeyDown(SDLK_LEFT)) {
    cam.move({-10, 0});

  } else if (Engine::isKeyDown(SDLK_RIGHT)) {
    cam.move({10, 0});
  }

  if (paused) {

    glm::vec2 mousepos = Hallucen::Engine::getMousePositionRelative(cam);

    for (auto &i : currentGen) {
      if (i.contains(mousepos)) {
        i.Birth();
      }
    }
  } else {
    for (auto cell : currentGen)

    {

      int aliveneighbors = 0;

      auto neighbors = cell.getNeighbors();

      for (auto &i : neighbors)

      {

        if (i->isAlive())

        {

          aliveneighbors++;
        }
      }

      if (cell.isAlive())

      {

        if (aliveneighbors < 2)

        {

          cell.Kill();

        }

        else if (aliveneighbors > 3)

        {

          cell.Kill();
        }

      }

      else

      {

        if (aliveneighbors == 3)

        {

          cell.Birth();
        }
      }

      nextGen.push_back(cell);
    }
  }
}

void MainScene::handleKey(SDL_Keycode key) {}

void MainScene::onMouseDown() {}