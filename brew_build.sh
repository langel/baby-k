#!/bin/bash
gcc-11 -o main.app main.c -I/opt/homebrew/include -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2
./main.app
