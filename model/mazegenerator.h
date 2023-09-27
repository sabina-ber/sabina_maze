/**
 * @file mazegenerator.h
 * @brief Maze generator using random algorithms.
 */
#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <map>
#include <random>
#include <set>

#include "cell.h"
#include "maze.h"

/**
 * @class MazeGenerator
 * @brief Class for generating random mazes.
 *
 * This class is responsible for generating random mazes using random
 * algorithms.
 */
class MazeGenerator {
 public:
  /**
   * @brief Constructor that accepts a Maze object to populate.
   * @param maze Reference to a Maze object.
   */
  explicit MazeGenerator(Maze& maze);
  /**
   * @brief Main function to generate the maze.
   *
   * Initializes and executes the algorithm for maze generation.
   */
  void generate();

 private:
  std::vector<int> generateRowIds(int cols, int row);
  void addWall(int row, int col);
  std::vector<int> fillFirstRowIds();
  std::vector<int> buildWalls(const std::vector<int>& row_ids, int row);
  void addHorizontalWalls(int row, const std::vector<int>& currentRowIds);
  std::vector<int> checkIds(const std::vector<int>& row_ids, int row);
  int generateNewId();
  bool randomDecision();
  void buildLastRow(std::vector<int>& row_ids, int row);
  std::vector<int> mergeCells(const std::vector<int>& row_ids, int col);
  void fillFirstRow();
  void fillLastRow();
  void fillLeftAndRight();

 private:
  Maze& maze;
  std::set<int> uniqueIds;
  std::mt19937 gen;
};

#endif  // MAZEGENERATOR_H
