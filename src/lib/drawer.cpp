#include "drawer.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <string>

void Drawer::Draw(Grid grid, sf::RenderWindow &window, sf::Font font,
                  int blocksize, int vx, int vy, short r) {
  for (int i = 0; i < grid.Size * grid.Size; ++i) {
    sf::Sprite block;
    sf::Texture image;
    std::string path = "assets/pics/" + std::to_string(grid.Size) + "x" +
                       std::to_string(grid.Size) + "/" + std::to_string(r) +
                       "/" + std::to_string(grid.Current_Grid[i]) + ".png";
    if (!image.loadFromFile(path)) {
      continue; // ошибка
    }
    block.setTexture(image);
    block.setPosition(vx + (i % grid.Size) * blocksize,
                      vy + (int(i / grid.Size)) * blocksize);
    window.draw(block);
  }
}

void Drawer::YouWin(sf::RenderWindow &window) {
  sf::Texture YouWinTexture;
  if (!YouWinTexture.loadFromFile(YOUWIN)) {
    return; // ошибка
  }
  sf::Sprite YouWinSprite;
  YouWinSprite.setTexture(YouWinTexture);
  YouWinSprite.setScale(2.0f, 2.0f);
  YouWinSprite.setPosition(int(WEIGHT / 2 - 200), 0);
  window.draw(YouWinSprite);
  window.display();
  sf::sleep(sf::seconds(2));
}

std::string EnterTheName(sf::RenderWindow &window, sf::Sprite background,
                         sf::Font font) {
  sf::RectangleShape Field;
  Field.setFillColor(sf::Color::Black);
  Field.setSize(sf::Vector2f(500, 60));
  Field.setPosition(625, 405);

  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::White);
  text.setPosition(660, 400);

  // Кнопка
  sf::Text EnterTheName;
  EnterTheName.setFont(font);
  EnterTheName.setString("Enter Your Name");
  EnterTheName.setFillColor(sf::Color::White);
  EnterTheName.setPosition(int(WEIGHT / 2 - 200), 100);
  EnterTheName.setCharacterSize(50);

  std::string input;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.key.code == sf::Keyboard::Escape)
        return "0";
      else if (event.key.code == sf::Keyboard::Enter &&
               input.size() > 0) // ввести имя
        return input;
      else if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) // проверка на символы ASCII
        {
          if (event.text.unicode == '\b' && input.size() > 0) // пробелы
          {
            input.pop_back();
          }

          else if (event.text.unicode != '\b' && input.size() < 20) {
            input += static_cast<char>(event.text.unicode);
          }
          text.setString(input);
        }
      }
    }

    window.clear();
    window.draw(background);
    window.draw(Field);
    window.draw(text);
    window.draw(EnterTheName);
    window.display();
  }

  return input;
}

int Drawer::DrawRecords(sf::RenderWindow &window, sf::Sprite background,
                        sf::Font font) {
  sf::Text Clear("Clear", font, 40);
  Clear.setFillColor(sf::Color::White);
  Clear.setPosition(0, 700);
  while (window.isOpen()) {
    sf::Event event;
    window.clear();
    window.draw(background);
    PrintRecord(window, font);
    window.draw(Clear);
    window.display();
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.key.code == sf::Keyboard::Escape)
        return 0;
      else if (event.type == sf::Event::MouseButtonPressed) {
        // Проверяем на какую кнопку нажал пользователь
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mousePosition = window.mapPixelToCoords(
              sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
          if (Clear.getGlobalBounds().contains(mousePosition)) {
            ClearFile();
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

void DrawAbout(sf::RenderWindow &window, sf::Sprite background, sf::Font font) {
  while ((window.isOpen())) {
    sf::Event event;
    while ((window.pollEvent(event))) {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.key.code == sf::Keyboard::Escape) {
        return;
      }
    }
    sf::Text about(
        L"Цель игры:\n\nВаша задача – перемещать квадраты\nна поле "
        "размером от 2x2 до 4x4,\nчтобы организовать их в правильном "
        "порядке\n\nКак играть:\n\nДля перемещения "
        "квадратов\nиспользуйте стрелки на клавиатуре:\nВверх: Квадрат "
        "переместится вверх\nВлево: Квадрат переместится влево\nВправо: "
        "Квадрат переместится вправо\nВниз: Квадрат переместиться "
        "вниз\n\nВаша цель:\n\nРасположить квадраты в "
        "правильном порядке",
        font, 30);
    about.setPosition(200, 150);
    window.draw(background);
    window.draw(about);
    window.display();
  }
}
