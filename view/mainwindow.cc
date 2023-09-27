#include "mainwindow.h"

#include "mazewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  centralWidget = new QWidget(this);
  QGridLayout *gridLayout = new QGridLayout();
  QVBoxLayout *buttonLayout = new QVBoxLayout();

  const QSize buttonSize(110, 30);

  loadMazeButton = new QPushButton("Load Maze", this);
  loadMazeButton->setFixedSize(buttonSize);
  connect(loadMazeButton, &QPushButton::released, this, &MainWindow::loadMaze);
  buttonLayout->addWidget(loadMazeButton);

  constructMazeButton = new QPushButton("Generate maze", this);
  constructMazeButton->setFixedSize(buttonSize);
  connect(constructMazeButton, &QPushButton::released, this,
          &MainWindow::constructMaze);
  buttonLayout->addWidget(constructMazeButton);

  QHBoxLayout *rowsColsLayout = new QHBoxLayout();
  rowsSpinBox = new QSpinBox(this);
  rowsSpinBox->setMinimum(0);
  rowsSpinBox->setMaximum(50);
  rowsSpinBox->setValue(10);

  colsSpinBox = new QSpinBox(this);
  colsSpinBox->setMinimum(0);
  colsSpinBox->setMaximum(50);
  colsSpinBox->setValue(10);

  rowsColsLayout->addWidget(new QLabel("Rows:", this));
  rowsColsLayout->addWidget(rowsSpinBox);
  rowsColsLayout->addWidget(new QLabel("Cols:", this));
  rowsColsLayout->addWidget(colsSpinBox);

  buttonLayout->addLayout(rowsColsLayout);

  saveMazeButton = new QPushButton("Save Maze", this);
  saveMazeButton->setFixedSize(buttonSize);
  connect(saveMazeButton, &QPushButton::released, this, &MainWindow::saveMaze);
  buttonLayout->addWidget(saveMazeButton);

  findPathButton = new QPushButton("Find Path", this);
  findPathButton->setFixedSize(buttonSize);
  connect(findPathButton, &QPushButton::released, this, &MainWindow::findPath);
  buttonLayout->addWidget(findPathButton);

  showTheWayButton = new QPushButton("Show the Way", this);
  showTheWayButton->setFixedSize(buttonSize);
  connect(showTheWayButton, &QPushButton::released, this,
          &MainWindow::showTheWay);
  buttonLayout->addWidget(showTheWayButton);

  QHBoxLayout *startLayout = new QHBoxLayout();
  QHBoxLayout *endLayout = new QHBoxLayout();

  startXSpinBox = new QSpinBox(this);
  startXSpinBox->setMinimum(0);
  startXSpinBox->setMaximum(50);
  startXSpinBox->setValue(0);

  startYSpinBox = new QSpinBox(this);
  startYSpinBox->setMinimum(0);
  startYSpinBox->setMaximum(50);
  startYSpinBox->setValue(0);

  endXSpinBox = new QSpinBox(this);
  endXSpinBox->setMinimum(0);
  endXSpinBox->setMaximum(50);
  endXSpinBox->setValue(0);

  endYSpinBox = new QSpinBox(this);
  endYSpinBox->setMinimum(0);
  endYSpinBox->setMaximum(50);
  endYSpinBox->setValue(0);

  startLayout->addWidget(new QLabel("Start X:", this));
  startLayout->addWidget(startXSpinBox);
  startLayout->addWidget(new QLabel("Start Y:", this));
  startLayout->addWidget(startYSpinBox);

  endLayout->addWidget(new QLabel("End X:", this));
  endLayout->addWidget(endXSpinBox);
  endLayout->addWidget(new QLabel("End Y:", this));
  endLayout->addWidget(endYSpinBox);

  buttonLayout->addLayout(startLayout);
  buttonLayout->addLayout(endLayout);

  mazeWidget = new MazeWidget(this);
  mazeWidget->setMinimumSize(360, 360);
  mazeWidget->setMaximumSize(720, 720);
  mazeWidget->setStyleSheet("border: 1px solid blue;");

  gridLayout->addLayout(buttonLayout, 0, 0);
  gridLayout->addWidget(mazeWidget, 0, 1);

  gridLayout->setColumnStretch(0, 1);
  gridLayout->setColumnStretch(1, 3);

  centralWidget->setLayout(gridLayout);
  setCentralWidget(centralWidget);

  connect(mazeWidget, &MazeWidget::startCoordinatesSelected, this,
          &MainWindow::updateStartCoordinates);
  connect(mazeWidget, &MazeWidget::endCoordinatesSelected, this,
          &MainWindow::updateEndCoordinates);
  connect(this, &MainWindow::findPathClicked, mazeWidget,
          &MazeWidget::onFindPathClicked);
}

MainWindow::~MainWindow() {
  delete loadMazeButton;
  delete constructMazeButton;
  delete findPathButton;
  delete startXSpinBox;
  delete startYSpinBox;
  delete endXSpinBox;
  delete endYSpinBox;
  delete saveMazeButton;
  delete rowsSpinBox;
  delete colsSpinBox;
  delete showTheWayButton;
  delete mazeWidget;
}

void MainWindow::loadMaze() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open Maze File", "", "Maze Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    emit loadMazeClicked(fileName);
  }
}

void MainWindow::constructMaze() {
  int rows = rowsSpinBox->value();
  int cols = colsSpinBox->value();
  emit constructMazeClicked(rows, cols);
}

void MainWindow::findPath() {
  isFindingPath = true;
  QMessageBox::warning(this, "PLAY", "Choose the entrance point.");
  emit findPathClicked(isFindingPath);  // Emit signal
}

int MainWindow::getRows() { return lineEditForRows->text().toInt(); }

int MainWindow::getCols() { return lineEditForCols->text().toInt(); }

void MainWindow::saveMaze() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save Maze File", "", "Maze Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    emit saveMazeClicked(fileName);
  }
}

void MainWindow::updateStartCoordinates(int x, int y) {
  startXSpinBox->setValue(x);
  startYSpinBox->setValue(y);
}

void MainWindow::updateEndCoordinates(int x, int y) {
  endXSpinBox->setValue(x);
  endYSpinBox->setValue(y);
}

void MainWindow::showTheWay() {
  int startX = startXSpinBox->value();
  int startY = startYSpinBox->value();
  int endX = endXSpinBox->value();
  int endY = endYSpinBox->value();
  std::vector<std::vector<int>> maze = mazeWidget->getMaze();
  emit showTheWayClicked(startX, startY, endX, endY, maze);
}
