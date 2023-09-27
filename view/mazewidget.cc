#include "mazewidget.h"

#include <QMouseEvent>
#include <QPainter>

MazeWidget::MazeWidget(QWidget *parent) : QWidget(parent) {
  mazeData = {
      {15, 15, 15, 15},
      {15, 15, 15, 15},
      {15, 15, 15, 15},
      {15, 15, 15, 15},
  };
}

MazeWidget::MazeWidget(const std::vector<std::vector<int>> &initialMazeData,
                       QWidget *parent)
    : QWidget(parent), mazeData(initialMazeData) {}

void MazeWidget::paintEvent(QPaintEvent * /* event */) {
  QPainter painter(this);
  int cellSize = std::min(this->width() / mazeData[0].size(),
                          this->height() / mazeData.size());

  for (std::vector<std::vector<int>>::size_type i = 0; i < mazeData.size();
       ++i) {
    for (std::vector<std::vector<int>>::size_type j = 0; j < mazeData[i].size();
         ++j) {
      int x = j * cellSize;
      int y = i * cellSize;
      int cell = mazeData[i][j];

      if (cell & 1) {
        painter.drawLine(x, y, x + cellSize, y);
      }
      if (cell & 2) {
        painter.drawLine(x + cellSize, y, x + cellSize, y + cellSize);
      }
      if (cell & 4) {
        painter.drawLine(x, y + cellSize, x + cellSize, y + cellSize);
      }
      if (cell & 8) {
        painter.drawLine(x, y, x, y + cellSize);
      }
    }
  }
  if (shouldDrawSolution) {
    drawSolution(painter, cellSize);
  }
}

void MazeWidget::updateMaze(const std::vector<std::vector<int>> &newMazeData) {
  shouldDrawSolution = false;
  solution.clear();
  repaint();
  mazeData = newMazeData;
  repaint();
}

void MazeWidget::updateSolution(
    const std::vector<std::pair<int, int>> &newSolution) {
  solution = newSolution;
  repaint();
}

void MazeWidget::onFindPathClicked(bool isFinding) {
  shouldDrawSolution = false;
  solution.clear();
  repaint();

  isFindingPath = isFinding;
}

void MazeWidget::mousePressEvent(QMouseEvent *event) {
  if (isFindingPath) {
    int cellSize = std::min(this->width() / mazeData[0].size(),
                            this->height() / mazeData.size());
    int cellX = event->pos().x() / cellSize;
    int cellY = event->pos().y() / cellSize;

    if (!firstClickDone) {
      firstClickY = cellX;
      firstClickX = cellY;
      firstClickDone = true;
      emit startCoordinatesSelected(firstClickX, firstClickY);
    } else {
      secondClickY = cellX;
      secondClickX = cellY;
      firstClickDone = false;
      isFindingPath = false;

      emit endCoordinatesSelected(secondClickX, secondClickY);
    }
  }
}

std::vector<std::vector<int>> MazeWidget::getMaze() const { return mazeData; }

void MazeWidget::setShouldDrawSolution(bool value) {
  shouldDrawSolution = value;
  repaint();
}

void MazeWidget::drawSolution(QPainter &painter, int cellSize) {
  painter.setPen(QPen(Qt::red, 2));

  for (size_t i = 1; i < solution.size(); ++i) {
    int prevX = solution[i - 1].first;
    int prevY = solution[i - 1].second;
    int curX = solution[i].first;
    int curY = solution[i].second;

    int x1 = prevY * cellSize + cellSize / 2;
    int y1 = prevX * cellSize + cellSize / 2;

    int x2 = curY * cellSize + cellSize / 2;
    int y2 = curX * cellSize + cellSize / 2;

    painter.drawLine(x1, y1, x2, y2);
  }
}
