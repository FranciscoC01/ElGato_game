#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//funciones
void clear();
void SetColor(int color);
void clearArrayChar(char* array, int max_x, int val);
int menu();

int main(){
    menu();
    return 0;
}

int menu(){
    int opt=0;
    int flagPrint=0;
    int flag=1,flagKeyPressed=1;
    char in;
    char c[]={62,32,32,32};
    while(flag){
        if(kbhit()){
            if(flagKeyPressed){
                in = getch();
                printf("\n%d\n",in);
                if(in=='w'){
                    if(opt+1>3) opt=3;
                    else opt++;
                }
                if(in=='s'){
                    if(opt-1<0)opt=0;
                    else opt--;
                }
                if((int)in==13){
                    switch(opt){
                        case 3:
                            //funcion Nuevo Juego
                            break;
                        case 2:
                            //funcion Continuar juego
                            break;
                        case 1:
                            //funcion tabla puntuaciones
                            break;
                        case 0:
                            flag=0;
                            break;
                        default:
                            printf("\n\nError en el programa...\n\n");
                    }
                }
                switch(opt){
                    case 3:
                        clearArrayChar(&c,4,32);
                        c[0]=62;
                        break;
                    case 2:
                        clearArrayChar(&c,4,32);
                        c[1]=62;
                        break;
                    case 1:
                        clearArrayChar(&c,4,32);
                        c[2]=62;
                        break;
                    case 0:
                        clearArrayChar(&c,4,32);
                        c[3]=62;
                        break;
                    default:
                        printf("\n\nError en el programa...\n\n");
                }
                flagPrint=0;
                flagKeyPressed=0;
            }
        }
        else{
            flagKeyPressed=1;
        }
        if(flagPrint == 0){
            clear();
            printf("===== EL GATO MATEMATICO =====\n");
            printf("%c1. Iniciar nueva partida\n",c[0]);
            printf("%c2. Continuar partida\n",c[1]);
            printf("%c3. Estadisticas de partidas anteriores\n",c[2]);
            printf("%c4. salir\n",c[3]);
            if(!flag) printf("Saliendo del juego...");
            flagPrint= 1; 
        }
    }
    return 1;
}

void clearArrayChar(char* array, int max_x, int val){
    int i;
    for(i=0;i<max_x;i++){
        *array=val;
        array++;
    }
    return ;
}

void clear(){
    system("cls");
    return ;
}

void SetColor(int color) {
    WORD wColor; //This handle is needed to get the current background attribute

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi; //csbi is used for wAttributes word

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        //To mask out all but the background attribute, and to add the color
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

// int i;
//     int random;
//     char word[]="hola que tal";
//     for(i=0;word[i];i++){
//         random= rand() % 10;
//         SetColor(random);
//         printf("%c",word[i]);
//         SetColor(7);
//     }