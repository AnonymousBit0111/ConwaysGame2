
#pragma once
#include "Hallucen/Entity.h"
#include "Hallucen/GL/DrawData.h"
#include "detail/qualifier.hpp"
#include "fwd.hpp"
#include <vector>

namespace Game {

class Cell : public Hallucen::Drawable {

private:
  std::vector<Hallucen::GL::TextureVertex> m_vertices;
  std::vector<Cell *> m_Neighbors;
  glm::vec2 m_Size, m_Pos, m_GridPos;
  glm::vec3 m_Colour;
  bool alive;

  void updateVerts();

public:
  Cell(glm::vec2 position, glm::vec3 colour);

  glm::vec2 getGridPos() { return m_GridPos; }

    std::vector<Cell *> getNeighbors(){return m_Neighbors;}

    bool isAlive(){return alive;}
  void setNeighbors(std::vector<Cell *> &neighbors) { m_Neighbors = neighbors; }
  bool contains(glm::vec2 pos);
  std::shared_ptr<Hallucen::Image> getImage() override { return nullptr; };
  std::vector<Hallucen::GL::TextureVertex> getVertices() override {
    return m_vertices;
  }

  inline std::vector<unsigned int> getIndices() override {
    return {0, 1, 2, 2, 3, 0};
  };
  inline std::shared_ptr<Hallucen::GL::Texture2D> getTexture() override {
    return nullptr;
  };
  void setColour(glm::vec3 colour);
  void Kill() {
    setColour({0, 0, 0});
    alive = false;
  }
  void Birth() {
    setColour({0.8, 0.8, 0.8});
    alive = true;
  }

  ~Cell() {}
};
} // namespace Game