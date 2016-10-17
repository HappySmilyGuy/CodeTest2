#include "gtest/gtest.h"
#include "../../headers/Cube.h"

TEST(CubeTests, EqualityOperand)
{
  Cube a;
  EXPECT_TRUE(a == a) << "Cube equality operand does not correctly identify equality.";
  Cube b(a);
  EXPECT_TRUE(a == b) << "Cube equality operand does not correctly identify equality.";
  a.rotate_face(UP, CLOCKWISE);
  EXPECT_FALSE(a == b) << "Cube equality operand does not correctly identify inequality.";
  a.rotate_face_UP, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a == b) << "Cube equality operand does not correctly identifiy equality after rotations.";
  a.rotate_cube(X, CLOCKWISE);
  EXPECT_FALSE(a == b) << "Cube equality operand does not correctly identify inequality by orientation.";
}

TEST(CubeTests, InequalityOperand)
{
  Cube a;
  EXPECT_FALSE(a != a) << "Cube inequality operand does not correctly identify equality.";
  Cube b(a);
  EXPECT_FASLE(a != b) << "Cube inequality operand does not correctly identify equality.";
  a.rotate_face(UP, CLOCKWISE);
  EXPECT_TRUE(a != b) << "Cube inequality operand does not correctly identify inequality.";
  a.rotate_face_UP, COUNTER_CLOCKWISE);
  EXPECT_FALSE(a != b) << "Cube inequality operand does not correctly identifiy equality after rotations.";
  a.rotate_cube(X, CLOCKWISE);
  EXPECT_TRUE(a != b) << "Cube inequality operand does not correctly identify inequality by orientation.";
}

