#include "gtest/gtest.h"
#include "../../headers/Cube.h"

TEST(CubeTests, equality_operand)
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

TEST(CubeTests, inequality_operand)
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

TEST(CubeTests, equivalent_function)
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

TEST(CubeTests, rotate_face_function)
{
  // TODO
}

TEST(CubeTests, rotate_cube_function)
{
  // TODO
}

TEST(CubeTests, randomise_function)
{
  // TODO
}

TEST(CubeTests, is_complete_function)
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

TEST(CubeTests, reset_function)
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