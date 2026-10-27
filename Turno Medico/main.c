#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "fecha.h"
#include "turno.h"
#include "listaE_paciente.h"
#include "listaVO_turno.h"
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
void limite(int limInf, int limSup, int *dato){
    int d = *dato;
    while(d < limInf || d > limSup){
        printf("Numero invalido. Ingrese el numero nuevamente.\n");
        scanf("%d", &d);
    }
    *dato = d;
}
int uniquedni(LPaciente p, int dni){
    Paciente aux; // paciente auxiliar que va actualizando durante el for
    if(isEmpty(p)){// si esta vacia, retornar 0
        return 0;
    }else{
        reset(&p); // reiniciar el cursor en 0
        while(!isOos(p)){
            aux = copy(p);
            if(getDNI(aux) == dni){
                return 1;
            }
            forwards(&p);
        }
    }
    return 0;
}
//! REV
void mostrarFechaPorPagina(Fecha agenda[]){
    int libres[390];
    int cantLibres = 0,i;
    for(i=0;i<390;i++){
        if(getDisponible(agenda[i]) == LIBRE){
            libres[i] = cantLibres;
            cantLibres++;
        }
    }
}

void cargaPaciente(LPaciente *lp);



 //! a)
void solicitarUnTurno(Lista *vo, LPaciente *l, Fecha agenda[])
{
    int dni, opcion, id, i;
    Turno t;

    printf("Numero de DNI del paciente: "); // pedir DNI
    scanf("%d", &dni);
    limite(10000000, 99999999, &dni);

    if (!uniquedni(*l, dni)) { // verificar si existe
        printf("El paciente no esta registrado.\n");
        printf("Desea cargarlo? (1: Si / 0: No): ");
        scanf("%d", &opcion);
        limite(0, 1, &opcion);

        if (opcion == 0) {
            printf("Solicitud cancelada.\n");
            return;
        }

        getchar();
        cargaPaciente(l);

        if (!uniquedni(*l, dni)) { // controlar el DNI
            printf("El DNI no coincide. No se asigno el turno.\n");
            return;
        }
    }

    printf("\nFechas disponibles:\n"); // mostrar fechas libres

    for (i = 0; i < 390; i++) {    //usar el mostrarfechaporpagina aca
        if (getDisponible(agenda[i]) == LIBRE) {
            printf("ID: %d - ", i);
            mostrarFecha(agenda[i]);
        }
    }

    printf("Ingrese el ID del turno: "); // elegir horario
    scanf("%d", &id);

    while (id < 0 || id >= 390 || getDisponible(agenda[id]) != LIBRE) {
        printf("ID invalido o turno ocupado. Ingrese otro: ");
        scanf("%d", &id);
    }
    initTurno(&t);
    setIdTurno(&t, id);
    setDniPacienteTurno(&t, dni);
    setFechaTurno(&t, agenda[id]);
    setEstadoTurno(&t, SOLICITADO);

    resetL(vo);

    while (!isOol(*vo) &&
           compararFechas(getFechaTurno(copyL(*vo)), agenda[id]) < 0) {
        forwardL(vo);
    }

    insertL(vo, t); // insertar ordenado

    setDisponible(&agenda[id], OCUPADO); // ocupar fecha

    printf("\nTurno solicitado correctamente. ID: %d\n", id);
    printf("Fecha del turno asignado: ");
    mostrarFecha(agenda[id]);
}


//! b)
void fechaLibreEnAgenda(Fecha agenda[], int dia, int mes){
    int i,d=0;
    for(i=0;i<390;i++){
        if(getDia(agenda[i]) == dia && getMes(agenda[i]) == mes && getDisponible(agenda[i]) == LIBRE){
            printf("ID del turno: %d\n", i);
            mostrarFecha(agenda[i]);
            d=1;
        }
    }
    if(d==0){
        printf("No se encontr%c ninguna fecha libre en la agenda.\n",162);
    }
}
//! d)
void fechaOcupadaAgenda(Fecha agenda[], int mes){
    int i,d=0;
    for(i=0;i<390;i++){
        if(getMes(agenda[i]) == mes && getDisponible(agenda[i]) == OCUPADO){
            printf("ID del turno: %d\n", i);
            mostrarFecha(agenda[i]);
            d=1;
        }
    }
    if(d==0){
        printf("No se encontr%c ninguna fecha ocupada en la agenda\n",162);
    }
}
//! n)
void cargaPaciente(LPaciente *lp){
    //! Variables
    Paciente p;
    init(&p);
    int dni,o; // dAux es para el control de que el numero de DNI sea unico
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
    }else{ // sino, avanzar uno mas e insertar el paciente
        forwards(lp);
        insert(lp,p);
    }
}
//! o)
void inicializarAgenda(Fecha agenda[]){
    int pos = 0;
    int mes, dia, hora, min;

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
            if (esDiaHabil(f_prueba)|| !esFeriado(f_prueba)){
                for(hora = 8; hora < 13; hora++){
                    for(min = 0; min <= 30; min += 30){
                        if (pos<390){
                        agenda[pos] = creaFecha(dia, mes, hora, min, LIBRE);
                        pos++;
                        }
                    }
                }
            }
        }
    }
}
//! p)
void mostrarPorDNI(LPaciente lp, int dni){
    Paciente auxi;
    reset(&lp);
    while(!isOos(lp)){
        auxi = copy(lp);
        if(getDNI(auxi) == dni){
            break;
        }
        forwards(&lp);
    }
    if(isOos(lp)){
        printf("Error\n");
    }else{
        printf("---------DATOS DEL PACIENTE INGRESADO POR DNI--------------\n");
        printf("Nombre: %s", getNombre(auxi));
        printf("Apellido: %s", getApellido(auxi));
        printf("N%cmero de DNI: %d\n",163, getDNI(auxi));
        if(getOSocial(auxi)){
            printf("Obra social: Si tiene\n");
        }else{
            printf("Obra social: No tiene\n");
        }
    }

}


int main(){
    int TcargaActual = 0;
    Fecha agenda[390];
    LPaciente listaE;
    inic(&listaE);
    Lista VO;
    inicLista(&VO);
    inicializarAgenda(agenda);
    cargaPaciente(&listaE);
    solicitarUnTurno(&VO, &listaE, agenda);
    return 0;
}
