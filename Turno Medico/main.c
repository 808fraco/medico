#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "fecha.h"
#include "turno.h"
#include "listaE_paciente.h"
#include "listaVO_turno.h"

// RETORNA NEGATIVO SI f1 < f2, CERO SI SON IGUALES, POSITIVO SI f1 > f2.
int compararFechas(Fecha f1, Fecha f2){
    if (f1.mes != f2.mes)   return f1.mes - f2.mes;
    if (f1.dia != f2.dia)   return f1.dia - f2.dia;
    if (f1.hora != f2.hora) return f1.hora - f2.hora;
    return f1.minuto - f2.minuto;
}

// Devuelve los días de cualquier mes del año 2026 (año no bisiesto)
int diaEnMes(int mes){
    switch(mes){
        case 2: 
            return 28; // Febrero 2026
        case 4: case 6: case 9: case 11:
            return 30; // Meses de 30 días
        default:
            return 31; // Meses de 31 días
    }
}

// Calcula el día de la semana para 2026 (1=Lunes, ..., 5=Viernes, 6=Sábado, 0=Domingo)
int diaSemana(Fecha f){
    int diaDelAnio = f.dia;
    int m;
    // SUMA LOS DIAS DE LOS MESES ANTERIORES EN 2026
    for (m = 1; m < f.mes; m++){
        diaDelAnio += diaEnMes(m);
    }
    // FORMULA PARA 2026
    return (diaDelAnio + 3) % 7;
}

int esDiaHabil(Fecha f){
    int ds = diaSemana(f);
    if (ds >= 1 && ds <= 5){ // Lunes (1) a Viernes (5)
        return 1;
    }
    return 0;
}

void mostrarFecha(Fecha f){
    printf("%02d/%02d/%d %02d:%02d hs [%s]\n",
       f.dia, f.mes, f.anio, f.hora, f.minuto,
       (f.disponible == LIBRE) ? "Libre" : "Ocupado");
}

Turno cargaTurno(Turno aux){
    initTurno(&aux);
    int dni;
    printf("DNI?\n");
    scanf("%d", &dni);
    setDniPacienteTurno(&aux, dni);
    return aux; // Se agregó el return
}

void inicializarAgenda(Fecha agenda[]){
    int pos = 0;
    int mes, dia, hora, min;

    // Bucle principal de meses
    for(mes = 11; mes <= 12; mes++){
        int max_dias = (mes == 11) ? 30 : 31; // Se calcula dentro del bucle
        
        for (dia = 1; dia <= max_dias; dia++){
            Fecha f_prueba = creaFecha(dia, mes, 8, 0, LIBRE);
            
            if (esDiaHabil(f_prueba)){
                for(hora = 8; hora < 13; hora++){
                    for(min = 0; min <= 30; min += 30){
                        agenda[pos] = creaFecha(dia, mes, hora, min, LIBRE);
                        pos++;
                    }
                }
            }
        }
    }
}

int main(){
    Fecha agenda[390];
    inicializarAgenda(agenda);
    
    int i;
    for(i = 0; i < 390; i++){
        Fecha aux = agenda[i];
        printf("=========================\n");
        printf("Turno ID #%d -> ", i);
        mostrarFecha(aux);
    }
    
    return 0;
}


