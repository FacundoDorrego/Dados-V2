#ifndef DADOSFACU_H_INCLUDED
#define DADOSFACU_H_INCLUDED
#define waitkey rlutil::anykey("Presiona cualquier tecla para lanzar\n")
#include <unordered_map>
#include "rlutil.h"
using namespace std;
int tirarDado1(int dado1[6]);
int dadoManual(int dado1[6]);
int sextetoSeis();
int sextetoX1(const std::unordered_map<int, int>& repeticiones);
int trioX1(const std::unordered_map<int, int>& repeticiones);
int sumarValores(const std::unordered_map<int, int>& repeticiones);
bool tieneEscalera(const std::unordered_map<int, int>& repeticiones);
char nombreUnJug(char nombreJug1[10]);
char nombreDosJug(char nombreJug[10],char nombreJug2[10]);
char modosOpc();
void menuPrin();
void hud();
void cambioTurno();
void entreTurno();
void dibuCuad();

//Devuelve 6 valores aleatorios y los guarda en la lista del dado1
int tirarDado1(int dado1[6]){
    rlutil::saveDefaultColor();
    srand(time(0));
    for(int i = 0; i<6;i++){
            rlutil::CursorHider hider;
            dado1[i]=(rand()%(6)+1);
            rlutil::msleep(250);
            rlutil::setColor(dado1[i]);
            gotoxy(35,(14+i));
            cout<<"Dado"<<" "<<i+1<<": "<<dado1[i]<<endl;
            rlutil::resetColor();
    }
}

//Dado manual
int dadoManual(int dado1[6]){
    int numM;
    gotoxy(35,8);
    cout<<"Modo Manual"<<endl;
    for(int i = 0; i<6; i++){
            gotoxy(4,(14+i));
            cout<<"Ingrese numero manualmente: ";
            cin>>numM;
            dado1[i]=numM;
            gotoxy(35,(14+i));
            cout<<"Dado"<<" "<<i+1<<": "<<dado1[i]<<endl;
            }
}

//Escalera
bool tieneEscalera(const std::unordered_map<int, int>& repeticiones) {
    for (const auto& par : repeticiones) {
            if(par.second!=1){
                    return false;
            }
    }
    return true;
}


// Sumar los valores distintos o que no se repiten más de 2 veces
int sumarValores(const std::unordered_map<int, int>& repeticiones) {
    int suma = 0;
    for (const auto& par : repeticiones) {
        if (par.second <=2) {
            suma += par.first*par.second;
        }
    }
    return suma;
}

//Multiplica el valor que se repitio 6 veces
int sextetoX1(const std::unordered_map<int, int>& repeticiones){
    int resultado=0;
    for (const auto& par : repeticiones){
    resultado = par.first;
    rlutil::setColor(2);
    gotoxy(35,20);
    cout<<"Has sacado un Sexteto X"<<endl;
    rlutil::resetColor();
    }
    return resultado*50;
}

//Trio X
int trioX1(const std::unordered_map<int, int>& repeticiones){
int resultado=0;
    for (const auto& par : repeticiones){
            if(par.second>=3){
                resultado = par.first*10;
    rlutil::setColor(2);
    gotoxy(35,20);
    cout<<"Has sacado un Trio X"<<endl;
    rlutil::resetColor();
            }
    }
    return resultado;
}

//Cuadrado
void dibuCuad(){
    for(int i=0;i<11;i++){
        rlutil::CursorHider hider;
        rlutil::msleep(5);
        gotoxy(30,(9+i));
        cout<<"|";
        gotoxy(90,(9+i));
        cout<<"|";
        }
    for(int i=0;i<61;i++){
        rlutil::CursorHider hider;
        rlutil::msleep(5);
        gotoxy((30+i),8);
        cout<<"-";
        gotoxy((30+i),20);
        cout<<"-";
        }
}

//Sexteto 6--
int sextetoSeis(){
    int puntajeRonda=0;
    puntajeRonda=0;
    rlutil::setColor(4);
    gotoxy(35,20);
    cout<<"Has sacado un Sexteto de 6 :/"<<endl;
    rlutil::resetColor();
    return puntajeRonda;
}

//Nombre
char nombreUnJug(char nombreJug[10]){
     dibuCuad();
     gotoxy(40,10);
     cout<<"Ingrese su nombre (Maximo 10 caracteres)";
     gotoxy(55,15);
     cin>>nombreJug;
     rlutil::cls();
}

//Nombres dos jugadores
char nombreDosJug(char nombreJug[10],char nombreJug2[10]){
     dibuCuad();
     gotoxy(33,10);
     cout<<"Ingrese el nombre del jugador 1 (Maximo 10 caracteres)";
     gotoxy(55,15);
     cin>>nombreJug;
     rlutil::cls();
     dibuCuad();
     gotoxy(33,10);
     cout<<"Ingrese el nombre del jugador 2 (Maximo 10 caracteres)";
     gotoxy(55,15);
     cin>>nombreJug2;
     rlutil::cls();
}

//Menu principal
void menuPrin(){
    gotoxy(41,8);
    cout<<"Jugador con maxima puntuacion: "<<endl;
    gotoxy(41,9);
    cout<<"Puntaje Maximo: "<<endl;
    gotoxy(41,13);
    cout<<"1 jugador"<<endl;
    gotoxy(41,14);
    cout<<"2 jugadores"<<endl;
    gotoxy(41,15);
    cout<<"0 para salir"<<endl;
    gotoxy(41,17);
    cout<<"Opcion: ";
}

//Menu Automatico o Manual
char modosOpc(){
    gotoxy(40,10);
    cout<<"A: Modo Automatico"<<endl;
    gotoxy(40,11);
    cout<<"M: Modo manual"<<endl;
    gotoxy(40,12);
    cout<<"Opcion: ";
}

//Menu de juego
void hud(){
    const rlutil::CursorHider hider;
    gotoxy(35,9);
    cout<<"TURNO DE: ";
    gotoxy(53,9);
    cout<<" | ";
    gotoxy(57,9);
    cout<<"RONDA N: ";
    gotoxy(67,9);
    cout<<" | ";
    gotoxy(70,9);
    cout<<"PUNTAJE TOTAL: "<<endl;
    gotoxy(35,10);
    cout<<"---------------------------------------------------------"<<endl;
    gotoxy(35,11);
    cout<<"MAXIMO PUNTAJE DE LA RONDA: "<<endl;
    gotoxy(35,12);
    cout<<"LANZAMIENTO N: "<<endl;
    gotoxy(35,13);
    cout<<"---------------------------------------------------------"<<endl;
 }

 //Pantalla de cambio de turno (dos jugadores)
void cambioTurno(){
    gotoxy(50,12);
    cout<<"RONDA N: "<<endl;
    gotoxy(50,13);
    cout<<"Proximo turno: "<<endl;
    gotoxy(50,15);
    cout<<"Puntaje "<<endl;
    gotoxy(66,15);
    cout<<": "<<endl;
    gotoxy(50,16);
    cout<<"Puntaje "<<endl;
    gotoxy(66,16);
    cout<<": "<<endl;
}

//Pantalla de entre turn (un jugador)
void entreTurno(){
    gotoxy(49,12);
    cout<<"RONDA N: "<<endl;
    gotoxy(49,14);
    cout<<"Nombre del jugador: "<<endl;
    gotoxy(49,16);
    cout<<"Puntaje de "<<endl;
    gotoxy(68,16);
    cout<<": "<<endl;
}

#endif // DADOSFACU_H_INCLUDED
