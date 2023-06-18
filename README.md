# Chess in C++/SFML

This is a C++ project that implements a simple chess game using SFML.<br>

![ezgif com-video-to-gif (1)](https://user-images.githubusercontent.com/111639941/218856315-59802d3e-3b42-4cc4-a5f3-fa643fc1607a.gif)


## Not implemented yet
- Checkmate
- En passant

## Prerequisites
Before running, make sure you have the following installed on your system:
-   SFML library: You can download SFML from the official website ([https://www.sfml-dev.org/](https://www.sfml-dev.org/)) and follow the installation instructions for your operating system, for example on Debian-based systems:
```
$ sudo apt-get install libsfml-dev
```
- OpenGL library: You can install the library with the following command:
```
$ sudo apt-get install libglu1-mesa-dev mesa-common-dev
```
- A C++ compiler, e.g. ``GCC``
```
$ sudo apt-get install build-essential
```
- On Windows, make sure to set the ``SFML_PATH`` variable to the root path of the SFML library:
```
set SFML_PATH=C:\path\to\sfml
```
 
## Build using Makefile
If you have ``GNU Make`` installed on your system, you can use the included ``Makefile`` to build the project.

1. Clone the repository to your local machine:
```
$ git clone https://github.com/BlackyDrum/chess.git
```
2. Change to the cloned directory:
```
$ cd chess
```
3. Use make to build the project. The executable ``chess`` will be generated in the root directory.
```
$ make
```
4. Run the binary file (or double click the .exe on Windows):
```
$ ./chess
```
<strong>Note: If you encounter any problems on Windows trying to run ``chess.exe``, make sure to put the .dll in the same directory as the ``chess.exe``.
You can find the .dll files in the official SFML ``bin`` folder.</strong>
