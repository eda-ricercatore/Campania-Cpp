#!/bin/sh
g++ -c Student.cpp
g++ -c StudentDB.cpp
g++ -c main.cpp
g++ -o myprogram.out Student.o StudentDB.o main.o
./myprogram.out
