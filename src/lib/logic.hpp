#pragma once
#include "grid.hpp"
#include <fstream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

void ClearFile();
void PrintRecord(sf::RenderWindow& window, sf::Font font);
std::string GetCurrentDatetime();

class Logic {
public:
  int Difficulty(sf::RenderWindow &window, sf::Font font,
                 sf::Sprite background);
  int Game(int size, int blocksize, int vx, int vy, sf::RenderWindow &window,
           sf::Sprite background, sf::Font font, bool &win);
};
class Record {
public:
    std::string name;  // Имя игрока
    std::string turns; // Потраченное количество ходов
    std::string difficly; // Сложность игры
    std::string date;     // Время установления рекорда
    std::string time; // Время сессии
};

class Leaderboard {
private:
    std::vector<Record> records;

public:
    void addRecord(Record record);
    void saveTableToFile();
    int loadTableFromFile();
    void clean();
};