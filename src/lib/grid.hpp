#pragma once
#include "links.hpp"
#include <SFML/Window/Mouse.hpp>
#include <vector>

class Grid {
private:
  std::vector<int> Win_Grid; // выиграшная позиция поля
  int Null_Index;            // нулевое значение поля

public:
  int Count = 0; // счетчик шагов пользователя
  int Size;      // размер игрового поля
  std::vector<int> Current_Grid; // игровое поле
  Grid(int current_size);        // характеристики поля
  bool Check_Win(); // проверка на правильную сборку поля
  void Random();    // рандомизация поля
  int Turn_Left();  // сдвиг ячейки налево
  int Turn_Right(); // сдвич ячейки вправо
  int Turn_Up();    // сдвич ячейки вверх
  int Turn_Down();  // сдвик ячейки вверх
};