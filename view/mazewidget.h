/**
 * @file mazewidget.h
 * @brief MazeWidget class to render and interact with the maze.
 */

#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QPaintEvent>
#include <QWidget>
#include <utility>
#include <vector>

/**
 * @class MazeWidget
 * @brief Class for rendering and interacting with the maze.
 *
 * This class is responsible for rendering the maze, responding to mouse events,
 * and providing options to find paths and update maze data.
 */
class MazeWidget : public QWidget {
  Q_OBJECT

 public:
  /**
   * @brief Default constructor.
   */
  explicit MazeWidget(QWidget *parent = nullptr);
  /**
   * @brief Constructor with initial maze data.
   * @param initialMazeData 2D vector representing the initial maze data.
   * @param parent Parent QWidget.
   */
  MazeWidget(const std::vector<std::vector<int>> &initialMazeData,
             QWidget *parent = nullptr);
  /**
   * @brief Paint event to draw the maze and the solution if applicable.
   * @param event QPaintEvent object.
   */
  void paintEvent(QPaintEvent *event) override;
  /**
   * @brief Mouse press event to determine the starting and ending points for
   * finding a path.
   * @param event QMouseEvent object.
   */
  void mousePressEvent(QMouseEvent *event) override;
  /**
   * @brief Update maze data and redraw.
   * @param newMazeData 2D vector containing the new maze data.
   */
  void updateMaze(const std::vector<std::vector<int>> &newMazeData);
  /**
   * @brief Update the path solution.
   * @param newSolution Vector of coordinates for the solution path.
   */
  void updateSolution(const std::vector<std::pair<int, int>> &newSolution);
  void drawSolution(QPainter &painter, int cellSize);
  /**
   * @brief Get the current maze data.
   * @return 2D vector containing the current maze data.
   */
  std::vector<std::vector<int>> getMaze() const;
  /**
   * @brief Sets whether the solution should be drawn.
   * @param value Boolean value to set.
   */
  void setShouldDrawSolution(bool value);

 public slots:
  void onFindPathClicked(bool isFinding);

 signals:
  void startCoordinatesSelected(int x, int y);
  void endCoordinatesSelected(int x, int y);

 private:
  std::vector<std::vector<int>> mazeData;
  std::vector<std::pair<int, int>> solution;
  bool isFindingPath = false;
  bool shouldDrawSolution = false;

  bool firstClickDone = false;
  int firstClickX = -1;
  int firstClickY = -1;
  int secondClickX = -1;
  int secondClickY = -1;
};

#endif  // MAZEWIDGET_H
