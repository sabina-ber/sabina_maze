#include "mazecontroller.h"

MazeController::MazeController() : QObject() {
  model = new MazeModel();
  w.show();

  connect(&w, &MainWindow::loadMazeClicked, this,
          &MazeController::loadMazeClicked);
  connect(&w, &MainWindow::constructMazeClicked, this,
          &MazeController::generateMazeClicked);
  connect(model, &MazeModel::mazeChanged, this, &MazeController::onMazeChanged);
  connect(model, &MazeModel::mazeGenerated, this,
          &MazeController::onMazeGenerated);
  connect(model, &MazeModel::mazeSolved, this, &MazeController::onMazeSolved);
  connect(&w, &MainWindow::saveMazeClicked, this,
          &MazeController::onSaveMazeClicked);
  connect(&w, &MainWindow::showTheWayClicked, this,
          &MazeController::onShowTheWayClicked);
}

void MazeController::loadMazeClicked(const QString &fileName) {
  loadMazeFromFile(fileName.toStdString());
}

void MazeController::onSaveMazeClicked(const QString &fileName) {
  saveMazeToFile(fileName.toStdString());
}

void MazeController::generateMazeClicked(int rows, int cols) {
  generateMaze(rows, cols);
}

void MazeController::onMazeGenerated() {
  w.getMazeWidget()->updateMaze(model->getMaze());
}

void MazeController::loadMazeFromFile(const std::string &filePath) {
  model->loadFromFile(filePath);
}

void MazeController::generateMaze(int rows, int cols) {
  model->generate(rows, cols);
}

void MazeController::saveMazeToFile(const std::string &filePath) {
  model->save(filePath);
}

void MazeController::onMazeChanged() {
  w.getMazeWidget()->updateMaze(model->getMaze());
}

void MazeController::onMazeSolved(std::vector<std::pair<int, int>> mazeSolve) {
  w.getMazeWidget()->updateSolution(mazeSolve);
  w.getMazeWidget()->setShouldDrawSolution(true);
}

void MazeController::onShowTheWayClicked(
    int startX, int startY, int endX, int endY,
    const std::vector<std::vector<int>> &maze) {
  model->solve(startX, startY, endX, endY, maze);
}
