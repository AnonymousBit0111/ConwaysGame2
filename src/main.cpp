#include "Hallucen/Hallucen.h"
#include "Hallucen/Ref.h"
#include "Mainscene.h"

int main() {
  Hallucen::Engine::init();

  Hallucen::Engine::initWindow(1000, 1000, "Conways game of life");
  Hallucen::Engine::runScene(Hallucen::make_Ref<Game::MainScene>());

  Hallucen::Engine::cleanup();
}