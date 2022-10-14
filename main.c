#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//funciones
void clear();

void SetColor(int color)
{
    WORD wColor; //This handle is needed to get the current background attribute

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi; //csbi is used for wAttributes word

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //To mask out all but the background attribute, and to add the color
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}




int main(){
    int tablero[6][6];
    while(!kbhit()){
        printf("hola");
        Sleep(1000);
        clear();
        Sleep(1000);
    }
    return 0;
}

void clear(){
    system("cls");
    return ;
}