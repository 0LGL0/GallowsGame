#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

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

  unsigned attemptsCount = 0;
  std::string theGallows =
      "########## \n"
      " #/     |  \n"
      " #         \n"
      " #         \n"
      " #         \n"
      " #         \n"
      " #           ";
  while (true) {
#if defined(__linux__) || defined(__unix) || defined(__unjx__)
    std::system("clear");
#elif defined(_WIN64) || defined(_WIN32)
    std::system("cls");
#endif

    char userLetter;
    bool isLetterCorrect = false;

    switch(attemptsCount){
      case 1: theGallows[32] = 'O'; break;
      case 2: theGallows[44] = '&'; break;
      case 3: theGallows[43] = '/'; break;
      case 4: theGallows[45] = '\\'; break;
      case 5: theGallows[55] = '/'; break;
      case 6: theGallows[57] = '\\'; 
    }
    std::cout << theGallows << std::endl << std::endl; 

    if (attemptsCount == 6) {
      std::cout << "Sorry, you lose ^)" << std::endl;
      break;
    } else if (guessedWord == famousWord) {
      std::cout << "Congratulations!! You win with " << attemptsCount
                << " attempts";
      break;
    }
    
    std::cout << "Count of attempts: \033[1;34m" << attemptsCount << "\033[0m" << std::endl;
    std::cout << "Word you need to guess: " << famousWord << std::endl;
    std::cout << "\033[1;31mYou can press 'Ctrl' + 'C' to quit\033[0m" << std::endl;
    std::cin >> userLetter;

    std::vector<unsigned> indexes;
    for (unsigned i = 0; i < guessedWord.size(); i++) {
      if (guessedWord[i] == userLetter || guessedWord[i] == (userLetter + 32) || guessedWord[i] == (userLetter - 32)) {
        if (guessedWord[i] != famousWord[i]){
          famousWord[i] = guessedWord[i];
          isLetterCorrect = true;
        }
      }
    }

    if(!isLetterCorrect)
      attemptsCount++;
  }

  return 0;
}
