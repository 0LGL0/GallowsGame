# GallowsGame

GallowsGame is a simple word-guessing game implemented in C++. This README provides instructions on how to clone, build, and run the game on both Linux and Windows platforms.

## Table of Contents

- [Requirements](#requirements)
- [Getting Started](#getting-started)
  - [Cloning the Repository](#cloning-the-repository)
  - [Building and Running on Linux](#building-and-running-on-linux)
  - [Building and Running on Windows](#building-and-running-on-windows)

## Requirements

- A C++ compiler (e.g., `clang` or `g++` for Linux, `MSVC` for Windows)
- CMake (optional, for a more portable build system)

## Getting Started

### Cloning the Repository

To clone the repository, run the following command:

```sh
git clone https://github.com/0LGL0/GallowsGame.git
cd GallowsGame
```

### Building and Running on Linux

1. **Install the necessary packages (for clang, change g++/gcc to clang):**

   On Debian-based distributions (e.g., Ubuntu):

   ```sh
   sudo apt update
   sudo apt install g++ make
   ```

   On Red Hat-based distributions (e.g., Fedora):

   ```sh
   sudo dnf install g++ make
   ```

   On Arch Linux:
   
   ```sh 
   sudo pacman -Syu
   sudo pacman -S gcc
   ```

2. **Create `build` directory:**
   
   ```sh
   mkdir build
   cd build
   ```

3. **Compile the game:**

- GCC:

  ```sh
  g++ -o GallowsGame ../src/main.cpp -std=c++20
  ```

- Clang:
  
  ```sh
  clang++ ../src/main.cpp -o GallowsGame -std=c++20
  ```

- CMake:
       
  ```sh
  cmake ..
  cmake --build .
  ```

4. **Run the game:**

   ```sh
   ./GallowsGame
   ```

### Building and Running on Windows

1. **Install the necessary tools:**

   - [Visual Studio](https://visualstudio.microsoft.com/) (Make sure to include the C++ Desktop Development workload)

2. **Open the Developer Command Prompt for Visual Studio:**

   You can find this in the Start Menu under Visual Studio.

3. **Navigate to the cloned repository:**

   ```sh
   cd path\to\GallowsGame
   ```

4. **Compile the game:**

   ```sh
   cl src\main.cpp /Fe:GallowsGame.exe
   ```

5. **Run the game:**

   ```sh
   GallowsGame.exe
   ```

## Notes

- Ensure that the `res/words.txt` file exists in the appropriate directory as the game relies on this file to function correctly.
- For any issues or contributions, please refer to the [issues section](https://github.com/0LGL0/GallowsGame/issues) of the repository.

Happy gaming!