TEST(CubeTests, EquivalentFunction)
{
  Cube a;
  EXPECT_TRUE(a.equivalent(a)) << "\"equivalent\" function does not correctly match equality.";
  Cube b(a);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 0.";
  b.rotate_cube(X, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 0.";
  b.rotate_cube(X, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 1.";
  b.rotate_cube(Y, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 1.";
  b.rotate_cube(Y, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 2.";
  b.rotate_cube(Z, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 2.";
  b.rotate_cube(Z, COUNTER_CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equality. 3.";
  b.rotate_cube(X, CLOCKWISE);
  b.rotate_cube(X, CLOCKWISE);
  EXPECT_TRUE(a.equivalent(b)) << "\"equivalent\" function does not correctly match equivalence. 3.";
}

namespace
{
  bool check_cube(const Cube& cube, uint[6][3][3] expected_stickers, int& f, int& x, int& y)
  {
    Cube_Of_Faces c = cube.view();
    for (f = 0; f < 6; ++f)
    {
      for (x = 0; x < 3; ++x)
      {
        for (y = 0; x < 3; ++x)
        {
          EXPECT_EQ(expected_stickers[f][x][y] != c[f][x][y]);
        }
      }
    }
    return true;
  }
}

TEST(CubeTests, RotateFaceFunction)
{
  Cube a;
  int f,x,y;
  EXPECT_TRUE(check_cube(a, {{{0,0,0},{0,0,0},{0,0,0}},
                             {{1,1,1},{1,1,1},{1,1,1}},
                             {{2,2,2},{2,2,2},{2,2,2}},
                             {{3,3,3},{3,3,3},{3,3,3}},
                             {{4,4,4},{4,4,4},{4,4,4}},
                             {{5,5,5},{5,5,5},{5,5,5}}}, f, x, y)) << "\"check_cube\" function doesn't correctly find equality.";
  EXPECT_FALSE(check_cube(a, {{{1,0,0},{0,0,0},{0,0,0}},
                              {{1,1,1},{1,1,1},{1,1,1}},
                              {{2,2,2},{2,2,2},{2,2,2}},
                              {{3,3,3},{3,3,3},{3,3,3}},
                              {{4,4,4},{4,4,4},{4,4,4}},
                              {{5,5,5},{5,5,5},{5,5,5}}}, f, x, y)) << "\"check_cube\" function doesn't correctly find inequality.";
  a.rotate_face(FRONT, CLOCKWISE);
  EXPECT_TRUE(check_cube(a, {{{0,0,0},{0,0,0},{0,0,0}},
                             {{4,1,1},{4,1,1},{4,1,1}},
                             {{2,2,2},{2,2,2},{2,2,2}},
                             {{3,3,5},{3,3,5},{3,3,5}},
                             {{4,4,4},{4,4,4},{3,3,3}},
                             {{1,1,1},{5,5,5},{5,5,5}}}, f, x, y)) << "\"rotate\" doesn't correctly rotate a face. "
                                                                      "Error at [" + f + "][" + x + "][" + y + "] 1.";
  a.rotate_face(FRONT, COUNTER_CLOCKWISE);
  EXPECT_EQ(a, Cube()) << "\"rotate_face\" function does not correctly rotate COUNTER_CLOCKWISE.";
  a.rotate_face(BACK, CLOCKWISE);
  EXPECT_TRUE(check_cube(a, {{{0,0,0},{0,0,0},{0,0,0}},
                             {{1,1,5},{1,1,5},{1,1,5}},
                             {{2,2,2},{2,2,2},{2,2,2}},
                             {{4,3,3},{4,3,3},{4,3,3}},
                             {{1,1,1},{4,4,4},{4,4,4}},
                             {{5,5,5},{5,5,5},{3,3,3}}}, f, x, y)) << "\"rotate\" doesn't correctly rotate a face. "
                                                                      "Error at [" + f + "][" + x + "][" + y + "] 1.";
  a.rotate_face(RIGHT, CLOCKWISE);
  EXPECT_TRUE(check_cube(a, {{{0,0,5},{0,0,5},{0,0,3}},
                             {{1,1,1},{1,1,1},{5,5,5}},
                             {{1,2,2},{4,2,2},{4,2,2}},
                             {{4,3,3},{4,3,3},{4,3,3}},
                             {{1,1,0},{4,4,0},{4,4,0}},
                             {{5,5,2},{5,5,2},{3,3,2}}}, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. "
                                                                      "Error at [" + f + "][" + x + "][" + y + "] 1.";
  a.rotate_face(BACK, COUNTER_CLOCKWISE);
  a.rotate_face(BACK, COUNTER_CLOCKWISE);
  EXPECTED_EQ(a, Cube()) << "\"rotate_face\" function does not correctly rotate COUNTER_CLOCKWISE.";
  // TODO tests need extending.
}

TEST(CubeTests, RotateCubeFunction)
{
  a.rotate_cube(X, CLOCKWISE);
  EXPECT_TRUE(check_cube(a, {{{5,5,5},{5,5,5},{5,5,5}},
                             {{1,1,1},{1,1,1},{1,1,1}},
                             {{4,4,4},{4,4,4},{4,4,4}},
                             {{0,0,0},{0,0,0},{0,0,0}},
                             {{3,3,3},{3,3,3},{3,3,3}},
                             {{2,2,2},{2,2,2},{2,2,2}}}, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. "
                                                                      "Error at [" + f + "][" + x + "][" + y + "] 1.";
  a.rotate_cube(X, COUNTER_CLOCKWISE);
  EXPECTED_EQ(a, Cube()) << "\"rotate_cube\" function does not correctly rotate COUNTER_CLOCKWISE in X.";

  a.rotate_cube(Y, CLOCKWISE);
  EXPECT_TRUE(check_cube(a, {{{1,1,1},{1,1,1},{1,1,1}},
                             {{2,2,2},{2,2,2},{2,2,2}},
                             {{3,3,3},{3,3,3},{3,3,3}},
                             {{0,0,0},{0,0,0},{0,0,0}},
                             {{4,4,4},{4,4,4},{4,4,4}},
                             {{5,5,5},{5,5,5},{5,5,5}}}, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. "
                                                                      "Error at [" + f + "][" + x + "][" + y + "] 1.";
  a.rotate_cube(Y, COUNTER_CLOCKWISE);
  EXPECTED_EQ(a, Cube()) << "\"rotate_cube\" function does not correctly rotate COUNTER_CLOCKWISE in Y.";

  a.rotate_cube(Z, CLOCKWISE);
  EXPECT_TRUE(check_cube(a, {{{0,0,0},{0,0,0},{0,0,0}},
                             {{4,4,4},{4,4,4},{4,4,4}},
                             {{2,2,2},{2,2,2},{2,2,2}},
                             {{5,5,5},{5,5,5},{5,5,5}},
                             {{3,3,3},{3,3,3},{3,3,3}},
                             {{1,1,1},{1,1,1},{1,1,1}}}, f, x, y)) << "\"rotate\" doesn't correctly rotate the face that is rotating. "
                                                                      "Error at [" + f + "][" + x + "][" + y + "] 1.";
  a.rotate_cube(Z, COUNTER_CLOCKWISE);
  EXPECTED_EQ(a, Cube()) << "\"rotate_cube\" function does not correctly rotate COUNTER_CLOCKWISE in Z.";
}

TEST(CubeTests, RandomiseFunction)
{
  bool bl = Cube().randomise() == Cube();
  EXPECTED_FALSE(bl && Cube().randomise() == Cube()) << "\"randomise()\" doesn't do any changes.";
  bl = Cube().randomise() == Cube().randomise();
  EXPECTED_FASLE(bl && Cube().randomise() == Cube().randomise()) << "\"randomise()\" doesn't do random changes.";
}

TEST(CubeTests, IsCompleteFunction)
{
  Cube a;
  EXPECT_TRUE(a.is_complete()) << "\"is_complete()\" incorrectly identifies a default cube as incomplete.";
  a.rotate_face(UP, COUNTERCLOCKWISE);
  EXPECT_FALSE(a.is_complete()) << "\"is_complete()\" incorrectly identifies an incomplete cube as complete.";
  a.rotate_face(UP, CLOCKWISE);
  EXPECT_TRUE(a.is_complete()) << "\"is_complete()\" incorrectly identifies a complete cube as incomplete. 1.";
  a.rotate_cube(X, CLOCKWISE);
  EXPECT_TRUE(a.is_complete()) << "\"is_complete()\" incorrectly identifies a rotated complete cube as incomplete. 1.";
}

TEST(CubeTests, ResetFunction)
{
  {
    Cube a;
    a.rotate_face(UP, COUNTER_CLOCKWISE);
    a.reset();
    EXPECT_EQ(a, Cube()) << "\"reset()\" does not successfully reset a cube with a rotated face.";
  }
  {
    Cube a;
    a.rotate_cube(X, COUNTER_CLOCKWISE);
    a.reset();
    EXPECT_EQ(a, Cube()) << "\"reset()\" does not successfully reset a rotated cube.";
  }
}