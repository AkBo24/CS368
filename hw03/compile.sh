#!/bin/bash
clear
g++ -o hw3 homework_3.cpp -Wall -std=c++11
./hw3 < input1.txt
cat out1_formatted_summary.txt
