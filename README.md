# Little-Flower
Little Flower Video Game for PC written in C++.
See the [Game Design Document](https://www.notion.so/reganwillis/Little-Flower-Game-Design-Document-332e2eabf06e401bb381adc6e64a6043).

## Development
I used [this tutorial](https://code.visualstudio.com/docs/languages/cpp#_example-install-mingwx64) and [this tutorial](https://www.msys2.org/) to install a C++ compiler and add it to the path. I compiled the program with `g++ -Wall -c main.cpp` and ran it with `a.exe`.

I downloaded [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) for a simple graphics interface. Now the compilation and run instructions must include paths to the new library.

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

## Resources
* [g++ cheatsheet](https://bytes.usc.edu/cs104/wiki/gcc/)
* [compiling a SFML program](https://www.sfml-dev.org/tutorials/2.1/start-linux.php#compiling-a-sfml-program)
* [C++ & SFML - Simple 2D Games](https://www.youtube.com/watch?v=C06eGdy7C6k)