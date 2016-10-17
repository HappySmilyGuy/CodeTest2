#include "gtest/gtest.h"
#include "../../headers/Cube.h"

using RubiksCube::Cube;
using RubiksCube::Cube_Of_Faces;
using RubiksCube::Face;
using RubiksCube::Direction::CLOCKWISE;
using RubiksCube::Direction::COUNTER_CLOCKWISE;
using RubiksCube::Axis;

TEST(CubeTests, EqualityOperand)
{
  Cube a;
  EXPECT_TRUE(a == a) << "Cube equality operand does not correctly identify equality.";
  Cube b(a);
  EXPECT_TRUE(a == b) << "Cube equality operand does not correctly identify equality.";
  a.rotate_face(Face::UP, CLOCKWISE);
  EXPECT_FALSE(a == b) << "Cube equality operand does not correctly identify inequality.";
  a.rotate_face(Face::UP, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a == b) << "Cube equality operand does not correctly identify equality after rotations.";
  a.rotate_cube(Axis::X, CLOCKWISE);
  EXPECT_FALSE(a == b) << "Cube equality operand does not correctly identify inequality by orientation.";
}

TEST(CubeTests, InequalityOperand)
{
  Cube a;
  EXPECT_FALSE(a != a) << "Cube inequality operand does not correctly identify equality.";
  Cube b(a);
  EXPECT_FALSE(a != b) << "Cube inequality operand does not correctly identify equality.";
  a.rotate_face(Face::UP, CLOCKWISE);
  EXPECT_TRUE(a != b) << "Cube inequality operand does not correctly identify inequality.";
  a.rotate_face(Face::UP, COUNTER_CLOCKWISE);
  EXPECT_FALSE(a != b) << "Cube inequality operand does not correctly identify equality after rotations.";
  a.rotate_cube(Axis::X, CLOCKWISE);
  EXPECT_TRUE(a != b) << "Cube inequality operand does not correctly identify inequality by orientation.";
}

