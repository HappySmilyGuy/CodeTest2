//
// Created by Eddie on 17-Oct-16.
//

#ifndef RUBIKS_CUBE_CUBE_H
#define RUBIKS_CUBE_CUBE_H

#include <array>
#include <random>
#include <chrono>

namespace RubiksCube
{
  enum Colour { GREEN, RED, BLUE, ORANGE, WHITE, YELLOW };
  enum Face { FRONT, RIGHT, BACK, LEFT, UP, DOWN };
  enum Direction { CLOCKWISE, COUNTER_CLOCKWISE };
  enum Axis { X, Y, Z };

  typedef std::array<std::array<Colour, 3>, 3> Face_Type;
  typedef std::array<Face_Type, 6> Cube_Of_Faces;

  const std::array<std::string, 6> ColourStrings = {"Green", "Red", "Blue", "Orange", "White", "Yellow"};
  const std::array<char, 6> ColourChars = { 'G', 'R', 'B', 'O', 'W', 'Y' };
  const std::array<std::string, 6> FaceStrings { "Front", "Right", "Back", "Left", "Up", "Down" };
  const std::array<char, 6> FaceChars = { 'F', 'R', 'B', 'L', 'T', 'D' };

  /// This class is an implementation of a Rubik's Cube.
  /// WARNING: this class is not thread safe.
  ///
  /// In this implementation of a classic Rubik's Cube, each of the six faces is covered by nine stickers,
  /// each of one of six solid colours: white, red, blue, orange, green, and yellow:
  /// White is opposite yellow, blue is opposite green, and orange is opposite red, and the red, white and blue are
  /// arranged in that order in a clockwise arrangement around one vertex.
  /// Each face turns independently, also rotating the stickers adgacent to that face.
  /// For the puzzle to be solved, each face must be returned to have only one colour.
  class Cube
  {
  public:
    /// Cube is constructed with all sickers on FRONT set to GREEN, all of RIGHT set to RED, BACK set to BLUE,
    /// LEFT to ORANGE, UP to WHITE and DOWN to YELLOW.
    Cube();

    /// Cube is created with in the same state as @obj
    Cube(const Cube& obj);
    virtual ~Cube();

    /// Applies @no_of_rotates random rotations.
    void randomise(unsigned int no_of_rotations = 30);

    void rotate_face(Face, Direction);

    /// Rotates the entire cube 90 degrees into a different orientation.
    /// A rotation in the X axis is looking from the outside at the RIGHT face.
    /// A rotation in the Y axis is looking from the outside at the UP face.
    /// A rotation in the Z axis is looking from the outside at the FRONT face.
    void rotate_cube(Axis, Direction);

    /// Returns whether each side of the cube includes stickers with only a single colour.
    bool is_solved() const;

    /// Returns a copy of the state of the cube.
    Cube_Of_Faces view() const;

    /// Sets the state to the same as the default constructor.
    void reset();

    bool operator==(const Cube &rhs) const;
    bool operator!=(const Cube &rhs) const;

    /// returns true if the cubes are the same but in different orientations.
    bool equivalent(const Cube &rhs) const;

  private:
    void rotate_just_face(Face face, Direction dir);

    // equivalent to "Colour faces[6][3][3]"
    Cube_Of_Faces faces_;
  };
}

#endif //RUBIKS_CUBE_CUBE_H
