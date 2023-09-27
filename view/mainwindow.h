#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class MazeWidget;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  int getRows();
  int getCols();

  int getStartX();
  int getStartY();
  int getEndX();
  int getEndY();

  void updateStartCoordinates(int x, int y);
  void updateEndCoordinates(int x, int y);

  MazeWidget *getMazeWidget() const { return mazeWidget; }

 signals:
  void loadMazeClicked(const QString &fileName);
  void constructMazeClicked(int rows, int cols);
  void findPathClicked(bool isFindingPath);
  void saveMazeClicked(const QString &fileName);
  void showTheWayClicked(int startX, int startY, int endX, int endY,
                         const std::vector<std::vector<int>> &maze);

 public slots:
  void loadMaze();
  void constructMaze();
  void findPath();
  void saveMaze();
  void showTheWay();

 private:
  QPushButton *loadMazeButton;
  QPushButton *constructMazeButton;
  QPushButton *findPathButton;
  QLineEdit *lineEditForRows;
  QLineEdit *lineEditForCols;
  QWidget *centralWidget;
  MazeWidget *mazeWidget;
  QPushButton *saveMazeButton;
  QSpinBox *startXSpinBox;
  QSpinBox *startYSpinBox;
  QSpinBox *endXSpinBox;
  QSpinBox *endYSpinBox;
  QSpinBox *rowsSpinBox;
  QSpinBox *colsSpinBox;
  QPushButton *showTheWayButton;

  bool isFindingPath = false;
};

#endif  // MAINWINDOW_H
