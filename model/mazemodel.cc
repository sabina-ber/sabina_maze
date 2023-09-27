#include "mazemodel.h"

#include "cell.h"

MazeModel::MazeModel() : QObject(), maze(nullptr), generator(nullptr) {}

bool MazeModel::loadFromFile(const std::string& filePath) {
  maze = std::make_unique<Maze>(filePath.c_str());
  emit mazeChanged();
  return true;
}

void MazeModel::generate(int rows, int cols) {
  maze = std::make_unique<Maze>(rows, cols);
  generator = std::make_unique<MazeGenerator>(*maze);
  generator->generate();
  emit mazeGenerated();
}

void MazeModel::save(const std::string& filePath) {
  maze->saveToFile(filePath);
}

void MazeModel::solve(int startX, int startY, int endX, int endY,
                      const std::vector<std::vector<int>>& mazeToSolve) {
  std::vector<std::pair<int, int>> solvedMazeVector =
      maze->solveMaze(startX, startY, endX, endY, mazeToSolve);
  emit mazeSolved(solvedMazeVector);
}

std::vector<std::vector<int>> MazeModel::getMaze() const {
  if (maze) {
    return maze->getMaze();
  } else {
    return std::vector<std::vector<int>>();
  }
}
