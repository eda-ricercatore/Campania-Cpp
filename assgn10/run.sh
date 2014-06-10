#!/bin/sh
g++ -c Student.cpp
g++ -c StudentDB.cpp
g++ -c Graduate.cpp
g++ -c Undergraduate.cpp
g++ -c main.cpp
g++ -o myprogram.out Student.o StudentDB.o Undergraduate.o Graduate.o main.o
./myprogram.out
