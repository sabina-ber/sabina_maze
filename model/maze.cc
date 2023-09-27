#include "maze.h"

#include "cell.h"

const int INF = 1e9;

Maze::Maze(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  maze.resize(rows, std::vector<int>(cols, 0));
}

Maze::Maze(const std::string& filePath) {
  this->filePath = filePath;
  loadFromFile();
}

void Maze::loadFromFile() {
  std::ifstream inFile(filePath);
  if (!inFile.is_open()) {
    std::cerr << "Could not open the file." << std::endl;
    return;
  }

  int mazeRows, mazeCols;
  inFile >> mazeRows >> mazeCols;
  this->rows = mazeRows;
  this->cols = mazeCols;
  maze = std::vector<std::vector<int>>(mazeRows, std::vector<int>(mazeCols, 0));

  for (int i = 0; i < mazeRows; ++i) {
    for (int j = 0; j < mazeCols; ++j) {
      int value;
      inFile >> value;
      if (value == 1) {
        maze[i][j] |= RIGHT_WALL;
        if (j != mazeCols - 1) {        // new
          maze[i][j + 1] |= LEFT_WALL;  // new
        }
      }
    }
  }

  for (int i = 0; i < mazeRows; ++i) {
    for (int j = 0; j < mazeCols; ++j) {
      int value;
      inFile >> value;
      if (value == 1) {
        maze[i][j] |= BOTTOM_WALL;
        if (i != mazeRows - 1) {       // new
          maze[i + 1][j] |= TOP_WALL;  // new
        }
      }
    }
  }

  for (int i = 0; i < mazeRows; ++i) {
    maze[i][0] |= LEFT_WALL;
  }
  for (int j = 0; j < mazeCols; ++j) {
    maze[0][j] |= TOP_WALL;
  }

  inFile.close();
}

const std::vector<std::vector<int>> Maze::getMaze() const {
  int newRows = maze.size();
  int newCols = maze[0].size();
  std::vector<std::vector<int>> simpleMaze(newRows,
                                           std::vector<int>(newCols, 0));

  for (size_t i = 0; i < maze.size(); ++i) {
    for (size_t j = 0; j < maze[i].size(); ++j) {
      int cell = maze[i][j];
      if (cell & TOP_WALL) {
        simpleMaze[i][j] |= TOP_WALL;
      }
      if (cell & RIGHT_WALL) {
        simpleMaze[i][j] |= RIGHT_WALL;
      }
      if (cell & BOTTOM_WALL) {
        simpleMaze[i][j] |= BOTTOM_WALL;
      }
      if (cell & LEFT_WALL) {
        simpleMaze[i][j] |= LEFT_WALL;
      }
    }
  }

  return simpleMaze;
}

void Maze::saveToFile(const std::string& filePath) {
  std::ofstream outFile(filePath);
  if (!outFile.is_open()) {
    std::cerr << "Could not open the file for writing." << std::endl;
    return;
  }

  int mazeRows = maze.size();
  int mazeCols = maze[0].size();

  outFile << mazeRows << " " << mazeCols << std::endl;

  for (int i = 0; i < mazeRows; ++i) {
    for (int j = 0; j < mazeCols; ++j) {
      if (maze[i][j] & RIGHT_WALL) {
        outFile << "1 ";
      } else {
        outFile << "0 ";
      }
    }
    outFile << std::endl;
  }

  outFile << std::endl;

  for (int i = 0; i < mazeRows; ++i) {
    for (int j = 0; j < mazeCols; ++j) {
      if (maze[i][j] & BOTTOM_WALL) {
        outFile << "1 ";
      } else {
        outFile << "0 ";
      }
    }
    outFile << std::endl;
  }

  outFile.close();
}

int Maze::getRows() const { return rows; }

int Maze::getCols() const { return cols; }

int Maze::getCell(int row, int col) const {
  if (row >= 0 && row < rows && col >= 0 && col < cols) {
    return maze[row][col];
  }
  return -1;  // или другое значение для индикации ошибки
}

void Maze::setCell(int row, int col, int value) {
  if (row >= 0 && row < rows && col >= 0 && col < cols) {
    maze[row][col] = value;
  }
}

bool Maze::canMove(int currentX, int currentY, int newX, int newY,
                   const std::vector<std::vector<int>>& maze) {
  int dx = newX - currentX;
  int dy = newY - currentY;

  if (dx == 1 && dy == 0) {
    return !(maze[currentX][currentY] & BOTTOM_WALL);
  } else if (dx == -1 && dy == 0) {
    return !(maze[newX][newY] & BOTTOM_WALL);
  } else if (dx == 0 && dy == 1) {
    return !(maze[currentX][currentY] & RIGHT_WALL);
  } else if (dx == 0 && dy == -1) {
    return !(maze[newX][newY] & RIGHT_WALL);
  }
  return false;
}

std::vector<std::vector<int>> Maze::calculateDistances(
    int startX, int startY, const std::vector<std::vector<int>>& mazeToSolve) {
  int mazeRows = mazeToSolve.size();
  int mazeCols = mazeToSolve[0].size();
  std::vector<std::vector<int>> dist(mazeRows, std::vector<int>(mazeCols, INF));
  dist[startX][startY] = 0;

  std::queue<std::pair<int, int>> q;
  q.push({startX, startY});

  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  while (!q.empty()) {
    auto [currentX, currentY] = q.front();
    q.pop();
    for (const auto& [dx, dy] : directions) {
      int newX = currentX + dx;
      int newY = currentY + dy;

      if (newX >= 0 && newX < mazeRows && newY >= 0 && newY < mazeCols) {
        if (canMove(currentX, currentY, newX, newY, mazeToSolve)) {
          if (dist[newX][newY] == INF) {
            dist[newX][newY] = dist[currentX][currentY] + 1;
            q.push({newX, newY});
          }
        }
      }
    }
  }

  return dist;
}

std::vector<std::pair<int, int>> Maze::solveMaze(
    int startX, int startY, int endX, int endY,
    const std::vector<std::vector<int>>& mazeToSolve) {
  auto dist = calculateDistances(startX, startY, mazeToSolve);
  int mazeRows = mazeToSolve.size();
  int mazeCols = mazeToSolve[0].size();

  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  std::vector<std::pair<int, int>> path;

  int currentX = endX, currentY = endY;

  path.push_back({currentX, currentY});

  while (currentX != startX || currentY != startY) {
    for (const auto& [dx, dy] : directions) {
      int newX = currentX - dx;
      int newY = currentY - dy;

      if (newX >= 0 && newX < mazeRows && newY >= 0 && newY < mazeCols) {
        if (dist[newX][newY] == dist[currentX][currentY] - 1) {
          if (canMove(newX, newY, currentX, currentY, mazeToSolve)) {
            path.push_back({newX, newY});
            currentX = newX;
            currentY = newY;
            break;
          }
        }
      }
    }
  }

  std::reverse(path.begin(), path.end());
  return path;
}
