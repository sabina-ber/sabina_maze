#include <QApplication>

#include "controller/mazecontroller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MazeController controller;
  return a.exec();
}
