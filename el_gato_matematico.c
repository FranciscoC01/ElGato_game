#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//funciones de utilidad
void clear();
int dominio(int x,int y,int min_x,int max_x,int min_y,int max_y);
void SetColor(int color);
void clearArrayChar(char* array, int max_x, int val);
void clearArray(int matriz[][6], int max_y, int val);
int gano(int tablero[][6],int x0,int y0);

//funciones principales
void guardarPartida(int tablero[][6], char jugadores[][10], int valores[], int turno,int abandonada,int ganador);
void traerPartida();
void tablaPartidas();
void jugar(int tablero[][6],char jugadores_arc[2][10],int valores_arc[6],int turno_arc,int continuar);
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
    char c[]={32,32,32,62};                      //array para la parte grafica del menu
    
    char jugadores[2][10];
    int valores[1];

    // int tablero[6][6];
    int tablero[][6]={{ 0, 0, 0, 0, 0, 0},
                      { 0, 0, 0, 0, 0, 0},
                      { 0, 0, 0, 0, 0, 0},
                      { 0, 0, 0, 0, 0, 0},
                      { 0, 0, 0, 0, 0, 0},
                      { 0, 0, 0, 0, 0, 0}};
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
                        jugar(tablero,jugadores,valores,0,0);
                        break;
                    case 2:
                        traerPartida();
                        break;
                    case 1:
                        tablaPartidas();
                        break;
                    case 0:
                        flag=0;
                        break;
                    default:
                        printf("\n\nError en el programa...\n\n");
                }
            }

            clearArrayChar(&c[0],4,32);
            c[opt]=62;

            flagPrint=0;
        }
        if(flagPrint == 0){
            clear();
            printf("===== EL GATO MATEMATICO =====\n");
            printf("%c1. Iniciar nueva partida\n",c[3]);
            printf("%c2. Continuar partida\n",c[2]);
            printf("%c3. Tabla de partidas ganadas\n",c[1]);
            printf("%c4. salir\n",c[0]);
            if(!flag) printf("\nSaliendo del juego...");
            flagPrint= 1;
        }
    }
    return ;
}
//jugar(tablero_dat,jugadores_dat,valores_dat,turno_dat);
void jugar(int tablero[][6],char jugadores_arc[2][10],int valores_arc[6],int turno_arc,int continuar){

    int turno=0;
    int flagOut=0;
    int flag=0;
    int reScreen=1;
    int flagAbandona[2]={0,0};
    int flagAlert=0;
    int flagWinner=0;
    int flagEncontrado=0;
    int x,y,i,b;
    int aux;
    char in;
    char jugadores[2][10];
    int currentPlayer=0;
    int currentMark=-1;
    int tableroImp[][6]={{ 1, 2, 3, 4, 5, 6},
                         { 7, 8, 9,10,12,14},
                         {15,16,18,20,21,24},
                         {25,27,28,30,32,35},
                         {36,40,42,45,48,49},
                         {54,56,63,64,72,81}};
    int valores[]={-1,0,-1,-1,0,-1};
    char c[]={32,32,32,32,32,32,32,32,32};

    if(continuar==0){
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
    }else{
        for(i=0;i<2;i++){
            for(b=0;b<10;b++){
                jugadores[i][b]=jugadores_arc[i][b];
            }
        }
        for(i=0;i<6;i++){
            valores[i]=valores_arc[i];
        }
        clearArrayChar(&c[0],9,32);
        c[valores[0]]=62;
        c[valores[3]]=62;
        turno=turno_arc;
        flag=1;
    }
    

    while((flag)&&(!flagOut)){
        //=============== CONTROL TECLADO ======================
        if(kbhit()){
            switch((int)getch()){
                case 49:                                             //Si se apreto '1' 
                    if(turno!=0){                                    //Solo si no es el primer turno
                        if(valores[3]!=valores[5]){                  //En caso de haberse movido el otro marcador
                            clearArrayChar(&c[0],9,32);
                            valores[3]=valores[5];                   //Se lo devuelve a su lugar de origen
                            c[valores[0]]=62;
                            c[valores[3]]=62;
                        }
                        currentMark=0;                               //Y se establece el marcador seleccionado como libre
                    }
                    break;
                case 50:                                             //Si se apreto '2' 
                    if(turno!=0){
                        if(valores[0]!=valores[2]){
                            clearArrayChar(&c[0],9,32);
                            valores[0]=valores[2];
                            c[valores[0]]=62;
                            c[valores[3]]=62;
                        }
                        currentMark=3;
                    }
                    break;
                case 87:                                             //Si se ingresa 'W' o 'w'
                case 119:
                    if(turno!=0){                                    //Si no es el primer turno
                        if(currentMark!=-1){                         //Y si se tiene seleccionado un marcador
                            clearArrayChar(&c[0],9,32);              //reinicio el array de los marcadores a espacios(32)
                            //+++++ valor del selector +++++
                            if(valores[currentMark]-1<0) valores[currentMark]=8; //si el marcador seleccionado es menor a 0 lo mando al espacio 8
                            else valores[currentMark]--;                         //sino, lo dejo bajar
                            
                            //+++++ Movimiento del selector GRAFICAMENTE +++++
                            if(valores[0]==valores[3]){
                                c[valores[0]]=175;
                            }
                            else{
                                c[valores[0]]=62;
                                c[valores[3]]=62;
                            }
                        }
                    }else{                                           //Si es el primer turno
                        clearArrayChar(&c[0],9,32);                  //reinicio el array de los marcadores a espacios(32)
                        //+++++ valor del selector +++++
                        if(valores[1]==0){                           //Si el marcador 1 esta suelto
                            (valores[0]-1<0)? (valores[0]=8):(valores[0]--);   //Si el marcador 1 es menor a 0 lo mando al espacio 8
                        }else if(valores[4]==0){                     //Si el marcador 2 esta suelto
                            (valores[3]-1<0)? (valores[3]=8):(valores[3]--);
                        }

                        //+++++ Movimiento del selector GRAFICAMENTE +++++
                        if(valores[0]==valores[3]){
                            c[valores[0]]=175;
                        }
                        else{
                            c[valores[0]]=62;
                            c[valores[3]]=62;
                        }
                    }
                    break;
                case 83:                                             //Si se ingresa 'S' o 's'
                case 115: 
                    if(turno!=0){                                    //Si no es el primer turno
                        if(currentMark!=-1){                         //Y hay alguno marcador seleccionado
                            clearArrayChar(&c[0],9,32);              //Reinicio el array de los marcadores
                            //+++++ valor del selector +++++
                            if(valores[currentMark]+1>8) valores[currentMark]=0;   //Si el marcador seleccionado es mayor a 8 lo mando al espacio 0 
                            else valores[currentMark]++;                           //sino lo dejo subir
                            
                            //+++++ Movimiento del selector GRAFICAMENTE +++++
                            if(valores[0]==valores[3]){ 
                                c[valores[0]]=175;
                            }
                            else{
                                c[valores[0]]=62;
                                c[valores[3]]=62;
                            }
                        }
                    }else{                                           //Es el primer turno
                        clearArrayChar(&c[0],9,32);                  //limpio el array de marcadores
                        //+++++ valor del selector +++++
                        if(valores[1]==0){                           //si el marcador 1 esta suelto
                            (valores[0]+1>8)? (valores[0]=0):(valores[0]++);   //Si el marcador 1 es mayor a 8 lo mando al espacio 0
                        }else if(valores[4]==0){                     //si el marcador 2 esta suelto
                            (valores[3]+1>8)? (valores[3]=8):(valores[3]++);
                        }

                        //+++++ Movimiento del selector GRAFICAMENTE +++++
                        if(valores[0]==valores[3]){
                            c[valores[0]]=175;
                        }
                        else{
                            c[valores[0]]=62;
                            c[valores[3]]=62;
                        }
                    }
                    break;
                case 13:                                             //Si se apreto 'Enter'
                    if(flagAbandona[0]){
                        if(flagAbandona[1]){
                            guardarPartida(tablero,jugadores,valores,turno,1,currentPlayer);
                            flag=0;
                        }else{
                            flagAbandona[1]=1;
                        }
                    }else{
                        if(turno!=0){                                    //Y no es el primer turno
                            if((valores[0]!=valores[2])||(valores[3]!=valores[5])){  //Reviso que alguno de los dos marcadores haya cambiado de posicion
                                aux=(valores[0]+1)*(valores[3]+1);                   //calculo el valor de la multiplicacion
                                flagEncontrado=0;
                                flagAlert=0;                                         //y reinicio la bandera de casilla bloqueada
                                for(y=0;(y<6)&&(!flagEncontrado);y++){                                    //itero entre a X e Y entre 0 y 5 
                                    for(x=0;(x<6)&&(!flagEncontrado);x++){
                                        if(tableroImp[y][x]==aux){                   //Si el valor en tableroImp es igual a la multiplicacion creada
                                            if(tablero[y][x]==0){                    //y si la casilla en tablero esta vacia
                                                if(currentPlayer==0){              //veo que jugador esta actualmente
                                                    tablero[y][x]=1;                 //asigno en tablero ese lugar al jugador 1
                                                }else{
                                                    tablero[y][x]=2;                 //asigno en tablero ese lugar al jugador 2
                                                }
                                                flagWinner=gano(tablero,x,y);        //me fijo si con este movimiento el jugador gano
                                                flagEncontrado=1;       
                                            }else{                                   //SINO
                                                flagAlert=1;                         //paso la bandera de alerta de casilla bloqueada
                                            }
                                        }
                                    }
                                }
                                if(!flagAlert&&!flagWinner){                        //si flagAlert no se activo y tampoco la de ganador
                                    valores[2]=valores[0];                          //paso los valores actuales de los marcadores al "historial"
                                    valores[5]=valores[3];
                                    turno++;                                        //paso de turno
                                    currentPlayer= !currentPlayer;                  //le doy el turno al otro jugador
                                    currentMark=-1;                                 //y deselecciono los marcadores
                                }
                            }
                        }else{                                           //Si es el primer turno
                            if((valores[1]==0)&&(valores[0]!=-1)){       //Si el marcador 1 se movio y no esta fijo
                                valores[1]=1;                            //lo fijo
                            }else if((valores[4]==0)&&(valores[3]!=-1)){ //Si el marcador 2 se movio y no esta fijo
                                valores[4]=1;                            //lo fijo
                            }

                            if((valores[1]==1)&&(valores[4]==1)){        //si los dos marcadores estan fijos
                                valores[2]=valores[0];                   //paso los valores actuales de los marcadores al "historial"
                                valores[5]=valores[3];        
                                aux=(valores[0]+1)*(valores[3]+1);       //calculo la multiplicacion
                                for(y=0;y<6;y++){                        //busco el valor en tableroImp
                                    for(x=0;x<6;x++){
                                        if(tableroImp[y][x]==aux){
                                            tablero[y][x]=currentPlayer+1; //le doy el valor del jugador inicial
                                        }
                                    }
                                }
                                turno++;                                 //paso de turno
                                currentPlayer= !currentPlayer;           //le doy el control al otro jugador
                                // printf("JUEGA %i",currentPlayer);
                            }
                        }
                    }
                    break;
                case 27:                                             //Si se apreto 'esc' 
                    if(flagAbandona[1]){                             //si se quiere salir del loop sin guardar
                        flag=0;
                    }else{                                          
                        flagAbandona[0]=!flagAbandona[0];            //si no se quiere salir del loop
                    }
                    break;
            }
            reScreen=1;                                              //actualizo la pantalla
        }

        //=================== IMPRESION =======================
        if(reScreen){                                   //si es necesario actualizar la pantalla
            clear();                                                 //limpio la pantalla
            if((!flagWinner)&&(!flagAbandona[0])&&(!flagAbandona[1])){
                for(y=0;y<6;y++){                                        //imprimo por niveles horizontales
                    printf("%c%c",9,9);                                  //imprimo 2 tabulaciones
                    for(x=0;x<6;x++){                                    //imprimo cada fila del nivel
                        switch(tablero[y][x]){                           //si tablero en esa coordenada tiene algun valor
                            case 1:                                      //si es del jugador 1 
                                SetColor(2);                             //le asigno el color verde a la casilla 
                                break;
                            case 2:                                      //si es del jugador 2
                                SetColor(3);                             //le asigno el color celeste a la casilla
                                break;
                            default:                                     //si no es de nadie
                                SetColor(7);                             //la dejo con el color por default gris 
                        }
                        printf("%2i ",tableroImp[y][x]);                 //imprimo los caracteres con un ancho de 2
                    }
                    SetColor(7);                                         //devuelvo el caracter al color por default
                    printf("%3c%i",c[y],y+1);                            //imprimo el espacio del marcador con 3 de ancho y un numero
                    if(y<3){                                             //si estoy en los primeros niveles imprimo los numeros 7,8,9
                        printf("%3c%i",c[6+y],7+y);
                    }
                    printf("\n");
                }
                printf("\nTurno de: %s",jugadores[currentPlayer]);
                if(turno!=0){
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
                    if(flagAlert){
                        SetColor(4); //rojo
                        printf("\nel valor seleccionado ya esta tomado por vos o por tu oponente, elegi otro valor");
                        SetColor(7);
                    }
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

                printf("\n\nControles: \n");
                printf("- con \"w\" y \"s\" mueve los marcadores\n");
                printf("- con \"Enter\" los fija\n");
                printf("- con \"1\" y \"2\" selecciona los marcadores\n");
                printf("Nota: DESPUES del PRIMER TURNO puede mover SOLO 1 marcador\n");
            }else if(flagAbandona[0]){
                if(flagAbandona[1]){
                    printf("\n\nquiere guardar la partida?\naprete Enter\nen caso contrario, aprete esc");
                }else{
                    printf("\n\nSeguro que quiere abandonar la partida?\naprete Enter\nen caso contrario, aprete esc");
                }
            }else{
                printf("El ganador de la partida fue %s y le tomo %i turnos ganar",jugadores[currentPlayer],turno);
                guardarPartida(tablero,jugadores,valores,turno,0,currentPlayer);
                printf("aprete enter para volver al menu\n");
                while(!kbhit());
                flagOut=1;
            }
            reScreen=0;
        }
    
    }
    return ;
}


//funcion que inicializa un array a un valor especifico
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

//funcion que permite continuar una partida
void traerPartida(){
    FILE* origen;
    FILE* destino;

    //datos de la partida
    int tablero[6][6];
    char jugadores[2][10];
    int valores[6];
    int turno;

    //variables de la funcion
    char dato;  
    int sz;
    int nPartidas;
    int i,sup,inf,lug;
    int flag=1;
    int printScreen=1;
    int opt=0;

    //archivos a consultar/crear
    char partidas[]= "./data.dat";
    char partidasTemp[]= "./data.tmp"; 

    origen=fopen(partidas,"rb");
    fseek(origen,0,SEEK_END);

    sz = ftell(origen);                //voy al final del archivo
    nPartidas=sz/192;                  //me fijo la cantidad de partidas guardadas
    char jugadores_list[2*(nPartidas)][10];  //declaro de forma dinamica la cantidad de partidas guardadas a mostrar
    char c[nPartidas];                       //de la misma forma con el marcador que ayudara a elegir la partida
    clearArrayChar(&c[0],nPartidas,32);      //limpio el array y lo inicializo en 32 "null"
    c[0]=62;
    rewind(origen);                          //vuelvo al origen

    for(i=0;i<nPartidas;i++){                //extraigo los nombres de los jugadores en cada partida
        fseek(origen,144, SEEK_CUR);
        fread(jugadores_list[i*2],sizeof(char[2][10]),1,origen);
        fseek(origen,28, SEEK_CUR);
    }

    while(flag){                             //entro en un loop donde muestro los nombres de las partidas
        if(kbhit()){
            switch((int) getch()){
                case 27: //esc
                    flag=0;
                    break;
                case 87: //w
                case 119:
                    if(opt-1<0) opt=nPartidas-1;
                    else opt--;
                    break;
                case 83: //s
                case 115:
                    if(opt+1>nPartidas-1) opt=0;
                    else opt++;
                    break;
                case 13: //enter
                    fclose(origen);                 //cierro el puntero original al archivo
                    origen = fopen(partidas,"rb");  //abro uno al archivo donde se guardan las partidas
                    destino = fopen(partidasTemp,"wb"); //otro al archivo destino donde estaran todas las partidas por continuar menos la elegida
                    fseek(origen,0,SEEK_END);       //calculo el tamaño del archivo
                    sz=ftell(origen);
                    rewind(origen);

                    sup=192*(opt+1);
                    inf=192*opt;


                    for(i=0;i<sz;i++){             //copio los datos al archivo destino a excepcion del bloque seleccionado
                        lug=ftell(origen);
                        if((lug<=sup)&&(lug>inf)){
                            fread(&dato,1,1,origen);
                        }else{
                            fread(&dato,1,1,origen);   
                            fwrite(&dato,1,1,destino);
                        }
                    }

                    fseek(origen,inf,SEEK_SET);   //saco los datos de la partida elegida
                    fread(tablero,sizeof(tablero),1,origen);
                    fread(jugadores,sizeof(jugadores),1,origen);
                    fread(valores,sizeof(valores),1,origen);
                    fread(&turno,sizeof(int),1,origen);

                    fclose(origen);              //cierro los punteros
                    fclose(destino);

                    system("rename data.dat dataDelet.dat");  //renombro el archivo origen
                    system("rename data.tmp data.dat");       //renombro el archivo destino al nombre del archivo origen
                    system("del dataDelet.dat");              //borro el archivo origen viejo
                    jugar(tablero,jugadores,valores,turno,1); //entro a la partida
                    return ;
                    break;
            }
            
            clearArrayChar(&c[0],nPartidas,32);
            c[opt]=62;

            printScreen=1;
        }
        if(printScreen){
            system("cls");
            printf("====== Partidas a continuar ======\n");
            for(i=0;i<nPartidas;i++){ //imprimo las partidas con el nombre de sus jugadores
                printf("%c %i - %s vs %s \n",c[i],i+1,jugadores_list[(i*2)],jugadores_list[(i*2)+1]);
            }
            printScreen=0;
        }
    }
    fclose(origen);
}

//funcion que muestra las partidas ganadas
void tablaPartidas(){
    FILE* origen;

    char tabla[]="./tabla_posiciones.dat";
    int sz,i;
    int numTabla;
    char jugadores[2][10];
    int turno;
    origen = fopen(tabla,"rb");
    if(origen == NULL){
        puts("el archivo no se pudo abrir");
        exit(1);
    }
    clear();
    fseek(origen,0,SEEK_END);
    sz=ftell(origen);
    printf("==== Partidas ganadas ====\n\n");
    if(sz!=0){
        numTabla=sz/24;
        rewind(origen);
        // 2 3 7
        for(i=0;i<numTabla;i++){
            fread(jugadores,sizeof(char[2][10]),1,origen);
            fread(&turno,sizeof(int),1,origen);
            printf("- ");
            SetColor(3);
            printf("%s ",jugadores[0]);
            SetColor(7);
            printf("le gano a ");
            SetColor(2);
            printf("%s ",jugadores[1]);
            SetColor(7);
            printf("en %i turnos\n",turno);
            // printf("- %s le gano a %s en %i turnos\n",jugadores[0],jugadores[1],turno);
        }
    }else{
        printf("no hay partidas ganas que mostrar.\n");
    }
    printf("\n(Para volver al menu aprete cualquier tecla)\n");
    while(!kbhit());
    fclose(origen);
}

/*
    cada "partida" tiene 192bytes:
    144b -> tablero
    20b  -> datos de los jugadores
    24b  -> array de marcadores
    4b   -> turno
*/
void guardarPartida(int tablero[][6], char jugadores[][10], int valores[], int turno,int abandonada,int ganador){
    FILE* pf;

    char partidas[]= "./partidas_guardadas.dat";
    char tablaGanadas[]= "./tabla_posiciones.dat";

    if(abandonada){
        pf=fopen(partidas,"ab");
        if(pf==NULL){
            puts("Error al abrir el archivo");
            exit(1);
        }else{
            fwrite(tablero,sizeof(int[6][6]),1,pf);
            fwrite(jugadores,sizeof(char[2][10]),1,pf);
            fwrite(valores,sizeof(int[6]),1,pf);
            fwrite(&turno,sizeof(int),1,pf);
        }
        fclose(pf);
    }else{
        pf=fopen(tablaGanadas,"ab");
        if(pf==NULL){
            puts("error al abrir el archivo");
            exit(1);
        }else{
            fwrite(jugadores,sizeof(char[2][10]),1,pf);
            fwrite(&turno,sizeof(int),1,pf);
        }
        fclose(pf);
    }
    
}


//funcion que revisa si la posicion que se eligio en el turno gana la partida o no
int gano(int tablero[][6],int x0,int y0){
    int mult[][2]= {{ 1,-1}, //ascendente
                    { 1, 0}, //horizontal
                    { 0, 1}, //vertical
                    {-1,-1}};//descendente
    int i,b,x,y;
    int contador=0;
    int jugador=tablero[y0][x0];
    for(i=0;i<4;i++){                 //reviso en un "cuadrado" de 5x5
        for(b=-2;b<3;b++){
            x=x0+(mult[i][0]*b);
            y=y0+(mult[i][1]*b);
            if(dominio(x,y,0,5,0,5)){ //si la coordenada esta en el dom
                if(contador<3){       //y el contador es menor a 3, lo que quiere decir que no gano
                    if(tablero[y][x]==jugador){  //reviso si esa coordenada esta marcada por el jugador
                        contador++;
                    }
                    else{                        //en caso contrario reinicio el contador
                        contador=0;
                    }
                }else{
                    return 1;         //devuelvo 1 si gano
                }
            }
        }
    }
    return 0;                         //devuelvo 0 si no paso nada
}

//funcion que revisa si se cumplen intervalos en x,y especificos
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