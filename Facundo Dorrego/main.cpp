#include <iostream>
#include <ctime>
#include <unordered_map>
#include "rlutil.h"
#include "dadosfacu.h"
#include "funciones.h"
#define waitkey rlutil::anykey("Presiona cualquier tecla para lanzar\n")
using namespace std;
int main(){
    rlutil::setConsoleTitle("Juego de dados Facundo Dorrego");
    rlutil::saveDefaultColor();
    srand(time(0));
    int dado1[6];
    int ronda=1,puntajeRonda=0,puntajeRonda2=0,puntajeTotal=0,puntajeTotal2=0,puntajeTotalMax=0,suma=0,resultado=0,numM,numJugadores=0,accion=1;
    bool gano=false,encontrado=false,trio=false,sextetoX=false,sexteto6=false,escalera=false,dosJugadores=false,turnoJug2=false,ganoJ2=false,fin=false;
    char nombreJug[10]={0},nombreJug2[10]={0},nombreJugMax[10]={0} ,opcion,decision;
    //Ronda
    while(fin!=true){
            const rlutil::CursorHider hider;
            recuadro(38,5,45,20,cBLANCO,cNEGRO);
            //menu bienvenidos + opciones +  nombre jugador con mas puntaje y su puntaje
            menuPrin();
            gotoxy(72,8);
            cout<<nombreJugMax;
            gotoxy(57,9);
            cout<<puntajeTotalMax;
            gotoxy(49,17);
            cin>>numJugadores;
            rlutil::cls();
            while(gano!=true){
                    switch (numJugadores){
                        case 1:{
                            dosJugadores=false;
                            nombreUnJug(nombreJug);
                            const rlutil::CursorHider hider;
                            recuadro(38,5,45,20,cBLANCO,cNEGRO);
                            modosOpc();
                            cin>>opcion;
                            gotoxy(40,13);
                            waitkey;
                            rlutil::cls();
                            break;
                            }

                        case 2:{
                            dosJugadores=true;
                            nombreDosJug(nombreJug,nombreJug2);
                            const rlutil::CursorHider hider;
                            recuadro(38,5,45,20,cBLANCO,cNEGRO);
                            modosOpc();
                            cin>>opcion;
                            gotoxy(40,13);
                            waitkey;
                            rlutil::cls();
                            break;
                            }

                        case 0: {
                            return 0;
                            break;
                            }
                    }
                while(ronda!=0){
                        //reseteo ronda puntaje
                        puntajeRonda=0;
                        puntajeRonda2=0;
                        //3 lanzamientos
                        for(int i = 0; i<3;i++){
                            //reseteo de combinaciones
                            trio=false,sextetoX=false,sexteto6=false,encontrado=false,escalera=false;
                            if (turnoJug2==true){
                                hud();
                                gotoxy(45,9);
                                cout<<nombreJug2;
                                gotoxy(66,9);
                                cout<<ronda;
                                gotoxy(85,9);
                                cout<<puntajeTotal2;
                                gotoxy(64,11);
                                cout<<puntajeRonda2;
                                gotoxy(51,12);
                                cout<<i+1;
                                }
                            if (turnoJug2==false){
                                hud();
                                gotoxy(45,9);
                                cout<<nombreJug;
                                gotoxy(66,9);
                                cout<<ronda;
                                gotoxy(85,9);
                                cout<<puntajeTotal;
                                gotoxy(64,11);
                                cout<<puntajeRonda;
                                gotoxy(51,12);
                                cout<<i+1;
                                }
                            switch (opcion){
                                case 'M':
                                case 'm':
                                    dadoManual(dado1);
                                    break;

                                case 'A':
                                case 'a':
                                    tirarDado1(dado1);
                                    break;

                                default:
                                    rlutil::setColor(4);
                                    cout<<"Opcion incorrecta.";
                                    return 0;
                                    break;
                                    }
                            // Cuenta las repeticiones de cada número
                            std::unordered_map<int, int> repeticiones;
                            for (int i = 0; i < 6; ++i) {
                                    repeticiones[dado1[i]]++;
                            }
                            // Verificar si algún número se repite 3 o más veces
                            for (const auto& par : repeticiones){
                                    //Sexteto6--
                                    if (par.second == 6 && par.first == 6){
                                        if(turnoJug2==false){
                                            sexteto6=true;
                                            puntajeRonda=sextetoSeis();
                                        }
                                        if(turnoJug2==true){
                                            sexteto6=true;
                                            puntajeRonda2=sextetoSeis();
                                        }
                                    }
                                    //SextetoX
                                    if (par.second == 6 && par.first != 6&&escalera==false&&sexteto6==false){
                                        if(turnoJug2==false){
                                            sextetoX=true;
                                            puntajeRonda+=sextetoX1(repeticiones);
                                        }
                                        if(turnoJug2==true){
                                            sextetoX=true;
                                            puntajeRonda2+=sextetoX1(repeticiones);
                                        }
                                    }
                                    //TrioX
                                    if (par.second >= 3&&sextetoX==false&&escalera==false&&sexteto6==false){
                                        if(turnoJug2==false){
                                            trio=true;
                                            puntajeRonda+=trioX1(repeticiones);
                                        }
                                        if(turnoJug2==true){
                                            trio=true;
                                            puntajeRonda2+=trioX1(repeticiones);
                                        }
                                    }
                                }
                            //Escalera
                            if(tieneEscalera(repeticiones)){
                                if(turnoJug2==false){
                                    ganoJ2=false;
                                    escalera = true;
                                    gano=true;
                                    ronda=0;
                                    gotoxy(35,20);
                                    rlutil::setColor(2);
                                    cout<<"Escalera";
                                    gotoxy(35,21);
                                    rlutil::resetColor();
                                    system("pause");
                                    rlutil::cls();
                                    break;
                                }
                                if(turnoJug2==true){
                                    ganoJ2=true;
                                    escalera = true;
                                    gano=true;
                                    ronda=0;
                                    gotoxy(35,20);
                                    rlutil::setColor(2);
                                    cout<<"Escalera";
                                    gotoxy(35,21);
                                    rlutil::resetColor();
                                    system("pause");
                                    rlutil::cls();
                                    break;
                                }
                            }
                            //Suma de dados
                            if(trio==false&&sextetoX==false&&sexteto6==false&&escalera==false){
                                    if(turnoJug2==false){
                                        puntajeRonda+=sumarValores(repeticiones);
                                        rlutil::setColor(2);
                                        gotoxy(35,20);
                                        cout<<"Suma de dados"<<endl;
                                        rlutil::resetColor();
                                    }
                                    if(turnoJug2==true){
                                        puntajeRonda2+=sumarValores(repeticiones);
                                        rlutil::setColor(2);
                                        gotoxy(35,20);
                                        cout<<"Suma de dados"<<endl;
                                        rlutil::resetColor();
                                    }
                                }
                            gotoxy(35,21);
                            waitkey;
                            rlutil::cls();
                        }
                    //Puntaje total
                    if(turnoJug2==false){
                        puntajeTotal+=puntajeRonda;
                    }
                    if(turnoJug2==true){
                        puntajeTotal2+=puntajeRonda2;
                    }
                    //Entre turno y Cambio de turno
                    if(dosJugadores==true){
                        dibuCuad();
                        rlutil::CursorHider hider;
                        if(turnoJug2 == false&&escalera==false){
                            cambioTurno();
                            gotoxy(60,12);
                            cout<<ronda;
                            gotoxy(66,13);
                            cout<<nombreJug2;
                            gotoxy(58,15);
                            cout<<nombreJug;
                            gotoxy(68,15);
                            cout<<puntajeTotal;
                            gotoxy(58,16);
                            cout<<nombreJug2;
                            gotoxy(68,16);
                            cout<<puntajeTotal2;
                            gotoxy(30,21);
                            turnoJug2 = true;
                            ronda=ronda-1;
                            waitkey;
                            rlutil::cls();
                        }
                        else{
                            cambioTurno();
                            gotoxy(60,12);
                            cout<<ronda+1;
                            gotoxy(66,13);
                            cout<<nombreJug;
                            gotoxy(58,15);
                            cout<<nombreJug2;
                            gotoxy(68,15);
                            cout<<puntajeTotal2;
                            gotoxy(58,16);
                            cout<<nombreJug;
                            gotoxy(68,16);
                            cout<<puntajeTotal;
                            gotoxy(30,21);
                            turnoJug2 = false;
                            waitkey;
                            rlutil::cls();
                        }
                    }
                    if(dosJugadores==false){
                        dibuCuad();
                        rlutil::CursorHider hider;
                        entreTurno();
                        gotoxy(58,12);
                        cout<<ronda;
                        gotoxy(69,14);
                        cout<<nombreJug;
                        gotoxy(60,16);
                        cout<<nombreJug;
                        gotoxy(71,16);
                        cout<<puntajeTotal;
                        gotoxy(30,21);
                        waitkey;
                        rlutil::cls();
                    }
                    //Contador de rondas
                    ronda++;
                    if (escalera==true){
                        if(ganoJ2==false){
                            gano=true;
                            ronda=0;
                            rlutil::setColor(2);
                            gotoxy(35,10);
                            cout<<"¡El jugador 1 ha sacado una escalera!"<<endl;
                            rlutil::resetColor();
                        }
                        if(ganoJ2==true){
                            gano=true;
                            ronda=0;
                            rlutil::setColor(2);
                            gotoxy(35,10);
                            cout<<"¡El jugador 2 ha sacado una escalera!"<<endl;
                            rlutil::resetColor();
                        }
                    }
                    //Maximo puntaje
                    if(dosJugadores==false){
                        if(puntajeTotal>=500){
                            rlutil::cls();
                            rlutil::setColor(2);
                            gotoxy(35,10);
                            cout<<"Has llegado al maximo puntaje :)"<<endl;
                            rlutil::resetColor();
                            gano=true;
                            ronda=0;
                        }
                    }
                    if(dosJugadores==true){
                        if(puntajeTotal>=500||puntajeTotal2>=500){
                            if(puntajeTotal>puntajeTotal2){
                                rlutil::cls();
                                rlutil::setColor(2);
                                gotoxy(35,10);
                                cout<<"El jugador uno llego al maximo puntaje"<<endl;
                                rlutil::resetColor();
                                ganoJ2=false;
                                gano=true;
                                ronda=0;
                            }
                            if(puntajeTotal2>puntajeTotal){
                                rlutil::cls();
                                rlutil::setColor(2);
                                gotoxy(35,10);
                                cout<<"El jugador dos llego al maximo puntaje"<<endl;
                                rlutil::resetColor();
                                ganoJ2=true;
                                gano=true;
                                ronda=0;
                            }
                        }
                    }
                }
            }
            if(puntajeTotalMax<puntajeTotal){
                for(int i=0;i<10;i++){
                    nombreJugMax[i]=nombreJug[i];
                }
                puntajeTotalMax=puntajeTotal;
            }
            if(puntajeTotalMax<puntajeTotal2){
                for(int i=0;i<10;i++){
                    nombreJugMax[i]=nombreJug2[i];
                }
                puntajeTotalMax=puntajeTotal2;
            }
            gotoxy(35,11);
            system("pause");
            rlutil::cls();
            if(ganoJ2==false){
                rlutil::setColor(3);
                gotoxy(35,10);
                cout<<"Gano el jugador 1. "<<nombreJug<<" tu puntaje fue de: "<<puntajeTotal<<endl;
                rlutil::resetColor();
            }
            if(ganoJ2==true){
                rlutil::setColor(3);
                gotoxy(35,10);
                cout<<"Gano el jugador 2. "<<nombreJug2<<" tu puntaje fue de: "<<puntajeTotal2<<endl;
                rlutil::resetColor();
            }
            gotoxy(35,11);
            system("pause");
            rlutil::cls();
            recuadro(38,5,45,20,cBLANCO,cNEGRO);
            gotoxy(40,13);
            cout<<"¿Desea jugar otra vez? (Y = si, N = no): ";
            cin>>decision;
            rlutil::cls();
            switch (decision){
                case 'y':
                case 'Y':
                    puntajeTotal=0;
                    puntajeTotal2=0;
                    gano=false;
                    ronda=1;
                    break;

                case  'n':
                case  'N':
                    fin=false;
                    return 0;
                    break;
                    }
            rlutil::cls();
    }
}
