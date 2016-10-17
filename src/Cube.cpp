//
// Created by Eddie on 17-Oct-16.
//

#include "../headers/Cube.h"

namespace RubiksCube
{
  namespace
  {
    Cube_Of_Faces initialised_faces()
    {

    }
  }

  Cube::Cube()
    : faces_(initialised_faces())
  {}

  Cube::Cube(const Cube& in)
  {
    // TODO
  }

  Cube::~Cube()
  {}

  void Cube::randomise(unsigned int no_of_rotates)
  {
    //TODO
  }

  void Cube::rotate_face(Face face, Direction direction)
  {
    //TODO
  }

  void Cube::rotate_cube(Axis, Direction)
  {
    // TODO
  }

  bool Cube::is_solved() const
  {
    // TODO
    return false;
  }

  Cube_Of_Faces Cube::view() const
  {
    // TODO
    return Cube_Of_Faces();
  }

  void Cube::reset()
  {
    //TODO
  }

  bool Cube::operator==(const Cube &rhs) const
  {
    return faces_ == rhs.faces_;
  }

  bool Cube::operator!=(const Cube &rhs) const
  {
    return !(rhs == *this);
  }

  bool Cube::equivalent(const Cube &rhs) const
  {
    //TODO
    return false;
  }

}