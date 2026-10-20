#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "fecha.h"
#include "turno.h"
#include "listaE_paciente.h"
#include "listaVO_turno.h"
//! a
// RETORNA NEGATIVO SI f1 < f2, CERO SI SON IGUALES, POSITIVO SI f1 > f2.
int compararFechas(Fecha f1, Fecha f2){
if (f1.mes!=f2.mes)        return f1.mes-f2.mes;
if (f1.dia!=f2.dia)        return f1.dia-f2.dia;
if (f1.hora!=f2.hora)      return f1.hora-f2.hora;
return f1.minuto-f2.minuto;
}

int esDiaHabil(Fecha f){
    int ds=diaSemana(f);
    if (ds>=1&&ds<=5){
        return 1;
        }
    return 0;
}

int diaEnMes(int mes){
switch(mes){

case 11: // CASOS DE MESES CON 30 DIAS.
    return 30;
case 12:// CASO DE DICIEMBRE, RETORNA 31 DIAS.
    return 31;
    }
}
int diaSemana(Fecha f){
    int diaDelAnio=f.dia;
    int m;
//SUMA LOS DIAS DE LOS MESES ANTERIORES EN 2026
for (m=1;m<f.mes;m++){
    diaDelAnio+=diaEnMes(m);
    }
//FORMULA: (DIAS+3)%7
return (diaDelAnio+3)%7;
}

void mostrarFecha(Fecha f){
    printf("%02d/%02d/%d %02d:%02d hs [%s]",
       f.dia, f.mes, f.anio, f.hora, f.minuto,
       (f.disponible==LIBRE)?"Libre":"Ocupado");
}
Turno cargaTurno(Turno aux){
    initTurno(&aux);
    int dni;
    printf("DNI?\n");
    scanf("%d", &dni);
    setDniPacienteTurno(&aux, dni);
}

void inicializarAgenda(Fecha agenda[]){
int pos=0;
int mes, dia, hora, min;
int max_dias=(mes==11) ?30 :31;
for(mes=11;mes<=12;mes++){
    }
    for (dia=1;dia<=max_dias;dia++){
        Fecha f_prueba=creaFecha(dia, mes, 8,0,LIBRE);
        if (esDiaHabil(f_prueba)){
            for(hora=8;hora<13;hora++){
                for(min=0;min<=30;min+=30){
                    agenda[pos]=creaFecha(dia, mes, hora, min, LIBRE);
                    pos++;
                }
            }
        }

    }
}
int main(){
    Fecha agenda[390];
    inicializarAgenda(agenda);
    int i;
    for(i=0;i<390;i++){
        Fecha aux;
        aux=agenda[i];
        printf("=========================\n");
        printf("Fecha #%d\n", i);
        printf("Dia: %d\n", getDia(aux));
    }
    return 0;
}
