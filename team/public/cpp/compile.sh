#!/bin/bash

problem=team
grader_name=grader

g++ -std=gnu++17 -O2 -pipe -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
