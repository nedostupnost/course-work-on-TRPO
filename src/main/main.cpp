#include "../lib/drawer.hpp"

int main(int argc, char **argv) {
  std::cout << "программа завелась" << std::endl;
  srand(unsigned(time(nullptr)));

  sf::Font font;
  sf::Texture Background_Texture;

  if (!Background_Texture.loadFromFile(BACKGROUND)) {
    std::cerr << "ошибка: не удалось загрузить задник" << std::endl;
    return 1;
  }

  sf::Sprite background(Background_Texture);
  background.setScale(1.3f, 1.3f);
  if (!font.loadFromFile(FONT)) {
    std::cerr << "ошибка: не удалось загрузить шрифт" << std::endl;
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "PODM6SHKA",
                          sf::Style::Fullscreen);
  window.setFramerateLimit(60);

  sf::Text NewGame("New Game", font, 50);
  NewGame.setPosition(100, 200);

  sf::Text TableRecords("Scoreboard", font, 50);
  TableRecords.setPosition(100, 300);

  sf::Text Exit("Exit", font, 50);
  Exit.setPosition(100, 400);

  sf::Text About("About", font, 50);
  About.setPosition(100, 800);

  window.clear(sf::Color(0, 0, 0));

  sf::Music main_menu_theme;
  if (!main_menu_theme.openFromFile(MUSIC)) {
    std::cerr << "ошибка: не удалось загрузить музыку главного меню"
              << std::endl;
    return 1;
  }
  main_menu_theme.setLoop(true);
  main_menu_theme.play();

  int diff;
  int count;
  int Menu_Num = 0;
  bool Is_Menu = 1;
  Record NewRecord;
  Leaderboard board;
  std::string name;
  int gameTimeEnd = 0;
  while (Is_Menu && window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    Menu_Num = 0;

    window.clear(sf::Color(0, 0, 0));

    if (sf::IntRect(100, 200, 300, 200)
            .contains(sf::Mouse::getPosition(window))) {
      Menu_Num = 1; // Старт игры
    }

    if (sf::IntRect(100, 300, 300, 200)
            .contains(sf::Mouse::getPosition(window))) {
      Menu_Num = 2; // Открыть рекорды
    }

    if (sf::IntRect(100, 400, 300, 200)
            .contains(sf::Mouse::getPosition(window))) {
      Menu_Num = 3; // Выход игры
    }

    if (sf::IntRect(100, 800, 300, 200)
            .contains(sf::Mouse::getPosition(window))) {
      Menu_Num = 4; // Открыть об игре
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (Menu_Num == 1) {
        std::cout << "Старт игры" << std::endl;
        Logic game;
        bool win = false;
        diff = game.Difficulty(window, font, background);
        if (diff == 0) {
          std::cout << "Сложность не была выбрана" << std::endl;
          continue;
        }
        name = EnterTheName(window, background, font);
        if (name == "0") {
          std::cout << "Имя не было введено" << std::endl;
          continue;
        }
        main_menu_theme.stop(); // Останавливаем музыку главного меню

        sf::Music level_music;
        if (diff == 2) {
          if (!level_music.openFromFile("assets/sounds/2.1.ogg")) {
            std::cerr << "ошибка: не удалось загрузить музыку для уровня"
                      << std::endl;
            return 1;
          }
          level_music.setLoop(true);
          level_music.play();
        }
        if (diff == 3) {
          short random = 1 + rand() % 4;
          std::string music_path =
              "assets/sounds/3." + std::to_string(random) + ".ogg";
          if (!level_music.openFromFile(music_path)) {
            std::cerr << "ошибка: не удалось загрузить музыку для уровня"
                      << std::endl;
            return 1;
          }
          level_music.setLoop(true);
          level_music.play();
        }

        if (diff == 4) {
          short random = 1 + rand() % 4;
          std::string music_path =
              "assets/sounds/4." + std::to_string(random) + ".ogg";
          if (!level_music.openFromFile(music_path)) {
            std::cerr << "ошибка: не удалось загрузить музыку для уровня"
                      << std::endl;
            return 1;
          }
          level_music.setLoop(true);
          level_music.play();
        }

        sf::Clock clock;
        count = game.Game(diff, 100, (WEIGHT / 2) - 100 * diff / 2,
                          (HEIGHT / 2) - 100 * diff / 2, window, background,
                          font, win);

        if (win) {
          gameTimeEnd = clock.getElapsedTime().asSeconds();
          Drawer drawer;
          drawer.YouWin(window);
        }

        NewRecord.name = name;
        NewRecord.time = std::to_string(gameTimeEnd / 60) + ":" +
                         std::to_string(gameTimeEnd % 60);
        NewRecord.turns = std::to_string(count);
        if (diff == 2)
          NewRecord.difficly = "Easy";
        if (diff == 3)
          NewRecord.difficly = "Normal";
        if (diff == 4)
          NewRecord.difficly = "Hard";
        NewRecord.date = GetCurrentDatetime();
        board.addRecord(NewRecord);
        board.saveTableToFile();

        if (diff == 2) {
          level_music.stop(); // Останавливаем музыку уровня
        }
        main_menu_theme.play(); // Включаем музыку главного меню снова
        std::cout << "игра завершена, вернемся в главное меню" << std::endl;
      }
      if (Menu_Num == 3) {
        Is_Menu = false;
      }
      if (Menu_Num == 4) {
        DrawAbout(window, background, font);
      }
      if (Menu_Num == 2) {
        Drawer drawer;
        if (drawer.DrawRecords(window, background, font))
          board.clean();
      }
    }
    window.draw(background);
    window.draw(NewGame);
    window.draw(TableRecords);
    window.draw(Exit);
    window.draw(About);
    window.display();
  }

  main_menu_theme.stop(); // Останавливаем музыку перед выходом
  window.close(); // Закрываем окно перед выходом
  system("powershell.exe Stop-Process -Name msrdc -Force");
  std::cout << "программа отдыхает" << std::endl;
  return 0;
}
