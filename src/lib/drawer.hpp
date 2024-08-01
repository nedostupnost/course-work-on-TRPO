#pragma once
#include "links.hpp"
#include "logic.hpp"

class Drawer {
public:
  void Draw(Grid grid, sf::RenderWindow &window, sf::Font font, int blocksize,
            int vx, int vy, short r);
  void YouWin(sf::RenderWindow &window);
  int DrawRecords(sf::RenderWindow &window, sf::Sprite background,
                  sf::Font font);
};

std::string EnterTheName(sf::RenderWindow &window, sf::Sprite background,
                         sf::Font font);
void DrawAbout(sf::RenderWindow& window, sf::Sprite background, sf::Font font);