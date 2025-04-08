#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#if defined(__linux__)
#include <cctype>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#elif defined(__WIN32) || defined(WIN64)

#endif

#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class Game {
public:
  Game() {
    m_gameResPath = std::filesystem::current_path().remove_filename();
    m_gameResPath /= "res";
    m_wordsFileCountOfLines =
        getCountOfLines(m_gameResPath.string() + std::string("/words.txt"));
    m_randWordIndex = std::rand() % m_wordsFileCountOfLines + 1;
    m_guessedWord = parseFile(m_randWordIndex);

    m_famousWord = std::string(m_guessedWord.size(), '#');
    m_theGallows = "########## \n"
                   " #/     |  \n"
                   " #         \n"
                   " #         \n"
                   " #         \n"
                   " #         \n"
                   " #           ";
    m_attemptsCount = 0;
  }

  void play();

private:
  const unsigned getCountOfLines(const std::string pathToFile);
  const std::string parseFile(const unsigned short lineNum);

  void clearTerminal();
  void gameLoop();
  void updateGallows();

private:
  std::filesystem::path m_gameResPath;

  std::string m_guessedWord;
  std::string m_famousWord;
  std::string m_enteredLetters;
  std::string m_theGallows;

  unsigned m_randWordIndex;
  unsigned m_attemptsCount;
  unsigned m_wordsFileCountOfLines;
};

void Game::clearTerminal() {
#if defined(__linux__)
  std::system("clear");
#elif defined(_WIN64) || defined(_WIN32)
  std::system("cls");
#endif
}

// void getChar(char &letter) {
// #if defined(__linux__)
//   struct termios tNew, tOld;
//   tcgetattr(STDIN_FILENO, &tOld);
//   tNew = tOld;
//   tNew.c_lflag &= ~(ICANON);
//   tcsetattr(STDIN_FILENO, TCSANOW, &tNew);
//   letter = getchar();
//
//   tcsetattr(STDIN_FILENO, TCSANOW, &tOld);
// #elif defined(__WIN64) || defined(__WIN32)
//   letter = _getch();
// #endif
// }

const unsigned Game::getCountOfLines(const std::string pathToFile) {
  char buffer[1024];
  unsigned countOfLines = 0;

  std::ifstream file(pathToFile);
  if (!file.is_open())
    throw std::runtime_error("File is not found (" + pathToFile + ")");

  while (file.getline(buffer, 1024))
    countOfLines++;

  file.close();

  return countOfLines;
}

const std::string Game::parseFile(const unsigned short lineNum) {
  std::string wordsFilePath = m_gameResPath;
  wordsFilePath += "/words.txt";

  std::string resWord;
  char buffer[1024];
  std::ifstream file(wordsFilePath.c_str());

  if (!file.is_open())
    throw std::runtime_error("File is not found (" + wordsFilePath + ")");

  unsigned countOfLines = 0;
  while (file.getline(buffer, 1024)) {
    countOfLines++;
    if (countOfLines == lineNum)
      resWord = buffer;
  }
  m_wordsFileCountOfLines = countOfLines;

  file.close();

  return resWord;
}

void Game::play() {
  for (unsigned short i = 0; i < 2; i++) {
    const unsigned short indexOfFamousLetter =
        rand() % (m_guessedWord.size() - 1);
    m_famousWord[indexOfFamousLetter] = m_guessedWord[indexOfFamousLetter];
  }

  std::cout << m_guessedWord << std::endl;
  std::cout << m_famousWord << std::endl;

  gameLoop();
}

void Game::gameLoop() {
  while (true) {
    clearTerminal();

    char userLetter;
    bool isLetterCorrect = false;

    updateGallows();
    std::cout << m_theGallows << std::endl << std::endl;

    if (m_attemptsCount == 6) {
      std::cout << "Sorry, you lose ^)" << std::endl;
      break;
    } else if (m_guessedWord == m_famousWord) {
      std::cout << "Congratulations!! You win with " << m_attemptsCount
                << " attempts";
      break;
    }

    std::cout << "Count of attempts: " << GREEN << m_attemptsCount << RESET
              << std::endl;
    std::cout << GREEN << "Used letters: " << m_enteredLetters << std::endl;
    std::cout << "Word you need to guess: " << m_famousWord << std::endl;
    std::cout << RED << "You can press 'Ctrl' + 'C' to quit" << RESET
              << std::endl;
    do {
      // getChar(userLetter);
      std::cin >> userLetter;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!std::isalpha(userLetter) ||
             m_enteredLetters.find(userLetter) != std::string::npos);

    std::vector<unsigned> indexes;
    for (unsigned i = 0; i < m_guessedWord.size(); i++) {
      if (std::tolower(m_guessedWord[i]) == std::tolower(userLetter)) {
        if (m_guessedWord[i] != m_famousWord[i]) {
          m_famousWord[i] = m_guessedWord[i];
          isLetterCorrect = true;
        }
      }
    }

    if (!isLetterCorrect)
      m_attemptsCount++;
    m_enteredLetters.push_back(userLetter);
  }
}

void Game::updateGallows() {
  switch (m_attemptsCount) {
  case 1:
    m_theGallows[32] = 'O';
    break;
  case 2:
    m_theGallows[44] = '&';
    break;
  case 3:
    m_theGallows[43] = '/';
    break;
  case 4:
    m_theGallows[45] = '\\';
    break;
  case 5:
    m_theGallows[55] = '/';
    break;
  case 6:
    m_theGallows[57] = '\\';
  }
}

int main() {
  std::srand(time(NULL));
  Game *game = new Game();
  game->play();

  delete game;
  return 0;
}
