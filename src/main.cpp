#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string parseFile(const std::string path,
                            const unsigned short lineNum) {
  std::string resWord;
  char buffer[1024];
  std::ifstream file(path.c_str());

  if (!file.is_open()) {
    std::cerr << "File with words was not opened! (\"" << path << "\")";
    abort();
  }

  while (file.getline(buffer, 1024)) {
    static unsigned i = 0;
    i++;
    if (i == lineNum) {
      resWord = buffer;
      break;
    }
    // std::cout << buffer << std::endl;
  }

  file.close();

  return resWord;
}

int main() {
  std::filesystem::path pathToWordsFile = std::filesystem::current_path();
  pathToWordsFile += "/res/words.txt";
  // std::cout << pathToWordsFile.string() << std::endl;

  std::srand(time(NULL));
  const unsigned randWordIndex = std::rand() % 427 + 1;
  const std::string guessedWord = parseFile(pathToWordsFile, randWordIndex);
  std::string famousWord(guessedWord.size(), '#');
  for (unsigned short i = 0; i < 2; i++) {
    const unsigned short indexOfFamousLetter =
        rand() % (guessedWord.size() - 1);
    famousWord[indexOfFamousLetter] = guessedWord[indexOfFamousLetter];
  }

  std::cout << guessedWord << std::endl;
  std::cout << famousWord << std::endl;

  unsigned short attemptsCount = 0;

  while (true) {
    char userLetter;
    if (attemptsCount == 6) {
      std::cout << "Sorry, you lost ^)" << std::endl;
      break;
    } else if (guessedWord == famousWord) {
      std::cout << "Congratulations!! You win with " << attemptsCount
                << "attempts";
      return 0;
    }

    std::cout << attemptsCount << std::endl;
    std::cout << famousWord << std::endl;

    std::cin >> userLetter;

    std::vector<unsigned> indexes;
    for (unsigned i = 0; i < guessedWord.size(); i++) {
      if (guessedWord[i] == userLetter) {
        if (guessedWord[i] != famousWord[i]) {
          famousWord[i] = guessedWord[i];
          continue;
        }
      } else
        attemptsCount++;
    }
  }

  return 0;
}
