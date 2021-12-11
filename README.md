
The goal of this project is to solve numerically the Black & Scholes equation in C++. I done this with a fellow student in the project of a course to learn C++ !

The structure of the projet is the following : 
bin : ->  executables
build : ->  .o files
include : ->  .h files
src : ->  .cpp files

The file that gives the solution of the differential equation is main.cpp (it returns the vector C(0,.).
We made a Makefile to simplify the compilation :
The process is the following with a shell :
 - type make at the root of the folder
 - go to the subfolder "bin" and type "./main"
