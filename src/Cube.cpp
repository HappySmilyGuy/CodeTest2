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
      Cube_Of_Faces out;
      for (int f = 0; f < 6; ++f)
      {
        for (int x = 0; x < 3; ++x)
        {
          for (int y = 0; y < 3; ++y)
          {
            out[f][x][y] = static_cast<Colour>(f);
          }
        }
      }
      return out;
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

  void Cube::randomise(unsigned int no_of_rotations)
  {
    long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::knuth_b rng(seed); // random number generator
    for (int i = 0; i < no_of_rotations; ++i)
    {
      if (rng() & 1)
      {
        rotate_face(static_cast<Face>(rng()%6), static_cast<Direction>(rng() & 1));
      }
      else
      {
        rotate_cube(static_cast<Axis>(rng()%3), static_cast<Direction>(rng() & 1));
      }
    }
  }

  void Cube::rotate_face(Face face, Direction direction)
  {
    if (direction >= 2 || face >= 6)
    {
      return;
    }
    rotate_just_face(face, direction);
    Cube_Of_Faces temp = faces_;

    // rotate connected edge stickers
    switch (face)
    {
      case FRONT:
        if (direction == CLOCKWISE)
        {
          // <- R(far left) <- U(bottom) <- L(far right) <- D(top)
          temp[DOWN][0] = {faces_[RIGHT][0][0], faces_[RIGHT][1][0], faces_[RIGHT][2][0]};
          temp[RIGHT][0][0] = faces_[UP][2][0];
          temp[RIGHT][1][0] = faces_[UP][2][1];
          temp[RIGHT][2][0] = faces_[UP][2][2];
          temp[UP][2] = {faces_[LEFT][2][2], faces_[LEFT][1][2], faces_[LEFT][0][2]};
          temp[LEFT][0][2] = faces_[DOWN][0][0];
          temp[LEFT][1][2] = faces_[DOWN][0][1];
          temp[LEFT][2][2] = faces_[DOWN][0][2];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          temp[DOWN][0] = {faces_[LEFT][0][2], faces_[LEFT][1][2], faces_[LEFT][2][2]};
          temp[RIGHT][0][0] = faces_[DOWN][0][0];
          temp[RIGHT][1][0] = faces_[DOWN][0][1];
          temp[RIGHT][2][0] = faces_[DOWN][0][2];
          temp[UP][2] = {faces_[RIGHT][0][0], faces_[RIGHT][1][0], faces_[RIGHT][2][0]};
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
          temp[BACK][2][0] = faces_[UP][0][2];
          temp[BACK][1][0] = faces_[UP][1][2];
          temp[BACK][0][0] = faces_[UP][2][2];
          temp[DOWN][0][2] = faces_[BACK][2][0];
          temp[DOWN][1][2] = faces_[BACK][1][0];
          temp[DOWN][2][2] = faces_[BACK][0][0];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          // F(far right) <- U(far right) <- B(far left reverse) <- D(far right)
          temp[FRONT][0][2] = faces_[UP][0][2];
          temp[FRONT][1][2] = faces_[UP][1][2];
          temp[FRONT][2][2] = faces_[UP][2][2];
          temp[UP][0][2] = faces_[BACK][2][0];
          temp[UP][1][2] = faces_[BACK][1][0];
          temp[UP][2][2] = faces_[BACK][0][0];
          temp[BACK][2][0] = faces_[DOWN][0][2];
          temp[BACK][1][0] = faces_[DOWN][1][2];
          temp[BACK][0][0] = faces_[DOWN][2][2];
          temp[DOWN][0][2] = faces_[FRONT][0][2];
          temp[DOWN][1][2] = faces_[FRONT][1][2];
          temp[DOWN][2][2] = faces_[FRONT][2][2];
        }
        break;

      case BACK:
        if (direction == CLOCKWISE)
        {
          // RIGHT(far right) -> UP(top) -> LEFT(far left) -> DOWN(bottom)
          temp[RIGHT][0][2] = faces_[DOWN][2][0];
          temp[RIGHT][1][2] = faces_[DOWN][2][1];
          temp[RIGHT][2][2] = faces_[DOWN][2][2];
          temp[UP][0] = {faces_[RIGHT][0][2], faces_[RIGHT][1][2], faces_[RIGHT][2][2]};
          temp[LEFT][0][0] = faces_[UP][0][0];
          temp[LEFT][1][0] = faces_[UP][0][1];
          temp[LEFT][2][0] = faces_[UP][0][2];
          temp[DOWN][2] = {faces_[LEFT][0][0], faces_[LEFT][0][1], faces_[LEFT][0][2]};
        }
        else // direction == COUNTER_CLOCKWISE
        {
          // RIGHT(far right) <- UP(top) <- LEFT(far left) <- DOWN
          temp[RIGHT][0][2] = faces_[UP][0][0];
          temp[RIGHT][1][2] = faces_[UP][0][1];
          temp[RIGHT][2][2] = faces_[UP][0][2];
          temp[UP][0] = {faces_[LEFT][2][0], faces_[LEFT][1][0], faces_[LEFT][0][0]};
          temp[LEFT][0][0] = faces_[DOWN][2][0];
          temp[LEFT][1][0] = faces_[DOWN][2][1];
          temp[LEFT][2][0] = faces_[DOWN][2][2];
          temp[DOWN][2] = {faces_[RIGHT][2][2], faces_[RIGHT][1][2], faces_[RIGHT][0][2]};
        }
        break;

      case LEFT:
        if (direction == CLOCKWISE)
        {
          // UP(far left) -> FRONT(far left) -> BOTTOM(far left) -> BACK(far right reverse)
          temp[FRONT][0][0] = faces_[UP][0][0];
          temp[FRONT][1][0] = faces_[UP][1][0];
          temp[FRONT][2][0] = faces_[UP][2][0];
          temp[UP][0][0] = faces_[BACK][0][2];
          temp[UP][1][0] = faces_[BACK][1][2];
          temp[UP][2][0] = faces_[BACK][2][2];
          temp[BACK][2][2] = faces_[DOWN][0][0];
          temp[BACK][1][2] = faces_[DOWN][1][0];
          temp[BACK][0][2] = faces_[DOWN][2][0];
          temp[DOWN][0][0] = faces_[FRONT][0][0];
          temp[DOWN][1][0] = faces_[FRONT][1][0];
          temp[DOWN][2][0] = faces_[FRONT][2][0];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          // UP(far left) <- FRONT(far left) <- BOTTOM(far left) <- BACK(far right reverse)
          temp[FRONT][0][0] = faces_[DOWN][0][0];
          temp[FRONT][1][0] = faces_[DOWN][1][0];
          temp[FRONT][2][0] = faces_[DOWN][2][0];
          temp[UP][0][0] = faces_[FRONT][0][0];
          temp[UP][1][0] = faces_[FRONT][1][0];
          temp[UP][2][0] = faces_[FRONT][2][0];
          temp[BACK][2][2] = faces_[UP][0][0];
          temp[BACK][1][2] = faces_[UP][1][0];
          temp[BACK][0][2] = faces_[UP][2][0];
          temp[DOWN][0][0] = faces_[BACK][2][2];
          temp[DOWN][1][0] = faces_[BACK][1][2];
          temp[DOWN][2][0] = faces_[BACK][0][2];
        }
        break;

      case UP:
        if (direction == CLOCKWISE)
        {
          temp[BACK][0] = faces_[LEFT][0];
          temp[RIGHT][0] = faces_[BACK][0];
          temp[FRONT][0] = faces_[RIGHT][0];
          temp[LEFT][0] = faces_[FRONT][0];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          temp[BACK][0] = faces_[RIGHT][0];
          temp[RIGHT][0] = faces_[FRONT][0];
          temp[FRONT][0] = faces_[LEFT][0];
          temp[LEFT][0] = faces_[BACK][0];
        }
        break;

      case DOWN:
        if (direction == CLOCKWISE)
        {
          temp[BACK][2] = faces_[RIGHT][2];
          temp[RIGHT][2] = faces_[FRONT][2];
          temp[FRONT][2] = faces_[LEFT][2];
          temp[LEFT][2] = faces_[BACK][2];
        }
        else // direction == COUNTER_CLOCKWISE
        {
          temp[BACK][2] = faces_[LEFT][2];
          temp[RIGHT][2] = faces_[BACK][2];
          temp[FRONT][2] = faces_[RIGHT][2];
          temp[LEFT][2] = faces_[FRONT][2];
        }
        break;
      default:
        return;
    }
    faces_ = temp;
  }

  void Cube::rotate_cube(Axis axis, Direction dir)
  {
    switch (axis)
    {
      case X:
        rotate_just_face(RIGHT, dir);
        if (dir == CLOCKWISE)
        {
          rotate_just_face(LEFT, COUNTER_CLOCKWISE);
          Cube_Of_Faces temp = faces_;
          for (int x = 0; x < 3; ++x)
          {
            for (int y = 0; y < 3; ++y)
            {
              temp[FRONT][x][y] = faces_[DOWN][x][y];
              temp[UP][x][y] = faces_[FRONT][x][y];
              temp[BACK][x][y] = faces_[UP][2-x][2-y];
              temp[DOWN][x][y] = faces_[BACK][2-x][2-y];
            }
          }
          faces_ = temp;
        }
        else // dir == COUNTER_CLOCKWISE
        {
          rotate_just_face(LEFT, CLOCKWISE);
          Cube_Of_Faces temp = faces_;
          for (int x = 0; x < 3; ++x)
          {
            for (int y = 0; y < 3; ++y)
            {
              temp[FRONT][x][y] = faces_[UP][x][y];
              temp[UP][x][y] = faces_[BACK][2-x][2-y];
              temp[BACK][x][y] = faces_[DOWN][2-x][2-y];
              temp[DOWN][x][y] = faces_[FRONT][x][y];
            }
          }
          faces_ = temp;
        }
        break;
      case Y:
        rotate_just_face(UP, dir);
        if (dir == CLOCKWISE)
        {
          rotate_just_face(DOWN, COUNTER_CLOCKWISE);
          Face_Type temp = faces_[RIGHT];
          faces_[RIGHT] = faces_[BACK];
          faces_[BACK] = faces_[LEFT];
          faces_[LEFT] = faces_[FRONT];
          faces_[FRONT] = temp;
        }
        else // dir == COUNTER_CLOCKWISE
        {
          rotate_just_face(DOWN, CLOCKWISE);
          Face_Type temp = faces_[RIGHT];
          faces_[RIGHT] = faces_[FRONT];
          faces_[FRONT] = faces_[LEFT];
          faces_[LEFT] = faces_[BACK];
          faces_[BACK] = temp;
        }
        break;
      case Z:
        rotate_just_face(FRONT, CLOCKWISE);
        if (dir == CLOCKWISE)
        {
          rotate_just_face(BACK, COUNTER_CLOCKWISE);
          Cube_Of_Faces temp = faces_;
          for (int x = 0; x < 3; ++x)
          {
            for (int y = 0; y < 3; ++y)
            {
              temp[UP][x][y] = faces_[LEFT][2-y][x];
              temp[RIGHT][x][y] = faces_[UP][2-y][x];
              temp[DOWN][x][y] = faces_[RIGHT][2-y][x];
              temp[LEFT][x][y] = faces_[DOWN][2-y][x];
            }
          }
          faces_ = temp;
        }
        else // dir == COUNTER_CLOCKWISE
        {
          rotate_just_face(BACK, CLOCKWISE);
          Cube_Of_Faces temp = faces_;
          for (int x = 0; x < 3; ++x)
          {
            for (int y = 0; y < 3; ++y)
            {
              temp[UP][x][y] = faces_[RIGHT][2-x][y];
              temp[RIGHT][x][y] = faces_[DOWN][2-x][y];
              temp[DOWN][x][y] = faces_[LEFT][2-x][y];
              temp[LEFT][x][y] = faces_[UP][2-x][y];
            }
          }
          faces_ = temp;
        }
        break;
    }
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
    return faces_;
  }

  void Cube::reset()
  {
    faces_ = initialised_faces();
  }

  bool Cube::operator==(const Cube &rhs) const
  {
    return faces_ == rhs.faces_;
  }

  bool Cube::operator!=(const Cube &rhs) const
  {
    return !(rhs == *this);
  }

  void Cube::rotate_just_face(Face face, Direction dir)
  {
    Face_Type temp;
    for (int x = 0; x < 3; ++x)
    {
      for (int y = 0; y < 3; ++y)
      {
        if (dir == CLOCKWISE)
        {
          temp[x][y] = faces_[face][2 - y][x];
        }
        else // dir == COUNTER_CLOCKWISE
        {
          temp[x][y] = faces_[face][y][2-x];
        }
      }
    }
    faces_[face] = temp;
  }

}