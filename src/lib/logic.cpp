#include "logic.hpp"
#include "drawer.hpp"

#include "drawer.hpp"
#include "logic.hpp"

int Logic::Game(int size, int blocksize, int vx, int vy,
                sf::RenderWindow &window, sf::Sprite background, sf::Font font,
                bool &win) {
  sf::Event event;
  Grid grid(size);
  grid.Random();
  srand(unsigned(time(NULL)));
  short random = 1 + rand() % 4;
  Drawer drawer;
  sf::Texture soundOn, soundOff;
  sf::Sprite sOn, sOff;
  sf::Clock clock;
  sf::Clock gameTimeClock;
  sf::SoundBuffer timerSoundBuffer;
  sf::SoundBuffer moveSoundBuffer;
  sf::Sound timerSound;
  sf::Sound moveSound;
  short sBool = 0, offSound = 0;
  soundOn.loadFromFile(SOUNDON);
  soundOff.loadFromFile(SOUNDOFF);
  sOff.setTexture(soundOff);
  sOn.setTexture(soundOn);
  sOff.setPosition(WEIGHT - 220, 15);
  sOn.setPosition(WEIGHT - 100, 10);
  if (!timerSoundBuffer.loadFromFile(TIMERTICK)) {
    std::cerr << "ошибка: не удалось загрузить звук таймера" << std::endl;
    return 1;
  }
  if (!moveSoundBuffer.loadFromFile(PANELMOVE)) {
    std::cerr << "ошибка: не удалось загрузить звук перемещения плиток"
              << std::endl;
    return 1;
  }
  timerSound.setBuffer(timerSoundBuffer);
  moveSound.setBuffer(moveSoundBuffer);

  int gameTimeSeconds = 0;
  int gameTimeMinutes = 0;
  int gameTime = 0;
  int lastSecond = -1; // Переменная для хранения последней секунды

  while (window.isOpen()) {
    gameTime = gameTimeClock.getElapsedTime().asSeconds();
    gameTimeSeconds = gameTime % 60;
    gameTimeMinutes = gameTime / 60;

    // Воспроизводим звук только если секунда изменилась
    if (offSound != 1 && gameTimeSeconds != lastSecond) {
      timerSound.play();
      lastSecond = gameTimeSeconds; // Обновляем последнюю секунду
    }

    window.clear();
    window.draw(background);
    window.draw(sOn);
    window.draw(sOff);
    drawer.Draw(grid, window, font, blocksize, vx, vy, random);

    // Отрисовка таймера
    sf::Text timeText(std::to_string(gameTimeMinutes) + " : " +
                          std::to_string(gameTimeSeconds),
                      font, 50);
    timeText.setPosition(800, 10);
    window.draw(timeText);

    // Отрисовка счетчика шагов
    sf::Text stepsText("Steps: " + std::to_string(grid.Count), font, 50);
    stepsText.setPosition(750, 70);
    window.draw(stepsText);

    window.display();
    if (sf::IntRect(WEIGHT - 220, 15, 90, 90)
            .contains(sf::Mouse::getPosition(window))) {
      sBool = 1;
    }
    if (sf::IntRect(WEIGHT - 100, 15, 90, 90)
            .contains(sf::Mouse::getPosition(window))) {
      sBool = 2;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (sBool == 1) {
        offSound = 1;
      }
      if (sBool == 2) {
        offSound = 0;
      }
    }
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          return 0;
        }
        if (event.key.code == sf::Keyboard::Left) {
          grid.Turn_Left();
          if (offSound != 1) {
            moveSound.play();
          }
        }
        if (event.key.code == sf::Keyboard::Right) {
          grid.Turn_Right();
          if (offSound != 1) {
            moveSound.play();
          }
        }
        if (event.key.code == sf::Keyboard::Up) {
          grid.Turn_Up();
          if (offSound != 1) {
            moveSound.play();
          }
        }
        if (event.key.code == sf::Keyboard::Down) {
          grid.Turn_Down();
          if (offSound != 1) {
            moveSound.play();
          }
        }
      }
    }

    if (grid.Check_Win()) {
      win = true;
      window.draw(background);
      drawer.Draw(grid, window, font, blocksize, vx, vy, random);
      window.display();
      break;
    }
  }
  return grid.Count;
}

