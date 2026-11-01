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
        if (getDia(f)==feriados[i][0] && getMes(f)==feriados[i][1]){
            return 1;
        }
    }
    return 0;
}

// RETORNA NEGATIVO SI f1 < f2, CERO SI SON IGUALES, POSITIVO SI f1 > f2.
int compararFechas(Fecha f1, Fecha f2){
    if (getMes(f1) != getMes(f2))   return getMes(f1) - getMes(f2);
    if (getDia(f1) != getDia(f2))   return getDia(f1) - getDia(f2);
    if (getHora(f1) != getHora(f2)) return getHora(f1) - getHora(f2);
    return getMinuto(f1) - getMinuto(f2);
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
    int diaDelAnio = getDia(f);
    int m;
    // SUMA LOS DIAS DE LOS MESES ANTERIORES EN 2026
    for (m = 1; m < getMes(f); m++){
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
       getDia(f), getMes(f), getAnio(f), getHora(f), getMinuto(f),
       (getDisponible(f) == LIBRE) ? "Libre" : "Ocupado");
}

int limite(int limInf, int limSup){
        int n,d; // n guarda el numero q se desea guardar | d es para el scanf (0 = el tipo de dato no coincide con el entero (%d)
        do{
            d = scanf("%d", &n);
            while(getchar() != '\n');
            if(d == 0){
                printf("Entrada invalida. Digite el dato correctamente.\n");
            }
            while(n < limInf || n > limSup){
                printf("Entrada invalida. Digite el dato correctamente.\n");
                d = scanf("%d", &n);
                while(getchar() != '\n');
            }
        }while(d != 1);
        return n;
}
int uniquedni(LPaciente p, int dni){
    Paciente aux; // paciente auxiliar que va actualizando durante el while
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
void mostrarUnTurno(Turno t){
    Fecha f;
    initFecha(&f);
    f = getFechaTurno(t);
    printf("ID del turno: %d\n", getIdTurno(t));
    printf("N%cmero de DNI: %d\n", 163, getDniPacienteTurno(t));
    printf("Monto: %f\n", getMontoTurno(t));
    switch(getMutualTurno(t)){
        case 1:printf("Mutual: ANSES.\n");break;
        case 2:printf("Mutual: DOSEP.\n");break;
        case 3:printf("Mutual: OSDE.\n");break;
        case 4:printf("Mutual: OSFATUN.\n");break;
    }
    printf("D%ca: %02d\nMes: %02d\nA%co: %02d\n", 160,getDia(f),getMes(f),164,getAnio(f));
    printf("Hora: %02d:%02d\n", getHora(f),getMinuto(f));
    switch(getEstadoTurno(t)){
        case 1:printf("Estado: SOLICITADO.\n");break;
        case 2:printf("Estado: CONFIRMADO.\n");break;
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

void cargaPaciente(LPaciente *lp, int dni);
void eliminarTurnosCancelados(Lista *t);

//! -------------------------------------------------------------------------------- FUNCIONES PRINCIPALES --------------------------------------------------------------------------------
//! a)
void solicitarUnTurno(Lista *vo, LPaciente *l, Fecha agenda[]){
    int dni, opcion, id, i;
    int libres = 0;
    int mostradas = 0;
    int contador = 0;
    Turno t;
    printf("Numero de DNI del paciente: "); // pedir DNI
    dni = limite(10000000,99999999);

    if (!uniquedni(*l, dni)) { // verifica si existe
        printf("El paciente no esta registrado.\n");
        printf("Desea cargarlo? (1: Si / 0: No): ");
        opcion = limite(0,1);

        if (opcion == 0) {
            printf("Solicitud cancelada.\n");
            return;
        }
        cargaPaciente(l, dni);

        if (!uniquedni(*l, dni)) { // controla el DNI
            printf("El DNI no coincide. No se asigno el turno.\n");
            return;
        }
    }

    // cuenta las fechas libres para saber si hay lugar
    for (i = 0; i < 390; i++) {
        if (getDisponible(agenda[i]) == LIBRE) {
            libres++;
        }
    }
    if (libres == 0) {
        printf("No hay fechas disponibles en la agenda.\n");
        return;
    }

    int seguir = 1;   // 1 = seguir mostrando, 0 = elegir ahora

    printf("\nFechas disponibles:\n");
    for (i = 0; i < 390 && seguir; i++) {
        if (getDisponible(agenda[i]) == LIBRE) {
            printf("ID: %d - ", i);
            mostrarFecha(agenda[i]);
            mostradas++;
            contador++;

            if (contador == 15 && mostradas < libres) {
                printf("\n1. Ver mas fechas | 0. Elegir un ID ahora\n>");
                seguir = limite(0, 1);
                contador = 0;
            }
        }
    }

    printf("Ingrese el ID del turno: "); // elegir horario
    id = limite(0,389);

    while (getDisponible(agenda[id]) != LIBRE) {
        printf("Turno ocupado. Ingrese otro ID: ");
        id = limite(0, 389);
    }
    setDisponible(&agenda[id], OCUPADO); // ocupar fecha

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
    int cant=0;
    initTurno(&t);
    resetL(&l);
    while(!isOol(l)){
        t = copyL(l);
        if(dni == getDniPacienteTurno(t)){
            mostrarDatosTurno(t, agenda);
            cant++;
        }
        forwardL(&l);
    }
    return cant;
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
id = limite(0,389);

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
initTurno(&t);
init(&p);

printf("Ingrese el ID del turno a confirmar: ");
id = limite(0,389);

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
    int ok;
    int mutual;
    if(!getOSocial(p)){
        printf("Monto a pagar: \n");
        ok= scanf("%f", &monto); //a ok se le guarda 1 o 0, 1=si leyo bien el monto, 0=si no leyo bien el monto
        while(getchar()!= '\n');
        while (ok!=1||monto<0){// control del monto
            printf("Monto invalido. Ingrese un numero mayor o igual a 0: ");
            ok=scanf("%f", &monto);
            while(getchar()!='\n');
        }
        setMontoTurno(&t, monto);
        setMutualTurno(&t, 0);
    }else{
        printf("Escoja mutual:\n");
        printf("1.ANSES\n2.DOSEP\n3.OSDE\n4.OSFATUN\n");
        mutual = limite(1,4);
        setMutualTurno(&t,mutual);
        setMontoTurno(&t,0.0);
    }
setEstadoTurno(&t, CONFIRMADO);
supressL(vo);
insertL(vo, t);
printf("Turno Confirmado correctamente!\n");
return 1;
}
//! h)
int cancelarTurno(Lista *t, Fecha agenda[], int dni){
    Turno tc;
    initTurno(&tc);
    int id;
    if(isEmptyL(*t)){ //Control por si no hay turnos registrados
        printf("No hay turnos registrados.\n");
        return 0;
    }
    resetL(t);
    while(!isOol(*t)){ //recorrido con while no este fuera de la lista y guardar el turno cancelado en la variable "tc" y comprobar que el dni sea igual al ingresado
        tc = copyL(*t);
        if(getDniPacienteTurno(tc) == dni){ //compara dni del turno con el ingresado
            id = getIdTurno(tc); //guarda la id del turno
            break;
        }
        forwardL(t);
    }
    if(isOol(*t)){ //si no encontro nada, imprimir esto
        printf("No hay turnos para cancelar.\n");
        return 0;
    }
    if(buscarTurnoPorID(t, id)==0){ // control para ver si hay un turno registrado en la agenda
        printf("No se encontro ninguna ID registrada en la agenda.\n");
        return 0;
    }
    if(getEstadoTurno(tc) == SOLICITADO || getEstadoTurno(tc) == CONFIRMADO){ // si esta solicitado o confirmado el turno
        setEstadoTurno(&tc,CANCELADO); // settear el estado del turno en cancelado
        setDisponible(&agenda[id], LIBRE); // settear disponible la agenda en la posicion del id turno
        supressL(t); // elimina el turno de la lista
        insertL(t,tc); // inserta el nuevo turno cancelado en la lista
        eliminarTurnosCancelados(t); // elimina el turno cancelado usando la funcion j
        printf("%cTurno cancelado exitosamente!\n",173);
        return 1;
    }
    return 0;
}
//! i)
void proximoPaciente(Lista *t, LPaciente p,Fecha agenda[], int dia, int mes){
    Paciente pp;
    Turno tc;
    init(&pp);
    initTurno(&tc);
    int o;
    if(isEmptyL(*t)){
        printf("No hay turnos registrados en el sistema.\n");
        return;
    }else if(isEmpty(p)){
        printf("No hay pacientes registrados en el sistema.\n");
        return;
    }
    resetL(t);
    while(!isOol(*t)){
        tc = copyL(*t);
        Fecha aux = getFechaTurno(tc);
        if(getEstadoTurno(tc) == CONFIRMADO && getDia(aux) == dia && getMes(aux) == mes){
            printf("paso el break;\n");
            break;
        }
        forwardL(t);
    }
    if(isOol(*t)){
        printf("no se encontro ningun turno.\n");
        return;
    }
    reset(&p);
    while(!isOos(p)){
        pp = copy(p);
        if(getDNI(pp) == getDniPacienteTurno(tc)){
            break;
        }
        forwards(&p);
    }
    if(isOos(p)){
        printf("No se encontro al paciente con el turno confirmado.\n");
        return;
    }
    int dni = getDNI(pp);

    printf("Datos del paciente en el turno:\n");
    mostrarPaciente(pp);
    printf("El paciente se encuentra en el consultorio?\n[1.Si | 0. No]\n");
    o = limite(0,1);
    if(o == 1){
        printf("!set estado\n");
        setEstadoTurno(&tc,ATENDIDO);
        supressL(t);
        insertL(t,tc);
        printf("exito!\n");
    }else{
        cancelarTurno(t,agenda,dni);
    }
}
//! j)
void eliminarTurnosCancelados(Lista *t){
    FILE *tc;
    tc = fopen("turno_cancelados.txt", "a");
    if(tc==NULL){
        return;
    }
    Turno tt;
    resetL(t);
    while(!isOol(*t)){
        tt = copyL(*t);
        if(getEstadoTurno(tt) == CANCELADO){
            Fecha f = getFechaTurno(tt);
            fprintf(tc,"\n");
            fprintf(tc, "ID del turno: %d\n", getIdTurno(tt));
            fprintf(tc, "Dia: %d\n", getDia(f));
            fprintf(tc, "Mes: %d\n", getMes(f));
            fprintf(tc, "Hora: %02d:%02d\n", getHora(f), (getMinuto(f)));
            fprintf(tc, "Estado: CANCELADO\n");
            supressL(t);
        }else{
            forwardL(t);
        }
    }
    fclose(tc);
}
//! k)
void mostrarTodosTurnosPagina(Lista l, Fecha agenda[]){

    Turno t;
    int contador = 0;
    int pagina = 1;

    if(isEmptyL(l)){ // Verifica si la lista esta vacia
        printf("No hay turnos registrados en el sistema.\n");
        return;
    }
    resetL(&l);  // Vuelve al inicio de la lista

    printf("\n--- PAGINA %d ---\n", pagina);

    while(!isOol(l)){ // Recorre todos los turnos de la lista

        t = copyL(l);  //copia el turno actual
        mostrarDatosTurno(t, agenda);
        contador++;
        forwardL(&l);  // Avanza al siguiente turno

        if(contador == 5 && !isOol(l)){  // Cada 5 turnos realizar una pausa

            printf("\nPresione ENTER para continuar...");
            getchar();
            pagina++;
            contador = 0;

            printf("\n--- PAGINA %d ---\n", pagina);
        }
    }
    printf("\nFin de la lista de turnos.\n");
}
//! l)
void mostrarTurnosMesRec(Lista l, Fecha agenda[], int mes){

    if(isOol(l)){   // Si llega al final de la lista. Termina la funcion
        return;
    }
    Turno t = copyL(l);
    Fecha f = getFechaTurno(t);
    int estado = getEstadoTurno(t);

    // Verifica si pertenece al mes y esta solicitado o confirmado
    if(getMes(f) == mes && (estado == SOLICITADO || estado == CONFIRMADO)){

        mostrarDatosTurno(t, agenda);
    }
    // Avanza al siguiente turno
    forwardL(&l);
    mostrarTurnosMesRec(l, agenda, mes);
}
//! m)
int contarTurnosAtendidos(Lista l, int dia, int mes){
    int suma = 0;

    if(isOol(l)){   // Si llega al final de la lista, termina
        return 0;
    }

    Turno t = copyL(l);
    Fecha f = getFechaTurno(t);

    // Verifica si el turno corresponde al dia, mes y esta atendido
    if(getDia(f) == dia && getMes(f) == mes && getEstadoTurno(t) == ATENDIDO){
        suma = 1;
    }
    forwardL(&l);

    return suma + contarTurnosAtendidos(l, dia, mes);   // Suma el resultado con los siguientes turnos
}
//! n)
void cargaPaciente(LPaciente *lp, int dni){
    //! Variables
    Paciente p;
    init(&p);
    int o;
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

    setDNI(&p,dni);

    // Obra social
    printf("%cEl paciente tiene obra social?\n[1. Si | 0. No]\n",168);
    o = limite(0, 1);
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
        mostrarPaciente(auxi);
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
//! -------------------------------------------------------------------------------- MENU DE OPCIONES --------------------------------------------------------------------------------
int gestionTurnos(Lista *VO, Fecha agenda[], LPaciente *listaE){
    int d,c, dia,mes;
    d=-1;
    Fecha f;
    initFecha(&f);
    while(d != 0){
        printf("---------------------- GESTION DE TURNOS ----------------------\n");
        printf(" 1. Solicitar un turno\n");
        printf(" 2. Confirmar un turno\n");
        printf(" 3. Cancelar un turno \n");
        printf(" 4. Mostrar el proximo paciente\n");
        printf(" 0. Regresar\n>");
        d = limite(0,4);
        switch(d){
            case 1: solicitarUnTurno(VO,listaE,agenda); return 1;
            break;
            case 2: if(isEmptyL(*VO)){
                        printf("No hay turnos registrados.\n");
                        return 0;
                    }else{
                        confirmarTurno(VO,*listaE); return 1;
                    }
            break;
            case 3: if(isEmptyL(*VO)){
                        printf("No hay turnos registrados.\n");
                        return 0;
                    }else{
                        printf("%cN%cmero de DNI del paciente?\n",168,163);
                        int dni = limite(10000000,99999999);
                        cancelarTurno(VO,agenda,dni);
                        return 1;
                    }
            break;
            case 4: if(isEmptyL(*VO)){
                        printf("No hay turnos registrados.\n");
                        return 0;
                    }else{
                        while(1){
                            printf("%cD%ca?\n", 168,161);
                            dia = limite(1,31);
                            setDia(&f,dia);
                            printf("%cMes?\n", 168);
                            mes = limite(11,12);
                            setMes(&f, mes);
                            if(esDiaHabil(f) == 0 || esFeriado(f) == 1){
                                printf("No es un d%ca h%cbil o laboral. Ingrese el d%ca correctamente.\n",161,160,161);
                                continue;
                            }else if(esDiaHabil(f) == 1 && esFeriado(f) == 0){
                                c=1;
                            }
                            if(c==1){

                                break;
                            }
                        }
                        proximoPaciente(VO,*listaE,agenda,dia,mes); return 1;
                    }
            break;
            case 0: return 0;
            break;
        }
    }
    return 1;
}
int main(){
    Fecha agenda[390];
    LPaciente listaE;
    int d;
    //! INICIALIZADORES:
    inic(&listaE);
    Lista VO;
    inicLista(&VO);
    inicializarAgenda(agenda);
    //! MENU PRINCIPAL
    while(d != 0){
        printf("---------------------- SISTEMA DE GESTION MEDICA ----------------------\n");
        printf(" 1. Gesti%cn de turnos\n",162);
        //agregar opciones..
        printf(" 0. Salir\n>");
        d = limite(0,1);
        switch(d){
            case 1: gestionTurnos(&VO,agenda,&listaE);
            break;
            case 2: return 0;
            break;
        }

    }
    return 0;
}