TEST(DISABLED_CubeTests, EquivalentFunction)
{
  Cube a;
  EXPECT_TRUE(a.equivalent(a)) << "\"equivalent\" function does not correctly match equality.";
  Cube b(a);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 0.";
  b.rotate_cube(Axis::X, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 0.";
  b.rotate_cube(Axis::X, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 1.";
  b.rotate_cube(Axis::Y, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 1.";
  b.rotate_cube(Axis::Y, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 2.";
  b.rotate_cube(Axis::Z, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 2.";
  b.rotate_cube(Axis::Z, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 3.";
  b.rotate_cube(Axis::X, CLOCKWISE);
  b.rotate_cube(Axis::X, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 3.";
}

namespace
{
  bool check_cube(const Cube& cube, int expected_stickers[6][3][3], int& f, int& x, int& y)
  {
    Cube_Of_Faces c = cube.view();
    for (f = 0; f < 6; ++f)
    {
      for (x = 0; x < 3; ++x)
      {
        for (y = 0; y < 3; ++y)
        {
          if (expected_stickers[f][x][y] != c[f][x][y])
          {
            return false;
          }
        }
      }
    }
    return true;
  }
}

TEST(CubeTests, RotateFaceFunction)
{
  Cube a;
  int f, x, y;
  {
    int expected[6][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
                             {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
                             {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"check_cube\" function doesn't correctly find equality.";

  }
  {
    int expected[6][3][3] = {{{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
                             {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
                             {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}};
    EXPECT_FALSE(check_cube(a, expected, f, x, y)) << "\"check_cube\" function doesn't correctly find inequality.";
  }
  a.rotate_face(Face::FRONT, CLOCKWISE);
  {
    int expected[6][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{4, 1, 1}, {4, 1, 1}, {4, 1, 1}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{3, 3, 5}, {3, 3, 5}, {3, 3, 5}},
                             {{4, 4, 4}, {4, 4, 4}, {3, 3, 3}},
                             {{1, 1, 1}, {5, 5, 5}, {5, 5, 5}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate FRONT CLOCKWISE.";
  }
  a.rotate_face(Face::FRONT, COUNTER_CLOCKWISE);
  EXPECT_EQ(a, Cube()) << "\"rotate_face\" function does not correctly rotate FRONT COUNTER_CLOCKWISE.";
  a.rotate_face(Face::BACK, CLOCKWISE);
  {
    int expected[6][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{1, 1, 5}, {1, 1, 5}, {1, 1, 5}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{4, 3, 3}, {4, 3, 3}, {4, 3, 3}},
                             {{1, 1, 1}, {4, 4, 4}, {4, 4, 4}},
                             {{5, 5, 5}, {5, 5, 5}, {3, 3, 3}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate BACK CLOCKWISE.";
  }
  a.rotate_face(Face::RIGHT, CLOCKWISE);
  {
    int expected[6][3][3] = {{{0, 0, 5}, {0, 0, 5}, {0, 0, 3}},
                             {{1, 1, 1}, {1, 1, 1}, {5, 5, 5}},
                             {{4, 2, 2}, {4, 2, 2}, {1, 2, 2}},
                             {{4, 3, 3}, {4, 3, 3}, {4, 3, 3}},
                             {{1, 1, 0}, {4, 4, 0}, {4, 4, 0}},
                             {{5, 5, 2}, {5, 5, 2}, {3, 3, 2}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate FRONT and it's face CLOCKWISE.";
  }
  a.rotate_face(Face::RIGHT, COUNTER_CLOCKWISE);
  {
    int expected[6][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{1, 1, 5}, {1, 1, 5}, {1, 1, 5}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{4, 3, 3}, {4, 3, 3}, {4, 3, 3}},
                             {{1, 1, 1}, {4, 4, 4}, {4, 4, 4}},
                             {{5, 5, 5}, {5, 5, 5}, {3, 3, 3}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate RIGHT's face COUNTER_CLOCKWISE.";
  }
  a.rotate_face(Face::BACK, COUNTER_CLOCKWISE);
  {
    int expected[6][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
                             {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
                             {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate_face\" function does not correctly rotate BACK COUNTER_CLOCKWISE.";
  }
  // TODO tests need extending.
}

TEST(CubeTests, RotateCubeFunction)
{
  Cube a;
  int f, x, y;
  a.rotate_cube(Axis::X, CLOCKWISE);
  {
    int expected[6][3][3] = {{{5, 5, 5}, {5, 5, 5}, {5, 5, 5}},
                             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                             {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
                             {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
                             {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. 0.";
  }
  a.rotate_cube(Axis::X, COUNTER_CLOCKWISE);
  EXPECT_EQ(a, Cube()) << "\"rotate_cube\" function does not correctly rotate COUNTER_CLOCKWISE in X.";

  a.rotate_cube(Axis::Y, CLOCKWISE);
  {
    int expected[6][3][3] = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
                             {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
                             {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. 1.";
  }
  a.rotate_cube(Axis::Y, COUNTER_CLOCKWISE);
  EXPECT_EQ(a, Cube()) << "\"rotate_cube\" function does not correctly rotate COUNTER_CLOCKWISE in Y.";

  a.rotate_cube(Axis::Z, CLOCKWISE);
  {
    int expected[6][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                             {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
                             {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
                             {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}},
                             {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
                             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
    EXPECT_TRUE(check_cube(a, expected, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. 2.";
  }
  a.rotate_cube(Axis::Z, COUNTER_CLOCKWISE);
  EXPECT_EQ(a, Cube()) << "\"rotate_cube\" function does not correctly rotate COUNTER_CLOCKWISE in Z.";
}

TEST(DISABLED_CubeTests, RandomiseFunction)
{
  Cube a, b, c;
  a.randomise();
  b.randomise();
  c.randomise();
  bool bl = a == Cube();
  EXPECT_FALSE(bl && b == Cube()) << "\"randomise()\" doesn't do any changes.";
  bl = a == b;
  EXPECT_FALSE(bl && b == c) << "\"randomise()\" doesn't do random changes.";
}

TEST(CubeTests, IsCompleteFunction)
{
  Cube a;
  EXPECT_TRUE(a.is_solved()) << "\"is_solved()\" incorrectly identifies a default cube as incomplete.";
  a.rotate_face(Face::UP, COUNTER_CLOCKWISE);
  EXPECT_FALSE(a.is_solved()) << "\"is_solved()\" incorrectly identifies an incomplete cube as complete.";
  a.rotate_face(Face::UP, CLOCKWISE);
  EXPECT_TRUE(a.is_solved()) << "\"is_solved()\" incorrectly identifies a complete cube as incomplete. 1.";
  a.rotate_cube(Axis::X, CLOCKWISE);
  EXPECT_TRUE(a.is_solved()) << "\"is_solved()\" incorrectly identifies a rotated complete cube as incomplete. 1.";
}

TEST(CubeTests, ResetFunction)
{
  {
    Cube a;
    a.rotate_face(Face::UP, COUNTER_CLOCKWISE);
    a.reset();
    EXPECT_EQ(a, Cube()) << "\"reset()\" does not successfully reset a cube with a rotated face.";
  }
  {
    Cube a;
    a.rotate_cube(Axis::X, COUNTER_CLOCKWISE);
    a.reset();
    EXPECT_EQ(a, Cube()) << "\"reset()\" does not successfully reset a rotated cube.";
  }
}