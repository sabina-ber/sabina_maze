#include "mazegenerator.h"

MazeGenerator::MazeGenerator(Maze& maze)
    : maze(maze), gen(std::mt19937(std::random_device()())) {}

void MazeGenerator::generate() {
  std::vector<int> currentRowIds(maze.getCols());
  currentRowIds = fillFirstRowIds();
  for (int i = 0; i < maze.getRows(); ++i) {
    currentRowIds = checkIds(currentRowIds, i);
    currentRowIds = buildWalls(currentRowIds, i);

    if (i != maze.getRows() - 1) {
      addHorizontalWalls(i, currentRowIds);
    }

    if (i == maze.getRows() - 1) {
      buildLastRow(currentRowIds, i);
    }
  }
  fillFirstRow();
  fillLastRow();
  fillLeftAndRight();
}

std::vector<int> MazeGenerator::checkIds(const std::vector<int>& row_ids,
                                         int row) {
  std::vector<int> arr(maze.getCols());
  for (int j = 0; j < maze.getCols(); ++j) {
    if (row != 0) {
      if (maze.getCell(row - 1, j) & BOTTOM_WALL) {
        arr[j] = generateNewId();
      } else {
        arr[j] = row_ids[j];
      }
    } else {
      arr[j] = row_ids[j];
    }
  }
  return arr;
}

std::vector<int> MazeGenerator::fillFirstRowIds() {
  std::vector<int> arr(maze.getCols(), 0);
  int current_id = 1;
  for (int j = 0; j < maze.getCols(); ++j) {
    uniqueIds.insert(current_id);
    arr[j] = current_id++;
  }
  return arr;
}

std::vector<int> MazeGenerator::buildWalls(const std::vector<int>& row_ids,
                                           int row) {
  std::vector<int> arr = row_ids;
  for (std::vector<int>::size_type col = 0; col < row_ids.size() - 1; ++col) {
    if (randomDecision() || (arr[col] == arr[col + 1])) {
      addWall(row, col);
    } else {
      arr = mergeCells(arr, col);
    }
  }
  return arr;
}

void MazeGenerator::buildLastRow(std::vector<int>& row_ids, int row) {
  for (std::vector<int>::size_type col = 0; col < row_ids.size() - 1; ++col) {
    if (row_ids[col] != row_ids[col + 1]) {
      int cellValue = maze.getCell(row, col);
      maze.setCell(row, col, cellValue & ~RIGHT_WALL);
      int old_id = row_ids[col + 1];
      int new_id = row_ids[col];
      std::replace_if(
          row_ids.begin(), row_ids.end(),
          [old_id](const int& id) { return id == old_id; }, new_id);
    }
  }
}

std::vector<int> MazeGenerator::mergeCells(const std::vector<int>& row_ids,
                                           int col) {
  std::vector<int> arr = row_ids;
  int SellToMerge = arr[col + 1];
  int SellMerging = arr[col];
  for (std::vector<int>::size_type j = 0; j < row_ids.size(); ++j) {
    if (arr[j] == SellToMerge) {
      arr[j] = SellMerging;
    }
  }
  return arr;
}

void MazeGenerator::addHorizontalWalls(int row,
                                       const std::vector<int>& currentRowIds) {
  std::map<int, int> idFrequency;
  for (int col = 0; col < maze.getCols(); ++col) {
    int currentId = currentRowIds[col];
    idFrequency[currentId]++;
  }
  for (int col = 0; col < maze.getCols(); ++col) {
    int currentId = currentRowIds[col];
    if (randomDecision()) {
      if (idFrequency[currentId] > 1) {
        int cellValue = maze.getCell(row, col);
        maze.setCell(row, col, cellValue | BOTTOM_WALL);
        idFrequency[currentId]--;
      }
    }
  }
}

void MazeGenerator::addWall(int row, int col) {
  int cellValue = maze.getCell(row, col);
  maze.setCell(row, col, cellValue | RIGHT_WALL);
}

void MazeGenerator::fillFirstRow() {
  for (int i = 0; i < 1; ++i) {
    for (int j = 0; j < maze.getCols(); ++j) {
      int existingValue = maze.getCell(i, j);
      maze.setCell(i, j, existingValue | TOP_WALL);
    }
  }
}

void MazeGenerator::fillLastRow() {
  for (int i = maze.getRows() - 1; i > maze.getRows() - 2; --i) {
    for (int j = 0; j < maze.getCols(); ++j) {
      int existingValue = maze.getCell(i, j);
      maze.setCell(i, j, existingValue | BOTTOM_WALL);
    }
  }
}

void MazeGenerator::fillLeftAndRight() {
  for (int i = 0; i < maze.getRows(); ++i) {
    for (int j = 0; j < maze.getCols(); ++j) {
      if (j == 0) {
        int existingValue = maze.getCell(i, j);
        maze.setCell(i, j, existingValue | LEFT_WALL);
      }
      if (j == maze.getCols() - 1) {
        int existingValue = maze.getCell(i, j);
        maze.setCell(i, j, existingValue | RIGHT_WALL);
      }
    }
  }
}

int MazeGenerator::generateNewId() {
  int maxId;
  if (uniqueIds.empty()) {
    maxId = 0;
  } else {
    maxId = *uniqueIds.rbegin();
  }
  int newId = maxId + 1;
  if (newId < 0) {
    throw std::overflow_error("ID has overflowed");
  }
  uniqueIds.insert(newId);
  return newId;
}

bool MazeGenerator::randomDecision() {
  std::uniform_int_distribution<> distrib(0, 1);
  return distrib(gen) == 1;
}
