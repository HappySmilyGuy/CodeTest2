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
    : faces_(in.view())
  {}

  Cube::~Cube()
  {}

  void Cube::randomise(unsigned int no_of_rotates)
  {
    //TODO
  }

  void Cube::rotate_face(Face face, Direction direction)
  {
    Cube_Of_Faces temp;
    for (int x = 0; x < 3; ++x)
    {
      for (int y = 0; y < 3; ++y)
      {
        if (direction == CLOCKWISE)
        {
          temp[face][x][y] = faces_[face][x][2 - y];
        }
        else if (direction == COUNTER_CLOCKWISE)
        {
          temp[face][x][y] = faces_[face][2 - x][y];
        }
        else return; // should never happen: incorrect input.
      }
    }
    for (int x = 0; x < 3; ++x)
    {
      for (int y = 0; y < 3; ++y)
      {
        faces_[face][x][y] = temp[face][x][y];
      }
    }
    // TODO rotate connected edge squares
    switch (face)
    {
      case FRONT:

        break;
      case RIGHT:

        break;
      case BACK:

        break;
      case LEFT:

        break;
      case UP:

        break;
      case DOWN:

        break;

    }
  }

  void Cube::rotate_cube(Axis axis, Direction dir)
  {

  }

  bool Cube::is_solved() const
  {
    for (int f = 0; f < 6; ++f)
    {
      int face_value = faces_[f][0][0];
      for (int x = 0; x < 3; ++x)
      {
        for (int y = 0; y < 3; ++y)
        {
          if (faces_[f][x][y] != face_value)
          {
            return false;
          }
        }
      }
    }
    return true;
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