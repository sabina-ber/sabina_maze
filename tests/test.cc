#include <gtest/gtest.h>

#include "../model/cell.h"
#include "../model/maze.h"
#include "../model/mazegenerator.h"

TEST(MazeTest, ConstructorTest) {
  Maze maze(5, 5);
  EXPECT_EQ(maze.getRows(), 5);
  EXPECT_EQ(maze.getCols(), 5);
}

TEST(MazeTest, LoadFromFileTest) {
  Maze maze("../mazes/test.txt");
  ASSERT_EQ(maze.getRows(), 4);
  ASSERT_EQ(maze.getCols(), 4);
}

TEST(MazeTest, GetCellTest) {
  Maze maze(5, 5);
  EXPECT_EQ(maze.getCell(0, 0), 0);
}

TEST(MazeGenerator, GenerateMaze) {
  Maze m(5, 5);
  MazeGenerator gen(m);
  EXPECT_NO_THROW(gen.generate());
}

TEST(MazeTest, CellManipulationTest) {
  Maze maze(5, 5);
  maze.setCell(1, 1, 1);
  ASSERT_EQ(maze.getCell(1, 1), 1);
}

TEST(MazeTest, FindTheWayTest) {
  Maze maze("../mazes/test_maze.txt");

  auto path = maze.solveMaze(0, 0, 7, 9, maze.getMaze());

  std::vector<std::pair<int, int>> expectedPath = {
      {0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
      {5, 2}, {5, 3}, {6, 3}, {6, 4}, {7, 4}, {8, 4}, {9, 4},
      {9, 5}, {9, 6}, {9, 7}, {9, 8}, {9, 9}, {8, 9}, {7, 9}};

  ASSERT_EQ(path, expectedPath);
}

TEST(MazeTest, TestSaveAndLoad) {
  // Arrange
  std::string originalFilePath = "../mazes/saveTest.txt";
  std::string tempFilePath = "../mazes/temp_maze.txt";

  Maze originalMaze(originalFilePath);

  // Act
  originalMaze.saveToFile(tempFilePath);

  Maze newMaze(tempFilePath);

  // Assert
  ASSERT_EQ(originalMaze.getRows(), newMaze.getRows());
  ASSERT_EQ(originalMaze.getCols(), newMaze.getCols());

  for (int i = 0; i < originalMaze.getRows(); ++i) {
    for (int j = 0; j < originalMaze.getCols(); ++j) {
      ASSERT_EQ(originalMaze.getCell(i, j), newMaze.getCell(i, j));
    }
  }

  // Clean up: удаляем временный файл
  std::remove(tempFilePath.c_str());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
