#ifndef MAZE_H
#define MAZE_H

#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class Maze
 * @brief Maze class for representing and solving mazes.
 *
 * The Maze class provides functionalities to create a maze, load a maze from a
 * file, save a maze to a file, and solve a maze using various algorithms.
 */
class Maze {
 public:
  /**
   * @brief Constructor to initialize a Maze object with given rows and columns.
   *
   * @param rows Number of rows in the maze.
   * @param cols Number of columns in the maze.
   */
  Maze(int rows, int cols);

  /**
   * @brief Constructor to initialize a Maze object from a file.
   *
   * @param filePath Path to the file containing the maze representation.
   */
  explicit Maze(const std::string& filePath);

  /// @brief Method to load a maze from a file.
  void loadFromFile();

  /**
   * @brief Method to save the current maze to a file.
   *
   * @param filePath Path to the file where the maze will be saved.
   */
  void saveToFile(const std::string& filePath);

  /**
   * @brief Method to solve the current maze.
   *
   * @param startX Start row.
   * @param startY Start column.
   * @param endX End row.
   * @param endY End column.
   * @param mazeToSolve The maze matrix to solve.
   * @return A vector containing the path from start to end.
   */
  std::vector<std::pair<int, int>> solveMaze(
      int startX, int startY, int endX, int endY,
      const std::vector<std::vector<int>>& mazeToSolve);

  /// @name Getters
  /// @{

  /**
   * @brief Get the value of a cell in the maze.
   *
   * @param row Row of the cell.
   * @param col Column of the cell.
   * @return The value of the cell.
   */
  int getCell(int row, int col) const;

  /// @brief Get the number of rows in the maze.
  int getRows() const;

  /// @brief Get the number of columns in the maze.
  int getCols() const;

  /// @brief Get the current maze matrix.
  const std::vector<std::vector<int>> getMaze() const;

  /// @}

  /**
   * @brief Set the value of a cell in the maze.
   *
   * @param row Row of the cell.
   * @param col Column of the cell.
   * @param value New value of the cell.
   */
  void setCell(int row, int col, int value);

 private:
  std::vector<std::vector<int>> calculateDistances(
      int startX, int startY, const std::vector<std::vector<int>>& mazeToSolve);
  bool canMove(int currentX, int currentY, int newX, int newY,
               const std::vector<std::vector<int>>& maze);

 private:
  std::vector<std::vector<int>> maze;
  int rows, cols;
  std::string filePath;
  friend class MazeGenerator;
};

#endif  // MAZE_H
