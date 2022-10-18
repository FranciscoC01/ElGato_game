#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//funciones
void clear();
int dominio(int x,int y,int min_x,int max_x,int min_y,int max_y);
void SetColor(int color);
void clearArrayChar(char* array, int max_x, int val);
void clearArray(int matriz[][6], int max_y, int val);
int gano(int tablero[][6],int x0,int y0);
void menuNuevoJuego(int tablero[][6]);
void menu();

int main(){
    menu();
    return 0;
}

//funcion menu - control principal de programa
void menu(){
    //variables
    int opt=3;                                   //opcion elegida
    int flagPrint=0;                             //bandera de impresion para evitar multiples impresiones
    int flag=1;                                  //flag de bucle - si es 0 se sale del juego
    char in;                                     //variable input del usuario
    char c[]={62,32,32,32};                      //array para la parte grafica del menu
    int tablero[6][6];
    //programa
    while(flag){                                 //bucle principal - mantiene vivo el menu
        if(kbhit()){                             //si una tecla se presiono entonces se obtiene cual fue
            in = getch();
            if(in=='w'){                         //si es w entonces se sube el "puntero" y opt se le suma 1
                if(opt+1>3) opt=3;
                else opt++;
            }
            if(in=='s'){                         //si es s entonces se baja el "puntero" y opt se le resta 1
                if(opt-1<0)opt=0;
                else opt--;
            }
            if((int)in==13){                     //si es enter entonces se ingresa a esa opcion
                switch(opt){
                    case 3:
                        clearArray(tablero,6,0);
                        menuNuevoJuego(tablero);
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
            switch(opt){                       //switch que se encarga de mostrar graficamente que opcion se esta eligiendo
                case 3:
                    clearArrayChar(&c[0],4,32);
                    c[0]=62;
                    break;
                case 2:
                    clearArrayChar(&c[0],4,32);
                    c[1]=62;
                    break;
                case 1:
                    clearArrayChar(&c[0],4,32);
                    c[2]=62;
                    break;
                case 0:
                    clearArrayChar(&c[0],4,32);
                    c[3]=62;
                    break;
                default:
                    printf("\n\nError en el programa...\n\n");
            }
            flagPrint=0;
        }
        if(flagPrint == 0){
            clear();
            printf("===== EL GATO MATEMATICO =====\n");
            printf("%c1. Iniciar nueva partida\n",c[0]);
            printf("%c2. Continuar partida\n",c[1]);
            printf("%c3. Estadisticas de partidas anteriores\n",c[2]);
            printf("%c4. salir\n",c[3]);
            if(!flag) printf("\nSaliendo del juego...");
            flagPrint= 1;
        }
    }
    return ;
}

void menuNuevoJuego(int tablero[][6]){
    int turno=0;
    int flagOut=0;
    int flag=0;
    int flagScreen=0;
    int flagSelector=0;
    int flagAlert=0;
    int flagWinner=0;
    int x,y;
    int aux;
    char in;
    char jugadores[2][10];
    int currentPlayer= rand() % 1;
    int currentMark=-1;
    int tableroImp[][6]={{ 1, 2, 3, 4, 5, 6},
                         { 7, 8, 9,10,12,14},
                         {15,16,18,20,21,24},
                         {25,27,28,30,32,35},
                         {36,40,42,45,48,49},
                         {54,56,63,64,72,81}};
    int valores[]={-1,0,-1,-1,0,-1}; //lugar marc.1, estado: 1 fijado / 0 suelto, lugar anterior 
    char c[]={32,32,32,32,32,32,32,32,32};

    clear();
    printf("====== Nuevo juego ======\n");
    printf("ingrese nombre del primer jugador: ");
    gets(&jugadores[0]);
    printf("ingrese nombre del segundo jugador: ");
    gets(&jugadores[1]);
    printf("\n%s y %s cuando esten preparados apreten cualquier tecla o presionen esc para volver al menu...",jugadores[0],jugadores[1]);
    
    while(!flag){
        if(kbhit()){
            in=getch();
            if((int)in==27){
                flagOut=1;
                flag=1;
            }else{
                flag=1;
            }
        }
    }
    
    while((flag)&&(!flagOut)){
        if(kbhit()){
            in=getch();
            if(turno!=0){
                if(in=='1'){
                    if(valores[3]!=valores[5]){
                        clearArrayChar(&c[0],9,32);
                        valores[3]=valores[5];
                        c[valores[0]]=62;
                        c[valores[3]]=62;
                    }
                    currentMark=0;
                }
                if(in=='2'){
                    if(valores[0]!=valores[2]){
                        clearArrayChar(&c[0],9,32);
                        valores[0]=valores[2];
                        c[valores[0]]=62;
                        c[valores[3]]=62;
                    }
                    currentMark=3;
                }
            }
            if(in=='w'){
                if(turno==0){
                    clearArrayChar(&c[0],9,32);
                    if(valores[1]==0){
                        if(valores[0]-1<0) valores[0]==0;
                        else valores[0]--;
                    }else if(valores[4]==0){
                        if(valores[3]-1<0) valores[3]==0;
                        else valores[3]--;
                    }
                    if(valores[0]==valores[3]){
                        c[valores[0]]=175;
                    }
                    else{
                        c[valores[0]]=62;
                        c[valores[3]]=62;
                    }
                }else{
                    if(currentMark!=-1){
                        clearArrayChar(&c[0],9,32);
                        if(valores[currentMark]-1<0) valores[currentMark]==0;
                        else valores[currentMark]--;
                        if(valores[0]==valores[3]){
                            c[valores[0]]=175;
                        }
                        else{
                            c[valores[0]]=62;
                            c[valores[3]]=62;
                        }
                    }
                }
            }else if(in=='s'){
                if(turno==0){
                    clearArrayChar(&c[0],9,32);
                    if(valores[1]==0){
                        if(valores[0]+1>8) valores[0]==8;
                        else valores[0]++;
                    }else if(valores[4]==0){
                        if(valores[3]+1>8) valores[3]==8;
                        else valores[3]++;
                    }
                    if(valores[0]==valores[3]){
                        c[valores[0]]=175;
                    }
                    else{
                        c[valores[0]]=62;
                        c[valores[3]]=62;
                    }
                }else{
                    if(currentMark!=-1){
                        clearArrayChar(&c[0],9,32);
                        if(valores[currentMark]+1>8) valores[currentMark]==8;
                        else valores[currentMark]++;
                        if(valores[0]==valores[3]){
                            c[valores[0]]=175;
                        }
                        else{
                            c[valores[0]]=62;
                            c[valores[3]]=62;
                        }
                    }
                }
            }else if((int)in==13){
                if(turno==0){
                    if((valores[1]==0)&&(valores[0]!=-1)){
                        valores[1]=1;
                    }else if((valores[4]==0)&&(valores[3]!=-1)){
                        valores[4]=1;
                    }
                    if((valores[1]==1)&&(valores[4]==1)){
                        valores[2]=valores[0];
                        valores[5]=valores[3];
                        aux=(valores[0]+1)*(valores[3]+1);
                        for(y=0;y<6;y++){
                            for(x=0;x<6;x++){
                                if(tableroImp[y][x]==aux){
                                    tablero[y][x]=1;
                                }
                            }
                        }
                        turno++;
                        currentPlayer= !currentPlayer;
                    }
                }else{
                    if((valores[0]!=valores[2])||(valores[3]!=valores[5])){
                        aux=(valores[0]+1)*(valores[3]+1);
                        for(y=0;y<6;y++){
                            for(x=0;x<6;x++){
                                if(tableroImp[y][x]==aux){
                                    if(tablero[y][x]!=0){
                                        flagAlert=1;
                                    }else{
                                        if(currentPlayer%2==0){
                                            tablero[y][x]=1;
                                        }else{
                                            tablero[y][x]=2;
                                        }
                                        flagWinner = gano(tablero,x,y);
                                        flagAlert=0;
                                    }
                                    
                                }
                            }
                        }
                        if(!flagAlert){
                            valores[2]=valores[0];
                            valores[5]=valores[3];
                            turno++;
                            currentPlayer= !currentPlayer;
                            currentMark=-1;
                        }
                    }
                }
                
            }
            flagScreen=0;
        }
        if(!flagScreen){
            clear();
            for(y=0;y<6;y++){
                printf("%c%c",9,9);
                for(x=0;x<6;x++){
                    switch(tablero[y][x]){
                        case 1:
                            SetColor(2); //verde
                            break;
                        case 2:
                            SetColor(3); //celeste
                            break;
                        default:
                            SetColor(7); //gris
                    }
                    printf("%2i ",tableroImp[y][x]);
                }
                SetColor(7);
                printf("%3c%i",c[y],y+1);
                if(y<3){
                    printf("%3c%i",c[6+y],7+y);
                }
                printf("\n");
            }
            if(turno==0){
                printf("\n%s coloque de a uno los marcadores con las teclas w,s y confirme con el enter",jugadores[currentPlayer]);
            }
            else if(!flagWinner){
                printf("\n%s seleccione el marcador con la tecla 1 o 2,\nmueva el marcador con las teclas w,s \ny confirme con el enter", jugadores[currentPlayer]);
                switch(currentMark){
                    case 0:
                        printf("\n\nmarcador seleccionado: 1");
                        break;
                    case 3:
                        printf("\n\nmarcador seleccionado: 2");
                        break;
                    default:
                        printf("\n\nningun marcador seleccionado");
                }
                if(valores[0]==-1){
                    printf("\n\nMarcador 1: Sin colocar.\n");
                }else{
                    printf("\n\nMarcador 1: %i.\n",valores[0]+1);
                }
                if(valores[2]==-1){
                    printf("Marcador 2: Sin colocar.");
                }else{
                    printf("Marcador 2: %i.",valores[3]+1);
                }
                if(flagAlert){
                    SetColor(4); //rojo
                    printf("\nel valor seleccionado ya esta tomado por vos o por tu oponente, elegi otro valor");
                    SetColor(7);
                }
            }else{
                printf("\nGANASTE CAMPEON GANASTEEEE");
            }
            flagScreen=1;
        }
    }
    return ;
}

void clearArray(int matriz[][6], int max_y, int val){
    int x,y;
    for(y=0;y<max_y;y++){
        for(x=0;x<6;x++){
            matriz[y][x]=val;
        }
    }

    return ;
}

//funcion que inicializa un array de tipo char a un valor especifico
void clearArrayChar(char* array, int max_x, int val){
    int i;
    for(i=0;i<max_x;i++){
        *array=val;
        array++;
    }
    return ;
}

int gano(int tablero[][6],int x0,int y0){
    int i,x,y;
    int jugador=tablero[y0][x0];
    int contador=0;

    for(i=-2;i<3;i++){
        x=x0+i;
        y=y0+i;
        if(dominio(x,y,0,5,0,5)){
            if(tablero[y][x]==jugador){
                contador++;
            }else{
                contador=0;
            }
        }
    }
    if(contador>2) return 1;
    
    for(i=-2;i<3;i++){
        x=x0+i;
        y=y0;
        if(dominio(x,y,0,5,0,5)){
            if(tablero[y][x]==jugador){
                contador++;
            }else{
                contador=0;
            }
        }
    }
    if(contador>2) return 1;

    for(i=-2;i<3;i++){
        x=x0-i;
        y=y0+i;
        if(dominio(x,y,0,5,0,5)){
            if(tablero[y][x]==jugador){
                contador++;
            }else{
                contador=0;
            }
        }
    }
    if(contador>2) return 1;

    for(i=-2;i<3;i++){
        x=x0;
        y=y0+i;
        if(dominio(x,y,0,5,0,5)){
            if(tablero[y][x]==jugador){
                contador++;
            }else{
                contador=0;
            }
        }
    }
    if(contador>2) return 1;

    return 0;
}

int dominio(int x,int y,int min_x,int max_x,int min_y,int max_y){
    if((x>=min_x)&&(x<=max_x)&&(y>=min_y)&&(y<=max_y)){
        return 1;
    }else{
        return 0;
    }
}

//funcion que se encarga de limpiar la pantalla
void clear(){
    system("cls");
    return ;
}

//funcion que cambia el color del texto
//autor: desconocido - codigo compartido por el classroom
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