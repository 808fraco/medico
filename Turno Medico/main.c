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
void mostrarDatosTurno(Turno t, Fecha agenda[]){
    printf("ID del turno: %d\n", getIdTurno(t));

    switch(getMutualTurno(t)){
        case 1:printf("Mutual: ANSES.\n");break;
        case 2:printf("Mutual: DOSEP.\n");break;
        case 3:printf("Mutual: OSDE.\n");break;
        case 4:printf("Mutual: OSFATUN.\n");break;
    }
    mostrarFecha(agenda[getIdTurno(t)]);
    switch(getEstadoTurno(t)){
        case 1:printf("Estado: SOLICITADO.\n");break;
        case 2:printf("Estado: CONFIRMADO.\n");
            printf("Monto: %f\n", getMontoTurno(t));
            break;
        case 3:printf("Estado: ATENDIDO.\n");break;
        case 4:printf("Estado: CANCELADO.\n");break;
    }
}
void mostrarPaciente(Paciente p){
char *nom=getNombre(p);
char *ape=getApellido(p);

        printf("Nombre: %s", nom);
        printf("Apellido: %s", ape);
        printf("N%cmero de DNI: %d\n",163, getDNI(p));
        if(getOSocial(p)){
            printf("Obra social: Si tiene.\n");
        }else{
            printf("Obra social: No tiene.\n");
        }
free(nom);
free(ape);
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
void solicitarUnTurno(Lista *vo, LPaciente *l, Fecha agenda[]){
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

    while (!isOol(*vo) && compararFechas(getFechaTurno(copyL(*vo)), agenda[id]) < 0) {
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
//! c)
int mostrarTurnoPorDNI(Lista l, Fecha agenda[], int dni){
    Turno t;
    resetL(&l);
    while(!isOol(l)){
        t = copyL(l);
        if(dni==getDniPacienteTurno(t)){
            break;
        }
        forwardL(&l);
    }
    if(isOol(l)){
        return 0;
    }else{
        mostrarDatosTurno(t, agenda);
        return 1;
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

//! e)
int buscarTurnoPorID(Lista *vo, int idBuscado){
resetL(vo);
while(!isOol(*vo)){
    Turno t= copyL(*vo);
    if (getIdTurno(t)==idBuscado){
        return 1;//EL CURSOR DE *vo QUEDA PARADO SOBRE EL TURNO
    }
    forwardL(vo);
    }
return 0;
}
//! f)
void mostrarTurnoBuscado(Lista *vo, Fecha agenda[]){
int id;
printf("Ingrese el ID del turno a buscar: ");
scanf("%d", &id);
limite(0, 389, &id);

if(buscarTurnoPorID(vo, id)){
    Turno t=copyL(*vo);
    mostrarDatosTurno(t, agenda);
    }else {
        printf("El turno con ID %d, no existe en la lista. \n", id);
    }
}
//! g)
int confirmarTurno(Lista *vo, LPaciente l){
int id;
Turno t;
Paciente p;

printf("Ingrese el ID del turno a confirmar: ");
scanf("%d", &id);
limite(0,389,&id);

resetL(vo);
while(!isOol(*vo)){
    t=copyL(*vo);
    if(getIdTurno(t)==id){
        break;
    }
    forwardL(vo);
    }
    if(isOol(*vo)){
        printf("El turno ID no existe: %d\n", id);
        return 0;
    }
    if(getEstadoTurno(t) != SOLICITADO){ //Controla que el turno se encuentre solicitado
        printf("El turno no se encuentra solicitado.\n");
        return 0;
    }
    int dni = getDniPacienteTurno(t);
    reset(&l);
    while(!isOos(l)){
        p = copy(l);
        if(dni ==  getDNI(p)){
            break;
        }
        forwards(&l);
    }
    if(isOos(l)){
        printf("El DNI no se encuentra registrado dentro del sistema.\n");
        return 0;
    }
    float monto;
    int mutual;
    if(!getOSocial(p)){
        printf("Monto a pagar: \n");
        scanf("%f", &monto);
        setMontoTurno(&t, monto);
        setMutualTurno(&t, 0);
    }else{
        printf("Escoja mutual:\n");
        printf("1.ANSES\n2.DOSEP\n3.OSDE\n4.OSFATUN\n");
        scanf("%d", &mutual);
        limite(1,4,&mutual);
        setMutualTurno(&t,mutual);
        setMontoTurno(&t,0.0);
    }
setEstadoTurno(&t, CONFIRMADO);
supressL(vo);
insertL(vo, t);
printf("Turno Confirmado correctamente!\n");
return 1;
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
void mostrarPacientePorDNI(LPaciente lp, int dni){
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
        reset(&lp);
        while(!isOos(lp)){
        Paciente p=copy(lp);
        mostrarPaciente(p);
        forwards(&lp);
    }
    }

}
//! q)
void mostrarTodosPacientes(LPaciente lp){
    if (isEmpty(lp)){
    printf("No hay pacientes registrados en el sistema.");
    return;
    }
    printf("\n========================================\n");
    printf("     LISTA DE PACIENTES REGISTRADOS ");
    printf("\n========================================\n");
    int contador=0;
    reset(&lp);
    while(!isOos(lp)){
        Paciente p=copy(lp);
        printf("\nPaciente %d: \n", contador);
        mostrarPaciente(p);
        contador++;
        forwards(&lp);
    }
printf("\nTotal de clientes registrados: %d\n", contador);
}

//! r)
float calcularMontoMes(Lista l,int mesBuscado){
    float totalIngresado=0.0;
    int contadorTurnos=0;
    resetL(&l);
    while(!isOol(l)){
        Turno t=copyL(l);
        Fecha f=getFechaTurno(t);
        if (getMes(f)==mesBuscado&&(getEstadoTurno(t)==CONFIRMADO||getEstadoTurno(t)==ATENDIDO)){
            totalIngresado+=getMontoTurno(t);
            contadorTurnos++;
        }
        forwardL(&l);
    }
if (contadorTurnos>0){
    printf("\n========================================\n");
    printf("     RECAUDACION TOTAL DEL MES %d", mesBuscado);
    printf("\n========================================\n");
    printf("Turnos cobrados/atendidos: %d\n", contadorTurnos);
    printf("Monto total ingresado: $%.2f\n", totalIngresado);
    }else{
        printf("\nNo se Registraron ingresos ni turnos confirmados para el mes %d.\n", mesBuscado);
    }
return totalIngresado;
}
int main(){
    int TcargaActual = 0;
    Fecha agenda[390];
    LPaciente listaE;
    int dni_buscar;
    int mes_buscar;
    
    //! INICIALIZADORES:
    inic(&listaE);
    Lista VO;
    inicLista(&VO);
    inicializarAgenda(agenda);
    
    //! FUNCION PARA CARGAR UN PACIENTE:
    cargaPaciente(&listaE);

    //! FUNCION PARA SOLICITAR UN TURNO
    solicitarUnTurno(&VO, &listaE, agenda);
    
    //! FUNCION DE MOSTRAR TURNO POR ID:
    mostrarTurnoBuscado(&VO, agenda);
    
    //! FUNCION DE BUSCAR POR DNI:
    printf("Ingrese dni a buscar: ");
    scanf("%d", &dni_buscar);
    mostrarPacientePorDNI(listaE, dni_buscar);
    
    //! FUNCION PARA CONFIRMAR TURNO
    confirmarTurno(&VO, listaE);
    
    //! FUNCION PARA CALCULAR EL MONTO TOTAL DE UN MES:
    printf("Ingrese el mes a consultar recaudacion(11=Noviembre, 12=Diciembre): ");
    scanf("%d", &mes_buscar);
    limite(11,12,&mes_buscar);
    calcularMontoMes(VO, mes_buscar);
    
    //! FUNCION PARA MOSTRAR TODOS LOS PACIENTES:
    mostrarTodosPacientes(listaE);
    return 0;
}
