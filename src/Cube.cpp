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
    if (direction >= 2 || face >= 6)
    {
      return;
    }
    Cube_Of_Faces temp = faces_;

    // rotate only the face stickers
    for (int x = 0; x < 3; ++x)
    {
      for (int y = 0; y < 3; ++y)
      {
        if (direction == CLOCKWISE)
        {
          temp[face][x][y] = faces_[face][x][2 - y];
        }
        else //direction == COUNTER_CLOCKWISE
        {
          temp[face][x][y] = faces_[face][2 - x][y];
        }
      }
    }

    // TODO rotate connected edge stickers
    switch (face)
    {
      case FRONT:
        if (direction == CLOCKWISE)
        {
          // <- R(far left) <- U(bottom) <- L(far right) <- D(top)
          temp[DOWN][0] = {faces_[RIGHT][0][0], faces_[RIGHT][0][1], faces_[RIGHT][0][2]};
          temp[RIGHT][0][0] = faces_[UP][2][0];
          temp[RIGHT][0][1] = faces_[UP][2][1];
          temp[RIGHT][0][2] = faces_[UP][2][2];
          temp[UP][3] = {faces_[LEFT][2][2], faces_[LEFT][1][2], faces_[LEFT][0][2]};
          temp[LEFT][0][2] = faces_[DOWN][0][0];
          temp[LEFT][1][2] = faces_[DOWN][0][1];
          temp[LEFT][2][2] = faces_[DOWN][0][2];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          temp[DOWN][0] = {faces_[LEFT][0][2], faces_[LEFT][1][2], faces_[LEFT][2][2]};
          temp[RIGHT][0][0] = faces_[DOWN][0][0];
          temp[RIGHT][0][1] = faces_[DOWN][0][1];
          temp[RIGHT][0][2] = faces_[DOWN][0][2];
          temp[UP][3] = {faces_[RIGHT][0][0], faces_[RIGHT][0][1], faces_[RIGHT][0][2]};
          temp[LEFT][0][2] = faces_[UP][2][2];
          temp[LEFT][1][2] = faces_[UP][2][1];
          temp[LEFT][2][2] = faces_[UP][2][0];
        }
        break;

      case RIGHT:
        if (direction == CLOCKWISE)
        {
          // F(far right) -> U(far right) -> B(far left reverse) -> D(far right)
          temp[FRONT][0][2] = faces_[DOWN][0][2];
          temp[FRONT][1][2] = faces_[DOWN][1][2];
          temp[FRONT][2][2] = faces_[DOWN][2][2];
          temp[UP][0][2] = faces_[FRONT][0][2];
          temp[UP][1][2] = faces_[FRONT][1][2];
          temp[UP][2][2] = faces_[FRONT][2][2];
          temp[BACK][2][2] = faces_[UP][0][2];
          temp[BACK][2][1] = faces_[UP][1][2];
          temp[BACK][2][0] = faces_[UP][2][2];
          temp[DOWN][0][2] = faces_[BACK][2][2];
          temp[DOWN][1][2] = faces_[BACK][2][1];
          temp[DOWN][2][2] = faces_[BACK][2][0];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          // F(far right) <- U(far right) <- B(far left reverse) <- D(far right)
          temp[FRONT][0][2] = faces_[UP][0][2];
          temp[FRONT][1][2] = faces_[UP][1][2];
          temp[FRONT][2][2] = faces_[UP][2][2];
          temp[UP][0][2] = faces_[BACK][2][0];
          temp[UP][1][2] = faces_[BACK][2][1];
          temp[UP][2][2] = faces_[BACK][2][2];
          temp[BACK][2][2] = faces_[DOWN][0][2];
          temp[BACK][2][1] = faces_[DOWN][1][2];
          temp[BACK][2][0] = faces_[DOWN][2][2];
          temp[DOWN][0][2] = faces_[FRONT][0][2];
          temp[DOWN][1][2] = faces_[FRONT][1][2];
          temp[DOWN][2][2] = faces_[FRONT][2][2];
        }
        break;

      case BACK:
        if (direction == CLOCKWISE)
        {
          // RIGHT <- UP <- LEFT <- BOTTOM
        }
        else // direction == COUNTER_CLOCKWISE
        {
          // RIGHT -> UP -> LEFT -> BOTTOM
        }
        break;

      case LEFT:
        if (direction == CLOCKWISE)
        {

        }
        else // direction == COUNTER_CLOCKWISE
        {

        }
        break;

      case UP:
        if (direction == CLOCKWISE)
        {

        }
        else // direction == COUNTER_CLOCKWISE
        {

        }
        break;

      case DOWN:
        if (direction == CLOCKWISE)
        {

        }
        else // direction == COUNTER_CLOCKWISE
        {

        }
        break;
      default:
        return;
    }
    faces_ = temp;
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