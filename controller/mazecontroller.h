#ifndef MAZECONTROLLER_H
#define MAZECONTROLLER_H

#include <QObject>
#include <string>

#include "../model/cell.h"
#include "../model/mazemodel.h"
#include "../view/mainwindow.h"
#include "../view/mazewidget.h"

class MazeModel;

class MazeController : public QObject {
  Q_OBJECT

 public:
  MazeController();
  void loadMazeFromFile(const std::string &filePath);
  void generateMaze(int rows, int cols);
  // void solveMaze(int startX, int startY, int endX, int endY);
  void saveMazeToFile(const std::string &filePath);
  void onSaveMazeGenerated();
  void ShowTheWayClicked(int startX, int startY, int endX, int endY,
                         const std::vector<std::vector<int>> &maze);

 public slots:
  void loadMazeClicked(const QString &fileName);
  void generateMazeClicked(int rows, int cols);
  // void solveMazeClicked();
  void onMazeChanged();
  void onMazeGenerated();
  void onMazeSolved(std::vector<std::pair<int, int>>);
  void onSaveMazeClicked(const QString &fileName);
  void onShowTheWayClicked(int startX, int startY, int endX, int endY,
                           const std::vector<std::vector<int>> &maze);

 private:
  MazeModel *model;
  MainWindow w;
};

#endif  // MAZECONTROLLER_H
