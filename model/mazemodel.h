/**
 * @file mazemodel.h
 * @brief MazeModel class to handle maze operations.
 */

#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <QObject>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "maze.h"
#include "mazegenerator.h"
/**
 * @class MazeModel
 * @brief Class for managing maze operations.
 *
 * This class is responsible for loading, generating, solving, and saving mazes.
 */
class MazeModel : public QObject {
  Q_OBJECT

 public:
  /**
   * @brief Default constructor.
   */
  MazeModel();
  /**
   * @brief Load a maze from a file.
   * @param filePath Path to the file.
   * @return True if successful, false otherwise.
   */
  bool loadFromFile(const std::string& filePath);
  /**
   * @brief Generate a new maze.
   * @param rows Number of rows.
   * @param cols Number of columns.
   */
  void generate(int rows, int cols);
  /**
   * @brief Solve the maze.
   * @param startX Starting x-coordinate.
   * @param startY Starting y-coordinate.
   * @param endX Ending x-coordinate.
   * @param endY Ending y-coordinate.
   * @param mazeToSolve 2D vector representing the maze.
   */
  void solve(int startX, int startY, int endX, int endY,
             const std::vector<std::vector<int>>& mazeToSolve);
  /**
   * @brief Save the maze to a file.
   * @param filePath Path to the file.
   */
  void save(const std::string& filePath);
  /**
   * @brief Get the current maze.
   * @return 2D vector representing the maze.
   */
  std::vector<std::vector<int>> getMaze() const;
  /**
   * @brief Check if a maze is available.
   * @return True if a maze is loaded or generated, false otherwise.
   */
  bool isMazeAvailable() const { return maze != nullptr; }

 signals:
  /**
   * @brief Signal emitted when the maze is changed.
   */
  void mazeChanged();
  /**
   * @brief Signal emitted when the maze is solved.
   * @param std::vector<std::pair<int, int>> Vector of coordinates for the
   * solution path.
   */
  void mazeSolved(std::vector<std::pair<int, int>>);
  /**
   * @brief Signal emitted when a new maze is generated.
   */
  void mazeGenerated();

 private:
  std::unique_ptr<Maze> maze;
  std::unique_ptr<MazeGenerator> generator;
};

#endif  // MAZEMODEL_H