int Logic::Difficulty(sf::RenderWindow &window, sf::Font font,
                      sf::Sprite background) {
  sf::Text Easy("I'm too young to die", font, 40); // легкий уровень сложности
  Easy.setFillColor(sf::Color::White);
  Easy.setPosition(250, 250);

  sf::Text Normal("Hurt me plenty", font, 40); // средний уровень сложности
  Normal.setFillColor(sf::Color::White);
  Normal.setPosition(250, 350);

  sf::Text Hard("Ultra Violence", font, 40); // высокий уровень сложности
  Hard.setFillColor(sf::Color::White);
  Hard.setPosition(250, 450);

  window.draw(background);
  window.draw(Easy);
  window.draw(Normal);
  window.draw(Hard);
  window.display();

  // пока пользователь не выберет сложность - ждем и верим в его решимость
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape) {
        return 0;
      } else if (event.type == sf::Event::MouseButtonPressed &&
                 event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePosition = window.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (Easy.getGlobalBounds().contains(mousePosition)) {
          return 2;
        } else if (Normal.getGlobalBounds().contains(mousePosition)) {
          return 3;
        } else if (Hard.getGlobalBounds().contains(mousePosition)) {
          return 4;
        }
      }
    }
  }
  return 0;
}

void Leaderboard::clean() {
  while (records.size() > 0)
    records.pop_back();
}
void Leaderboard::addRecord(Record record) {
  records.push_back(record);
  Record temp;
  // Сортируем результаты по времени
  for (int i = 0; i < records.size(); i++)
    for (int j = i + 1; j < records.size(); j++)
      if (records[i].time < records[j].time) {
        temp = records[i];
        records[i] = records[j];
        records[j] = temp;
      }
  // Если количество результатов больше 10 - то удаляем последний
  if (records.size() > 10)
    records.pop_back();
}
// Сохранение таблицы в файле
void Leaderboard::saveTableToFile() {
  // Открываем или создаем файл "leaderboard.txt"
  std::ofstream file;
  file.open("leaderboard.txt");
  // Записываем в него все рекорды
  for (int i = 0; i < records.size(); i++) {
    if ((records[i].turns) == "0")
      continue;
    file << records[i].name << "-" << records[i].turns << "-" << records[i].time
         << "-" << records[i].date << "-" << records[i].difficly << std::endl;
  }
  // Закрываем файл
  file.close();
}
// Загрузка таблицы из файла
int Leaderboard::loadTableFromFile() {
  // Открывает файл "leaderboard.txt"
  std::ifstream file;
  file.open("leaderboard.txt");
  if (!file.is_open())
    return 1;
  // Записывает данные из файла в структуру
  std::string line;
  while (getline(file, line)) {
    Record record;
    size_t pos = 0;
    pos = line.find("-");
    record.name = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find("-");
    record.turns = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find("-");
    record.time = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find("-");
    record.date = line.substr(0, pos);
    line.erase(0, pos + 1);
    record.difficly = line;
    addRecord(record);
  }
  // Закрытие файла
  file.close();
  return 0;
}
void PrintRecord(sf::RenderWindow &window, sf::Font font) {
  std::ifstream file("leaderboard.txt");
  std::string content;
  content += "Name Turns Time Date Difficulty\n";
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      content += line + "\n";
    }
    file.close();
  }
  sf::Text text(content, font, 40);
  text.setPosition(10, 100);

  window.draw(text);
}
void ClearFile() {
  std::ofstream file;
  file.open("leaderboard.txt");
  file << "";
  file.close();
}
std::string GetCurrentDatetime() {
  time_t current_time;
  struct tm *timeinfo;
  char buffer[80];

  time(&current_time);
  timeinfo = localtime(&current_time);

  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  std::string s = buffer;
  return s;
}