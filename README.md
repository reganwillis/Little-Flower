# Little Flower
Little Flower Video Game for PC written in C++.
See the [Game Design Document](https://www.notion.so/reganwillis/Little-Flower-Puzzles-NFT-Version-Game-Design-Document-3682585ab6324d10b09851c36116ecfa).

## Included Repositories
* [Create-Flower](https://github.com/reganwillis/Randomize-Pixel-Art) (will be included)

## Development
I used [this tutorial](https://code.visualstudio.com/docs/languages/cpp#_example-install-mingwx64) and [this tutorial](https://www.msys2.org/) to install a C++ compiler and add it to the path. I compiled the program with `g++ -Wall -c main.cpp` and ran it with `a.exe`.

I downloaded [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) for a simple graphics interface. Now the compilation and run instructions must include paths to the new library.
TODO in future game: use OpenGL instead.

### Batch Script
Use the command `run` in the windows command line to run the batch script. This will run the commands below
TODO: make file? 

compile the program:
`g++ -c main.cpp -IC:\SFML-gcc\SFML-2.5.1\include`
creates: `main.o`

link the compiled file to the SFML libraries
`g++ main.o -o little-flower -LC:\SFML-gcc\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system`
creates: `little-flower.exe`

run new app:
`little-flower.exe`

## Error Log
* Error: SFML: undefined reference to _imp_ 
    * [Solution: download SFML GCC instead of SFML Visual C++](https://stackoverflow.com/questions/48661676/sfml-undefined-reference-to-imp)
* Error: The program can't start because sfml-graphics-2.dll is missing from your computer. Try reinstalling the program to fix this problem.
    * [Solution: Copy all dll files from main SFML > bin directory and paste them into your project folder.](https://stackoverflow.com/questions/29242013/sfml-2-1-and-codeblocks-error-sfml-graphics-2-dll-is-missing-from-your-computer/44126418)
* Error: C:/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/11.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: main.o:main.cpp:(.text+0x18): undefined reference to `Game::Game()'
    * looking for Game.h in the c++ folder instead of the current directory
    * add new cpp file to g++ compilation
    * add new output file (.o) to linking g++ command
* Error: invalid use of 'this' in non-member function
    * [Solution: declare cpp functions with class name in front of function name](https://stackoverflow.com/questions/9047671/invalid-use-of-this-in-non-member-function)

## Resources
* [g++ cheatsheet](https://bytes.usc.edu/cs104/wiki/gcc/)
* [compiling a SFML program](https://www.sfml-dev.org/tutorials/2.1/start-linux.php#compiling-a-sfml-program)
* tutorial 1:
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 1](https://www.youtube.com/watch?v=C06eGdy7C6k)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 2](https://www.youtube.com/watch?v=kxb0GvBNOGU)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 3](https://www.youtube.com/watch?v=LnMO84T7myM)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 4](https://www.youtube.com/watch?v=Y4fbvFjtVig)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 5](https://www.youtube.com/watch?v=Sil75qOxCW0)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 6](https://www.youtube.com/watch?v=K8pMdCJtdCY)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 7](https://www.youtube.com/watch?v=oDOgquwEf38)
    * [C++ & SFML - Simple 2D Games - GAME 1 / PART 8](https://www.youtube.com/watch?v=uaB3oK62T34)