#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>

// ----------------------
// Memory Leak Detection
// ----------------------
#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define ENABLE_LEAK_DETECTION()
#endif

// ----------------------
// Constants & Global Variables
// ----------------------
const int DEFAULT_GRID_SIZE = 15;  
const int TIMER_INTERVAL = 50;     


enum EventID {
    ID_PLAY = 10001,
    ID_PAUSE,
    ID_NEXT,
    ID_CLEAR,
    ID_TIMER
};

// ----------------------
// Cell Structure
// ----------------------
struct Cell {
    bool alive = false; 
};

#endif
