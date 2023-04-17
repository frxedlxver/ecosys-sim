//
// Created by rhend on 2023-04-17.
//

#include "print_color.hpp"
#include <windows.h>

void PrintColor::Col(int c)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
    return;
}