#include "grid.hpp"

Grid::Grid(int current_size) {
  for (int i = 0; i < current_size * current_size; i++) {
    Win_Grid.push_back(i + 1);
    Current_Grid.push_back(i + 1);
  }
  Win_Grid[current_size * current_size - 1] =
      Current_Grid[current_size * current_size - 1] = 0;
  Null_Index = current_size * current_size - 1;
  Size = current_size;
  Count = 0;
}

bool Grid::Check_Win() {
  for (int i = 0; i < Size * Size; i++) {
    if (Win_Grid[i] != Current_Grid[i]) {
      return false;
    }
  }
  return true;
}

int Grid::Turn_Left() {
  int temp;
  if (Null_Index % Size != 0) {
    temp = Current_Grid[Null_Index - 1];
    Current_Grid[Null_Index - 1] = 0;
    Current_Grid[Null_Index] = temp;
    Null_Index--;
    Count++;
    return 0;
  }
  return 1;
}

int Grid::Turn_Right() {
  int temp;
  if (Null_Index % Size != Size - 1) {
    temp = Current_Grid[Null_Index + 1];
    Current_Grid[Null_Index + 1] = 0;
    Current_Grid[Null_Index] = temp;
    Null_Index++;
    Count++;
    return 0;
  }
  return 1;
}

int Grid::Turn_Down() {
  int temp;
  if (Null_Index < Size * (Size - 1)) {
    temp = Current_Grid[Null_Index + Size];
    Current_Grid[Null_Index + Size] = 0;
    Current_Grid[Null_Index] = temp;
    Null_Index += Size;
    Count++;
    return 0;
  }
  return 1;
}
int Grid::Turn_Up() {
  int temp;
  if (Null_Index >= Size) {
    temp = Current_Grid[Null_Index - Size];
    Current_Grid[Null_Index - Size] = 0;
    Current_Grid[Null_Index] = temp;
    Null_Index -= Size;
    Count++;
    return 0;
  }
  return 1;
}

void Grid::Random() { // алгоритм Фишера-Йетса
  srand(time(NULL));
  for (int i = Size * Size - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    if (Current_Grid[i] == 0) {
      Null_Index = j;
    } else if (Current_Grid[j] == 0) {
      Null_Index = i;
    }
    std::swap(Current_Grid[i], Current_Grid[j]);
  }
}
