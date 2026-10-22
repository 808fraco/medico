#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "fecha.h"
#include "turno.h"
#include "listaE_paciente.h"
#include "listaVO_turno.h"


int buscarDia(Fecha f, dia){
    if(getDia(f)==dia){
        return 1;
    }else{
        return 0;
    }
}
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
int uniquedni(LPaciente p, int dni){
    int i,d;
    LPaciente auxi = p; // lista de paciente auxiliar para no alterar la lista actual
    Paciente aux; // paciente auxiliar que va actualizando durante el for
    if(isEmpty(p)){// si esta vacia, retornar 0
        return 0;
    }else{
        reset(&auxi); // reiniciar el cursor en 0
        while(!isOos(auxi)){
            aux = copy(auxi);
            if(getDNI(aux) == dni){
                return 1;
            }
            forwards(&auxi);
        }
    }
    return 0;
}
Turno cargaTurno(Turno aux){
    initTurno(&aux);
    int dni;
    printf("DNI?\n");
    scanf("%d", &dni);
    setDniPacienteTurno(&aux, dni);
    return aux; // Se agregó el return
}

int esFeriado(Fecha f){
    int feriados[5][2]={ {9,11}, {23,11}, {7,12}, {8,12}, {25,12} };// FERIADOS CON FORMATO ( {DIA, MES} ).
    int n=5; // CANTIDAD DE FERIADOS
    int i;
    for (i = 0; i < n; i++){
        if (f.dia==feriados[i][0] && f.mes==feriados[i][1]){
            return 1;
        }
    }
    return 0;
}

void inicializarAgenda(Fecha agenda[], Turno l){
    int pos = 0;
    int mes, dia, hora, min;
    int d=0;//Inicializo la variable auxiliar en 0 para el conteo de id turno.
    setIdTurno(&l, 0);//inicializa

    // Bucle principal de meses
    for(mes = 11; mes <= 12; mes++){
        int max_dias = (mes == 11) ? 30 : 31; // Se calcula dentro del bucle

        for (dia = 1; dia <= max_dias; dia++){
            Fecha f_prueba = creaFecha(dia, mes, 8, 0, LIBRE);
            if(esFeriado(f_prueba)){
                continue;
            }
            if (!esDiaHabil(f_prueba)){
                continue;
            }
                for(hora = 8; hora < 13; hora++){
                    for(min = 0; min <= 30; min += 30){
                        if (pos<390){
                        agenda[pos] = creaFecha(dia, mes, hora, min, LIBRE);
                        pos++;
                        d++;
                        setIdTurno(&l,d);
                        }
                    }
                }
        }
    }
}
void limite(int limInf, int limSup, int *dato){
    int d = *dato;
    while(d < limInf || d > limSup){
        printf("N%cmero invalido. Ingrese el n%cmero nuevamente.\n",163,163);
        scanf("%d", &d);
    }
    *dato = d;
}
void cargaPaciente(LPaciente *lp){ //funcion n
    //! Variables
    Paciente p;
    init(&p);
    int dni,o;
    char n[30], a[30];

    //! Carga de datos
    //Nombre
    printf("%cNombre del paciente?\n",168);
    fgets(n,30,stdin);
    setNombre(&p,n);

    //Apellido
    printf("%cApellido del paciente?\n",168);
    fgets(a,30,stdin);
    setApellido(&p,a);

    // Numero de DNI
    printf("%cN%cmero de DNI?\n", 168,163);
    scanf("%d", &dni);
    limite(10000000,99999999,&dni); // control de limite de numero de DNI
    while(uniquedni(*lp,dni) == 1){
            printf("El n%cmero de DNI ya est%c registrado en el sistema. Ingrese uno distinto correctamente.\n",163,160);
            scanf("%d", &dni);
            limite(10000000,99999999,&dni);
    }
    setDNI(&p,dni);
    // Obra social
    printf("%cEl paciente tiene obra social?\n[1. Si | 0. No]\n",168);
    scanf("%d",&o);
    limite(0,1,&o);
    getchar();
    setOSocial(&p,o);

    //! Insert en la lista
    if(isEmpty(*lp)){ // Si esta vacia, insertar en el principio
        insert(lp,p);
    }else{ // sino, avanzar hasta el final de la lista e insertar
        reset(lp);
        while(!isOos(*lp)){
            forwards(lp);
        }
        insert(lp,p);
    }
}

void mostrarPorDNI(LPaciente lp, int dni){
    LPaciente listaAux = lp;
    Paciente auxi;
    reset(&listaAux);
    while(!isOos(listaAux)){
        auxi = copy(listaAux);
        if(getDNI(auxi) == dni){
            break;
        }
        forwards(&listaAux);
    }
    if(isOos(listaAux)){
        printf("Error\n");
    }else{
        printf("Nombre: %s\n", getNombre(auxi));
    }

}

void mostrarPacientes(LPaciente lp){
LPaciente aux=lp;
Paciente auxi;
reset(&aux);
int i=0;
while(!isOos(aux)){
    auxi=copy(aux);

    printf("Paciente %d\n", i+1);
    printf("Nombre: %s", getNombre(auxi));
    printf("Apellido: %s", getApellido(auxi));
    printf("DNI: %d\n", getDNI(auxi));
    printf("Obra social: %s\n", (getOSocial(auxi)==1) ?"SI" :"NO");
    i++;
     forwards(&aux);
    }
    return;
}

void buscarYmostrar(Fecha agenda[], int mes, int dia){
Fecha deseada;
setMes(&deseada,mes);
setDia(&deseada,dia);
mostrarFecha(deseada);
int i,l;
for(i=0;i=390;i++){
    if(getDia(agenda[i] == dia && getMes(agenda[i]) == mes && getDisponible(agenda[i])== LIBRE){

    }




int main(){
    Fecha agenda[390];
    Turno ld;
    inicializarAgenda(agenda, ld);
    LPaciente listaE;
    inic(&listaE);
    cargaPaciente(&listaE);
    cargaPaciente(&listaE);
    mostrarPacientes(listaE);
    int i;
    for(i = 0; i < 390; i++){
        Fecha aux = agenda[i];
        printf("=========================\n");
        printf("Turno ID #%d -> ", i);
        mostrarFecha(aux);
    }

    return 0;
}

