#include <ctime>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../src/lib/drawer.hpp"
#include "../src/lib/grid.hpp"
#include "../thirdparty/ctest.h"

CTEST(GridTestSuite, DefaultConstructorTest) {
  Grid grid(3);

  ASSERT_EQUAL(grid.Size, 3);
  ASSERT_TRUE(grid.Check_Win());
}

CTEST(GridTestSuite, LeftTest) {
  Grid grid(3);
  // Проверяем, что начальное положение ячеек находится в выигрышной позиции
  ASSERT_TRUE(grid.Check_Win());
  // Делаем несколько ходов влево
  grid.Turn_Left();
  grid.Turn_Left();
  grid.Turn_Left();
  grid.Turn_Left();
  // Проверяем, что невозможно сделать ход влево, когда 0-я ячейка находится
  // на крайней левой позиции
  ASSERT_EQUAL(grid.Turn_Left(), 1);
}

CTEST(GridTestSuite, RightTest) {
  Grid grid(3);
  // Проверяем, что начальное положение ячеек находится в выигрышной позиции
  ASSERT_TRUE(grid.Check_Win());
  // Делаем несколько ходов вправо
  grid.Turn_Right();
  grid.Turn_Right();
  grid.Turn_Right();
  // Проверяем, что невозможно сделать ход вправо, когда 0-я ячейка находится
  // на крайней правой позиции
  ASSERT_EQUAL(grid.Turn_Right(), 1);
}

CTEST(GridTestSuite, UpTest) {
  Grid grid(3);
  // Проверяем, что начальное положение ячеек находится в выигрышной позиции
  ASSERT_TRUE(grid.Check_Win());
  // Делаем несколько ходов вверх
  grid.Turn_Up();
  grid.Turn_Up();
  grid.Turn_Up();
  // Проверяем, что невозможно сделать ход вверх, когда 0-я ячейка находится
  // на крайней верхней позиции
  ASSERT_EQUAL(grid.Turn_Up(), 1);
}

CTEST(GridTestSuite, DownTest) {
  Grid grid(3);
  // Проверяем, что начальное положение ячеек находится в выигрышной позиции
  ASSERT_TRUE(grid.Check_Win());
  // Делаем несколько ходов вниз
  grid.Turn_Down();
  grid.Turn_Down();
  grid.Turn_Down();
  // Проверяем, что невозможно сделать ход вниз, когда 0-я ячейка находится на
  // крайней нижней позиции
  ASSERT_EQUAL(grid.Turn_Down(), 1);
}

CTEST(RecordsTableTest, AddRecordTest) {
  Leaderboard table;
  Record record1 = {"John", "5", "1000", "2022-10-31", "hard"};
  table.addRecord(record1);
  ASSERT_EQUAL(table.loadTableFromFile(), 0);
}

CTEST(RecordsTableTest, SaveTableToFileTest) {
  Leaderboard table;
  Record record1 = {"John", "5", "1000", "2022-10-31", "hard"};
  table.addRecord(record1);
  ASSERT_EQUAL(table.loadTableFromFile(), 0);
  table.saveTableToFile();
  ASSERT_EQUAL(table.loadTableFromFile(), 0);
}

CTEST(RecordsTableTest, LoadTableFromFileTest) {
  Leaderboard table;
  Record record1 = {"John", "5", "1000", "2022-10-31", "hard"};
  Record record2 = {"Anna", "7", "800", "2022-11-01", "medium"};
  table.addRecord(record1);
  table.addRecord(record2);
  ASSERT_EQUAL(table.loadTableFromFile(), 0);
}

CTEST(GetCurrentDatetimeTest, TestResultLength) {
  std::string result = GetCurrentDatetime();
  ASSERT_EQUAL(result.length(), 19);
}

CTEST(GetCurrentDatetimeTest, TestStringFormat) {
  std::string result = GetCurrentDatetime();
  ASSERT_EQUAL(result[4], '-');
  ASSERT_EQUAL(result[7], '-');
  ASSERT_EQUAL(result[10], ' ');
  ASSERT_EQUAL(result[13], ':');
  ASSERT_EQUAL(result[16], ':');
}