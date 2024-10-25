## Chess SFML Project

This project is a chess game developed using C++ and SFML.

## Prerequisites

- CMake
- SFML
- A C++17 compatible compiler

---

## Setup Instructions

### Windows


#### 1. Install SFML
- Download SFML for Windows from [SFML Downloads](https://www.sfml-dev.org/download/sfml/2.6.1/).
- Extract the SFML files to a directory (e.g., `C:\Program Files\SFML-2.6.1`).
- Ensure that the SFML version matches the compiler you're using (e.g., Visual Studio or GCC/MinGW).

#### 2. Build the Project
1. Open a terminal (Command Prompt or PowerShell) and navigate to your project root directory.
   
2. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```
3. Configure and build the project with CMake
   ```bash
   cmake -DSFML_ROOT_DIR="C:/Path/To/SFML" ..
   cmake --build . --config Release
   ```
4. Run the executable  located in the `build/Release/` folder


### Linux


#### 1. Install SFML
  ```bash
  sudo apt install libsfml-dev
  ```

#### 2. Build the Project
1. Open a terminal (Command Prompt or PowerShell) and navigate to your project root directory.

2. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

3. Configure and build the project with CMake
   ```bash
   cmake ..
   make
   ```

4. Run the executable
   ```
   ./Chess
   ```
