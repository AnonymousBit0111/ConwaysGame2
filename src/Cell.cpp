#include "Cell.h"
#include "Hallucen/GL/DrawData.h"
#include "fwd.hpp"

using namespace Game;
using namespace Hallucen;
using namespace Hallucen::GL;

void Cell::updateVerts() {

  m_vertices = {
      TextureVertex{m_Pos.x, m_Pos.y, m_Colour.x, m_Colour.y, m_Colour.z, 0, 0

      },
      // top left
      TextureVertex{m_Pos.x + m_Size.x, m_Pos.y,

                    m_Colour.x,

                    m_Colour.y,

                    m_Colour.z, 0, 1

      },
      // top right
      TextureVertex{m_Pos.x + m_Size.x, m_Pos.y - m_Size.y,

                    m_Colour.x,

                    m_Colour.y,

                    m_Colour.z, 1, 1

      },
      // bottom  right
      TextureVertex{m_Pos.x, m_Pos.y - m_Size.y, m_Colour.x,

                    m_Colour.y,

                    m_Colour.z, 1, 0

      } // Bottom Left
  };
};

Cell::Cell(glm::vec2 pos, glm::vec3 colour)
    : m_Pos(pos), m_Colour(colour), m_Size(10, 10) {
  for (int i = 0; i < 4; i++) {
    m_vertices.push_back(TextureVertex{0, 0, 0, 0, 0, 0, 0});
  }
  m_GridPos = {m_Pos.x/m_Size.x,m_Pos.y/m_Size.y};

  updateVerts();
}

void Cell::setColour(glm::vec3 colour){
  this->m_Colour = colour;
  updateVerts();

}

bool Cell::contains(glm::vec2 pos) {
  bool a = (pos.x > m_vertices[0].x);
  bool b = (pos.x < m_vertices[1].x);
  bool c = (pos.y > m_vertices[2].y);
  bool d = (pos.y < m_vertices[0].y);

  return (a && b && c && d);
}