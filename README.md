### COMPILE THE PROJECT

To compile most projects, use the gcc command below. <br>
Some projects have assets or dependencies, they come in the project folder and must be in the same folder as the C++ file in order for the project to compile.<br><br>
Most projects require SFML 3.1.0 so make sure you have that. 

## Compiling the project
```
g++ -std=c++20 filename.cpp -o executableName -lsfml-graphics -lsfml-window -lsfml-system 
```

