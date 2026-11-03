#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "fecha.h"
#include "turno.h"
#include "listaE_paciente.h"
#include "listaVO_turno.h"
#define minDNI 10000000
#define maxDNI 99999999
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
    printf("%02d/%02d/%d %02d:%02d hs [%s]\n", //Formato dia/mes/año, hora/minuto e indica si esta "Libre" u "Ocupado".
       getDia(f), getMes(f), getAnio(f), getHora(f), getMinuto(f),
       (getDisponible(f) == LIBRE) ? "Libre" : "Ocupado");
}
int limite(int limInf, int limSup){
        int n,d = limInf-1; // n guarda el numero q se desea guardar | d es para el scanf (0 = el tipo de dato no coincide con el entero (%d)
        do{
            d = scanf("%d", &n);
            while(getchar() != '\n');
            while(n < limInf || n > limSup || d == 0){
                printf("ERROR: Entrada inv%clida. Digite el dato correctamente.\n>",160);
                d = scanf("%d", &n);
                while(getchar() != '\n');
            }
        }while(d != 1); // si el scanf devuelve 1, sale del while
        return n; // y retorna el numero controlado
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
int contarTurnosPaciente(Lista l, int dni){
    Turno t;
    initTurno(&t);
    int c = 0;
    resetL(&l);
    while(!isOol(l)){
        t = copyL(l);
        if(getDniPacienteTurno(t) == dni){
            c++;
        }
        forwardL(&l);
    }
    return c;
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
//! PROTOTIPOS
int fechaLibreEnAgenda(Fecha agenda[], int dia, int mes);
void cargaPaciente(LPaciente *lp, int dni);
int eliminarTurnosCancelados(Lista *t);

//! -------------------------------------------------------------------------------- FUNCIONES PRINCIPALES --------------------------------------------------------------------------------
//! a)
void solicitarUnTurno(Lista *vo, LPaciente *l, Fecha agenda[]){
    int dni, opcion, id, dia, mes, haylibres;
    Turno t;
    printf("Numero de DNI del paciente:\n>"); // pedir DNI
    dni = limite(10000000,99999999);

    if (!uniquedni(*l, dni)) { // si el DNI no existe en la lista de pacientes.
        printf("El paciente no esta registrado.\n");
        printf("Desea cargarlo? (1: Si / 0: No):\n>");
        opcion = limite(0,1);

        if (opcion == 0) {
            printf("Solicitud cancelada.\n");
            return;
        }
        cargaPaciente(l, dni);
    }

     // pide mes y dia hasta que haya horarios libres (0 en el mes para volver)
    do{
        printf("Mes del turno [11 o 12 | 0 para volver atr%cs]:\n>", 160);
        mes = limite(0,12);
        if(mes == 0){
            printf("Solicitud cancelada.\n");
            return;
        }
        if(mes < 11){
            printf("ERROR: Solo se atienden turnos en noviembre y diciembre.\n");
            haylibres = 0;
        }else{
            printf("Dia:\n>");
            dia = limite(1, diaEnMes(mes));
            haylibres = fechaLibreEnAgenda(agenda, dia, mes); // Busca y muestra los horarios libres para el dia y mes elegidos.
        }
    }while(haylibres == 0);


    printf("Ingrese el ID del turno:\n>"); // elegir horario
    id = limite(0,389);

     while (getDisponible(agenda[id]) != LIBRE || getDia(agenda[id]) != dia || getMes(agenda[id]) != mes) {
        printf("ID invalido o turno ocupado. Ingrese uno de la lista:\n>");
        id = limite(0,389);
    }
    setDisponible(&agenda[id], OCUPADO); // ocupar fecha

    initTurno(&t);
    setIdTurno(&t, id);
    setDniPacienteTurno(&t, dni);
    setFechaTurno(&t, agenda[id]);
    setEstadoTurno(&t, SOLICITADO);

    resetL(vo);

    // avanza mientras el cursor este dentro de la lista y la fecha del turno actual sea anterior a la nueva.
    while (!isOol(*vo) && compararFechas(getFechaTurno(copyL(*vo)), agenda[id]) < 0) {
        forwardL(vo);
    }

    insertL(vo, t); // insertar ordenado

    printf("\nTurno solicitado correctamente. ID: %d\n", id);
    printf("Fecha del turno asignado: ");
    mostrarFecha(agenda[id]);
}
//! b)
int fechaLibreEnAgenda(Fecha agenda[], int dia, int mes){
    int i,d=0;  //d indica si se encontro algun horario libre.
    for(i=0;i<390;i++){
         // comprueba que coincidan el dia, el mes y que el horario este libre.
        if(getDia(agenda[i]) == dia && getMes(agenda[i]) == mes && getDisponible(agenda[i]) == LIBRE){
            printf("ID del turno: %d\n", i);
            mostrarFecha(agenda[i]);
            d=1;   // indica que se encontro al menos un horario libre.
        }
    }
    if(d==0){
        printf("ERROR: No se encontr%c ninguna fecha libre en la agenda.\n",162);
    }
    return d;
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
        printf("ERROR: No se encontr%c ninguna fecha ocupada en la agenda.\n",162);
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
printf("Ingrese el ID del turno a buscar:\n>");
id = limite(0,389);

if(buscarTurnoPorID(vo, id)){
    Turno t=copyL(*vo);
    mostrarDatosTurno(t, agenda);
    }else {
        printf("El turno con el ID %d no est%c registrado en la lista. \n",id, 160);
    }
}
//! g)
int confirmarTurno(Lista *vo, LPaciente l){
int id;
Turno t;
Paciente p;
initTurno(&t);
init(&p);

printf("Ingrese el ID del turno a confirmar:\n>");
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
        printf("ERROR: El ID del turno ingresado no se encuentra registrado: %d\n", id);
        return 0;
    }
    if(getEstadoTurno(t) != SOLICITADO){ //Controla que el turno se encuentre solicitado
        printf("ERROR: El turno no se encuentra solicitado.\n");
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
        printf("ERROR: El DNI no se encuentra registrado dentro del sistema.\n");
        return 0;
    }
    float monto;
    int ok;
    int mutual;
    if(!getOSocial(p)){
        printf("Monto a pagar: \n>");
        ok= scanf("%f", &monto); //a ok se le guarda 1 o 0, 1=si leyo bien el monto, 0=si no leyo bien el monto
        while(getchar()!= '\n');
        while (ok!=1||monto<0){// control del monto
            printf("ERROR: Monto inv%clido. Ingrese un n%cmero mayor o igual a 0:\n>",160,163);
            ok=scanf("%f", &monto);
            while(getchar()!='\n');
        }
        setMontoTurno(&t, monto);
        setMutualTurno(&t, 0);
    }else{
        printf("Escoja mutual:\n");
        printf("1.ANSES\n2.DOSEP\n3.OSDE\n4.OSFATUN\n>");
        mutual = limite(1,4);
        setMutualTurno(&t,mutual);
        setMontoTurno(&t,0.0);
    }
setEstadoTurno(&t, CONFIRMADO);
supressL(vo);
insertL(vo, t);
printf("%cTurno Confirmado correctamente!\n",173);
return 1;
}
//! h)
int cancelarTurno(Lista *t, Fecha agenda[], int id){
    Turno tc;
    if(isEmptyL(*t)){ //Control por si no hay turnos registrados
        printf("ERROR: No hay turnos registrados.\n");
        return 0;
    }
    if(!buscarTurnoPorID(t, id)){
        printf("ERROR: No existe un turno con ID %d.\n", id);
        return 0;
    }
    tc=copyL(*t);
    if(getEstadoTurno(tc)!=SOLICITADO && getEstadoTurno(tc)!=CONFIRMADO){
        printf("ERROR: El turno no se pudo cancelar (ya atendido o cancelado).\n");
        return 0;
    }
    setEstadoTurno(&tc, CANCELADO);
    setDisponible(&agenda[id], LIBRE);
    supressL(t);
    insertL(t, tc);
    if(eliminarTurnosCancelados(t)==-1){
        return 0;
    }
        printf("%cTurno cancelado exitosamente!\n",173);
        return 1;
    }
//! i)
void proximoPaciente(Lista *t, LPaciente p,Fecha agenda[], int dia, int mes){
    Paciente pp;
    int id;
    Turno tc;
    init(&pp);
    initTurno(&tc);
    int o;
    if(isEmptyL(*t)){
        printf("ERROR: No hay turnos registrados en el sistema.\n");
        return;
    }else if(isEmpty(p)){
        printf("ERROR: No hay pacientes registrados en el sistema.\n");
        return;
    }
    resetL(t);
    while(!isOol(*t)){
        tc = copyL(*t);
        Fecha aux = getFechaTurno(tc);
        if(getEstadoTurno(tc) == CONFIRMADO && getDia(aux) == dia && getMes(aux) == mes){
            break;
        }
        forwardL(t);
    }
    if(isOol(*t)){
        printf("ERROR: No se encontr%c ning%cn turno.\n",162,163);
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
        printf("ERROR: No se encontro al paciente con el turno confirmado.\n");
        return;
    }

    printf("Datos del paciente en el turno:\n");
    mostrarPaciente(pp);
    printf("%cEl paciente se encuentra en el consultorio?\n[1.Si | 0. No]\n>",168);
    o = limite(0,1);
    id = getIdTurno(tc);
    if(o == 1){
        setEstadoTurno(&tc,ATENDIDO);
        supressL(t);
        insertL(t,tc);
        printf("%cEl paciente pas%c a estar atendido!\n",173,162);
    }else{
        cancelarTurno(t,agenda,id);
    }
}
//! j)
int eliminarTurnosCancelados(Lista *t){
    FILE *tc;
    Turno tt;
    Fecha f;
    int cant=0;

    tc = fopen("turno_cancelado.txt", "a");
    if(tc==NULL){
        printf("ERROR: No se pudo abrir el archivo %cturno_cancelado.txt%c.\n",34,34);
        return -1;
    }

    resetL(t);
    while(!isOol(*t)){
        tt = copyL(*t);
        if(getEstadoTurno(tt) == CANCELADO){
            f=   getFechaTurno(tt);
            fprintf(tc, "ID: %d | DNI: %d | Fecha: %02d/%02d/%d %02d:%02d | Monto: %.2f | Mutual: %d | Estado: CANCELADO\n",
                    getIdTurno(tt), getDniPacienteTurno(tt),
                    getDia(f), getMes(f), getAnio(f), getHora(f), getMinuto(f),
                    getMontoTurno(tt), getMutualTurno(tt));
            supressL(t);
            cant++;
        }else{
            forwardL(t);
        }
    }
    fclose(tc);
    return cant;
}
//! k)
void mostrarTodosTurnosPagina(Lista l, Fecha agenda[]){

    Turno t;
    int contador = 0;
    int pagina = 1;

    if(isEmptyL(l)){ // Verifica si la lista esta vacia
        printf("ERROR: No hay turnos registrados en el sistema.\n");
        return;
    }
    resetL(&l);  // Vuelve al inicio de la lista

    printf("\n--- P%cGINA %d ---\n", 181,pagina);

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

            printf("\n--- P%cGINA %d ---\n", 181,pagina);
        }
    }
    printf("\nFin de la lista de turnos.\n");
}
//! l)
void mostrarTurnosMesRec(Lista l, Fecha agenda[], int mes){

    if(isOol(l)){   // si el cursor esta fuera de la lista. termina
        return;
    }
    Turno t = copyL(l);
    Fecha f = getFechaTurno(t);
    int estado = getEstadoTurno(t);

    // verifica si pertenece al mes y esta solicitado o confirmado
    if(getMes(f) == mes && (estado == SOLICITADO || estado == CONFIRMADO)){

        mostrarDatosTurno(t, agenda);
    }
    // avanza al siguiente turno
    forwardL(&l);
    mostrarTurnosMesRec(l, agenda, mes);
}
//! m)
int contarTurnosAtendidos(Lista l, int dia, int mes){
    int suma = 0;

    if(isOol(l)){   // si el cursor esta fuera de la lista.
        return 0;
    }

    Turno t = copyL(l);
    Fecha f = getFechaTurno(t);

    // verifica si el turno corresponde al dia, mes y esta atendido
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
    printf("%cNombre del paciente?\n>",168);
    fgets(n,30,stdin);
    setNombre(&p,n);

    //Apellido
    printf("%cApellido del paciente?\n>",168);
    fgets(a,30,stdin);
    setApellido(&p,a);

    setDNI(&p,dni);

    // Obra social
    printf("%cEl paciente tiene obra social?\n[1. Si | 0. No]\n>",168);
    o = limite(0, 1);
    setOSocial(&p,o);

    //! Insert en la lista
    insert(lp,p);
}
//! ñ)
void eliminarPaciente(LPaciente *lp, Lista VO){
    Paciente p;
    Turno t;
    init(&p);
    initTurno(&t);
    int o,e=0, dniST; // e = encontrado, dniST = dni sin turno
    printf("%cN%cmero de DNI del paciente a eleminar?\n>",168,163);
    dniST = limite(minDNI,maxDNI);
    reset(lp);
    while(!isOos(*lp) && !e){
        p = copy(*lp);
        if(getDNI(p) == dniST){
            e=1;
        }else{
            forwards(lp);
        }
    }
    if(!e){
        printf("ERROR: No existe un paciente con ese n%cmero de DNI.\n",163);
        return;
    }
    if(contarTurnosPaciente(VO,dniST) > 0){
        printf("ERROR: El paciente tiene turnos registrados y no se puede eliminar.\n");
        return;
    }
    if(isOos(*lp)){
        printf("ERROR: El n%cmero de DNI ingresado no est%c registrado en el sistema.\n",163,160);
        return;
    }
    printf("DATOS DEL PACIENTE SIN TURNO:\n");
    mostrarPaciente(p);
    printf("%cDesea eliminar este registro del sistema?\n[1. Si | 0. No]\n>",168);
    o = limite(0,1);
    if(o==1){
        supress(lp);
        printf("%cRegistro eliminado con exito!\n",173);
        return;
    }
    printf("No se elimin%c el registro.\n",162);
    return;
}
//! o)
void inicializarAgenda(Fecha agenda[]){
    int pos = 0; // indica la posicion del arreglo donde se guardara cada horario.
    int mes, dia, hora, min;

    // Bucle principal de meses
    for(mes = 11; mes <= 12; mes++){
        int max_dias = (mes == 11) ? 30 : 31; // se calcula dentro del bucle

        for (dia = 1; dia <= max_dias; dia++){
            // se crea una fecha auxiliar para comprobar si el dia es habil o feriado.
            Fecha f_prueba = creaFecha(dia, mes, 8, 0, LIBRE);
            if(esFeriado(f_prueba)){
                continue; // si es feriado, pasa al siguiente dia.
            }
            if (!esDiaHabil(f_prueba)){
                continue; // si no es dia habil (sabado o domingo), pasa al siguiente dia.
            }
            for(hora = 8; hora < 13; hora++){
                for(min = 0; min <= 30; min += 30){
                    if (pos<390){ // comprueba que no se supere la capacidad del arreglo.
                    agenda[pos] = creaFecha(dia, mes, hora, min, LIBRE);
                    pos++; // avanza a la siguiente posicion del arreglo.
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
        printf("ERROR: No hay ning%cn paciente con el n%cmero de DNI ingresado.\n",163,163);
    }else{
        printf("---------DATOS DEL PACIENTE INGRESADO POR DNI--------------\n");
        mostrarPaciente(auxi);
    }
}
//! q)
void mostrarTodosPacientes(LPaciente lp){
    if (isEmpty(lp)){
    printf("ERROR: No hay pacientes registrados en el sistema.\n");
    return;
    }
    printf("\n========================================\n");
    printf("     LISTA DE PACIENTES REGISTRADOS ");
    printf("\n========================================\n");
    int contador=0;
    reset(&lp);
    while(!isOos(lp)){
        Paciente p=copy(lp);
        printf("\nPaciente %d: \n", contador+1);
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
        printf("\nERROR: No se registraron ingresos ni turnos confirmados para el mes %d.\n", mesBuscado);
    }
return totalIngresado;
}
//! s)
void backup(Lista l, LPaciente lp, Fecha agenda[]){
    FILE *archivo;
    Turno t;
    Fecha f;
    Paciente p;
    int i;

    archivo = fopen("turno.txt", "w");  // guarda los turnos en turno.txt

    if(archivo == NULL){
        printf("ERROR: No se pudo crear el archivo turno.txt\n");
        return;
    }
    resetL(&l); // vuelve al inicio de la lista de turnos.

    while(!isOol(l)){
        t = copyL(l);
        f = getFechaTurno(t); // obtiene su fecha.
        // guarda los datos del turno.
        fprintf(archivo, "%d %d %.2f %d %d %d %d %d %d %d\n",
            getIdTurno(t),
            getDniPacienteTurno(t),
            getMontoTurno(t),
            getMutualTurno(t),
            getEstadoTurno(t),
            getDia(f),
            getMes(f),
            getAnio(f),
            getHora(f),
            getMinuto(f));

        forwardL(&l); // avanza al siguiente turno.
    }

    fclose(archivo);

    archivo = fopen("pacientes.txt", "w"); //guarda los pacientes en pacientes.txt

    if(archivo == NULL){
        printf("ERROR: No se pudo crear el archivo pacientes.txt\n");
        return;
    }
    reset(&lp); // vuelve al inicio de la lista de pacientes.

    while(!isOos(lp)){ // recorre todos los pacientes.
        p = copy(lp);

        char *nom = getNombre(p);
        char *ape = getApellido(p);

        // guarda los datos del paciente.
        fprintf(archivo, "%s%s%d\n%d\n", nom, ape, getDNI(p), getOSocial(p));
        free(nom);
        free(ape);

        forwards(&lp); // avanza al siguiente paciente.
    }
    fclose(archivo);

    archivo = fopen("agenda.txt", "w"); // guarda la agenda en agenda.txt

    if(archivo == NULL){
        printf("ERROR: No se pudo crear el archivo agenda.txt\n");
        return;
    }

    for(i = 0; i < 390; i++){ // recorre las 390 posiciones de la agenda.
        f = agenda[i];

        // guarda los datos de cada fecha.
        fprintf(archivo, "%d %d %d %d %d %d\n",
            getDia(f),
            getMes(f),
            getAnio(f),
            getHora(f),
            getMinuto(f),
            getDisponible(f));
    }

    fclose(archivo);

    printf("BACKUP REALIZADO CORRECTAMENTE\n");
}

//! t)
void cargarBackup(Lista *vo, LPaciente *lp, Fecha agenda[]){
    FILE *archivo;

    // comprueba que existan los tres archivos antes de tocar nada
    archivo = fopen("pacientes.txt", "r");
    if(archivo == NULL){
        printf("No se encontro pacientes.txt. No se cargo nada.\n");
        return;
    }
    fclose(archivo);

    archivo = fopen("agenda.txt", "r");
    if(archivo == NULL){
        printf("No se encontro agenda.txt. No se cargo nada.\n");
        return;
    }
    fclose(archivo);

    archivo = fopen("turno.txt", "r");
    if(archivo == NULL){
        printf("No se encontro turno.txt. No se cargo nada.\n");
        return;
    }
    fclose(archivo);

    // vacia lo que haya cargado para no duplicar datos
    resetL(vo);
    while(!isOol(*vo)){
        supressL(vo);
    }
    inic(lp);

    // CARGAR LOS PACIENTES
    archivo = fopen("pacientes.txt", "r");

    if(archivo != NULL){
        char nom[30], ape[30];
        int dni, osocial;

        // lee los datos de los pacientes.
        while(fgets(nom, 30, archivo) != NULL){

            if(fgets(ape, 30, archivo) == NULL){
                break;
            }
            if(fscanf(archivo, "%d%d ", &dni, &osocial) != 2){
                break;
            }
            // crea el paciente y carga sus datos.
            Paciente p;
            init(&p);
            setNombre(&p, nom);
            setApellido(&p, ape);
            setDNI(&p, dni);
            setOSocial(&p, osocial);

            // inserta el paciente en la lista.
            if(!isFull(*lp)){
                if(isEmpty(*lp)){
                    insert(lp, p);
                }else{
                    forwards(lp);
                    insert(lp, p);
                }
            }
        }
        fclose(archivo);
        printf("Pacientes cargados correctamente.\n");

    }else{
        printf("No se encontro el archivo pacientes.txt\n");
    }
    // CARGAR LA AGENDA
    archivo = fopen("agenda.txt", "r");

    if(archivo != NULL){
        int i, dia, mes, anio, hora, min, disp;

        // lee las 390 fechas de la agenda.
        for(i = 0; i < 390; i++){

            if(fscanf(archivo, "%d %d %d %d %d %d",
                &dia, &mes, &anio, &hora, &min, &disp) == 6){

                agenda[i] = creaFecha(dia, mes, hora, min, disp);
            }
        }
        fclose(archivo);
        printf("Agenda cargada correctamente.\n");

    }else{
        printf("No se encontro el archivo agenda.txt\n");
    }

    // CARGAR LOS TURNOS
    archivo = fopen("turno.txt", "r");

    if(archivo != NULL){
        int id, dni, mutual, estado;
        int dia, mes, anio, hora, min;
        float monto;

        // lee los datos de cada turno.
        while(fscanf(archivo, "%d %d %f %d %d %d %d %d %d %d",
            &id, &dni, &monto, &mutual, &estado, &dia, &mes, &anio, &hora, &min) == 10){

            Turno t;
            Fecha f;

            // crea el turno y carga sus datos.
            initTurno(&t);

            setIdTurno(&t, id);
            setDniPacienteTurno(&t, dni);
            setMontoTurno(&t, monto);
            setMutualTurno(&t, mutual);
            setEstadoTurno(&t, estado);

            // crea la fecha del turno.
            f = creaFecha(dia, mes, hora, min, OCUPADO);
            setFechaTurno(&t, f);

            // marca la fecha como ocupada en la agenda.
            if(id >= 0 && id < 390){
                setDisponible(&agenda[id], OCUPADO);
            }
            // inserta el turno ordenado por fecha.
            resetL(vo);
            while(!isOol(*vo) &&
                compararFechas(getFechaTurno(copyL(*vo)), f) < 0){
                forwardL(vo);
            }
            insertL(vo, t);
        }
        fclose(archivo);
        printf("Turnos cargados correctamente.\n");

    }else{
        printf("No se encontro el archivo turno.txt\n");
    }

    printf(" DATOS RESTAURADOS CORRECTAMENTE\n");
}


//! -------------------------------------------------------------------------------- MENU DE OPCIONES --------------------------------------------------------------------------------
// Gestion de turnos
int gestionTurnos(Lista *VO, Fecha agenda[], LPaciente *listaE){
    int d,dia,mes;
    d=-1;
    Fecha f;
    initFecha(&f);
    while(d != 0){
        printf("==================== GESTI%cN DE TURNOS ====================\n",224);
        printf(" 1. Solicitar un turno\n");
        printf(" 2. Confirmar un turno\n");
        printf(" 3. Cancelar un turno \n");
        printf(" 4. Mostrar el pr%cximo paciente\n",162);
        printf(" 0. Regresar\n");
        printf("==========================================================\n>");
        d = limite(0,4);
        switch(d){
            case 1: solicitarUnTurno(VO,listaE,agenda); return 1;
            break;
            case 2: if(isEmptyL(*VO)){
                        printf("ERROR: No hay turnos registrados.\n");
                        return 0;
                    }else{
                        confirmarTurno(VO,*listaE); return 1;
                    }
            break;
            case 3: if(isEmptyL(*VO)){
                        printf("ERROR: No hay turnos registrados.\n");
                        return 0;
                    }else{
                        printf("%cN%cmero de ID del turno?\n>",168,163);
                        int id = limite(0,389);
                        cancelarTurno(VO,agenda,id);
                        return 1;
                    }
            break;
            case 4: if(isEmptyL(*VO)){
                        printf("ERROR: No hay turnos registrados.\n");
                        return 0;
                    }else{
                            do{
                            printf("%cMes?\n>", 168);
                            mes = limite(11,12);
                            printf("%cD%ca?\n>", 168,161);
                            dia = limite(1, diaEnMes(mes));
                            setMes(&f, mes);
                            setDia(&f,dia);
                            if(!esDiaHabil(f)|| esFeriado(f)){
                                printf("ERROR: No es un d%ca h%cbil o laboral. Ingrese el d%ca correctamente.\n",161,160,161);
                            }
                            }while(!esDiaHabil(f) || esFeriado(f));
                        proximoPaciente(VO,*listaE,agenda,dia,mes); return 1;
                    }
            break;
            case 0: return 0;
            break;
        }
    }
    return 1;
}
// Gestion de pacientes
void gestionPacientes(LPaciente *lp, Lista VO){
    int d = -1, dni;
    while(d != 0){
        printf("==================== GESTI%cN DE PACIENTES ====================\n",224);
        printf(" [1] Cargar un paciente\n");
        printf(" [2] Eliminar un paciente\n");
        printf(" [3] Buscar un paciente por n%cmero de DNI\n",163);
        printf(" [4] Mostrar todos los pacientes\n");
        printf(" [0] Regresar\n");
        printf("==============================================================\n>");
        d = limite(0,4);
        switch(d){
            case 1:
                printf("%cN%cmero de DNI?\n>", 168, 163);
                dni = limite(minDNI, maxDNI);
                if(uniquedni(*lp, dni)){
                    printf("ERROR: Ya existe un paciente con ese DNI.\n");
                }else{
                cargaPaciente(lp,dni);
                }
            break;
            case 2:
                if(isEmpty(*lp)){
                    printf("ERROR: No hay pacientes registrados.\n");
                }else{
                    eliminarPaciente(lp,VO);
                }
            break;
            case 3:
                if(isEmpty(*lp)){
                    printf("ERROR: No hay pacientes registrados.\n");
                    continue;
                }
                printf("%cN%cmero de DNI?\n>",168,163);
                dni=limite(minDNI, maxDNI);
                mostrarPacientePorDNI(*lp, dni);
                break;
            case 4:
                if(isEmpty(*lp)){
                    printf("ERROR: No hay pacientes registrados.\n");
                    continue;
                }
                mostrarTodosPacientes(*lp);
                break;
            case 0: system("cls"); return;
            break;
        }
    }
}
// Consultas de agenda
void consultasAgenda(Lista *VO, Fecha agenda[]){
int d=-1, dia, mes, dni, cant;
while(d!=0){
            printf("==================== CONSULTAS DE AGENDA ====================\n");
            printf(" [1] Buscar fechas libres por d%ca y mes\n",161);
            printf(" [2] Mostrar los turnos de un paciente (por DNI)\n");
            printf(" [3] Buscar fechas ocupadas por mes\n");
            printf(" [4] Buscar un turno por ID\n");
            printf(" [0] Regresar\n>");
    d=limite(0,4);
    switch(d){
case 1:
    printf("%cMes?\n", 168);
    mes = limite(11,12);
    printf("%cD%ca?\n", 168, 161);
    dia = limite(1, diaEnMes(mes));
    fechaLibreEnAgenda(agenda, dia, mes);
    break;
case 2:
    printf("%cN%cmero de DNI?\n>", 168, 163);
    dni=limite(minDNI, maxDNI);
    cant=mostrarTurnoPorDNI(*VO, agenda, dni);
    if(cant==0){
        printf("El paciente con DNI %d no tiene turnos registrados.\n", dni);
    }
    break;
case 3:
    printf("%cMes?\n", 168);
    mes = limite(11,12);
    fechaOcupadaAgenda(agenda, mes);
    break;
case 4:
    mostrarTurnoBuscado(VO, agenda);
    break;
        }
    }
}

void estadisticas(Lista *VO, Fecha agenda[]){
int d=-1, dia, mes, cant;
while(d!=0){
    printf("==================== ESTADISTICAS Y REPORTES ====================\n");
    printf(" [1] Mostrar todos los turnos (paginado)\n");
    printf(" [2] Mostrar turnos asignados de un mes\n");
    printf(" [3] Contar turnos atendidos de un dia\n");
    printf(" [4] Calcular el monto ingresado en un mes\n");
    printf(" [0] Regresar\n>");
    d=limite(0,4);
    switch(d){
    case 1:
        mostrarTodosTurnosPagina(*VO, agenda);
        break;
    case 2:
        if(isEmptyL(*VO)){
            printf("ERROR: No hay turnos registrados en el sistema.\n");
            continue;
        }
        printf("%cMes?\n", 168);
        mes = limite(11,12);
        resetL(VO);
        mostrarTurnosMesRec(*VO, agenda, mes);
        break;
    case 3:
        if(isEmptyL(*VO)){
            printf("ERROR: No hay turnos registrados en el sistema.\n");
            continue;
        }
        printf("%cMes?\n", 168);
        mes = limite(11,12);
        printf("%cD%ca?\n", 168, 161);
        dia = limite(1, diaEnMes(mes));
        resetL(VO);
        cant=contarTurnosAtendidos(*VO, dia, mes);
        if(cant==0){
            printf("No se registraron turnos atendidos en el dia: %d/%d.\n", dia, mes);
            }else{
            printf("Se registraron %d turnos atendidos en el dia: %d/%d.\n", cant, dia, mes);
            }
        break;
    case 4:
        if(isEmptyL(*VO)){
            printf("ERROR: No hay montos registrados en el sistema (no hay turnos registrados).\n");
            continue;
        }
        printf("%cMes?\n", 168);
        mes = limite(11,12);
        calcularMontoMes(*VO, mes);
        break;
        }
    }
}

void archivosBackup(Lista *VO, LPaciente *listaE, Fecha agenda[]){
int d=-1, op;
while(d!=0){
    printf("==================== ARCHIVOS Y BACKUP ====================\n");
    printf(" [1] Generar backup\n");
    printf(" [2] Cargar backup\n");
    printf(" [0] Regresar\n>");
    d = limite(0,2);
    switch(d){
        case 1:
            backup(*VO, *listaE, agenda);
            break;
        case 2:
            printf("Cargar el backup reemplaza todos los datos actuales.\n%cDesea continuar? [1. Si | 0. No]\n>", 168);
            op = limite(0,1);
            if(op==1){
                cargarBackup(VO, listaE, agenda);
            }
            break;
        }
    }
}

int main(){
    Fecha agenda[390];
    LPaciente listaE;
    int d=-1;
    //! INICIALIZADORES:
    inic(&listaE);
    Lista VO;
    inicLista(&VO);
    inicializarAgenda(agenda);
    //! MENU PRINCIPAL
    while(d != 0){
        printf("==================== SISTEMA DE GESTI%cN M%cDICA ====================\n",224,144);
        printf(" [1] Gesti%cn de Turnos\n",162);
        printf(" [2] Gesti%cn de Pacientes\n",162);
        printf(" [3] Consultas de Agenda\n");
        printf(" [4] Estad%csticas y Reporte\n",161);
        printf(" [5] Archivos y Backup (copia de seguridad)\n");
        printf(" [0] Salir\n");
        printf("===================================================================\n>");
        d = limite(0,5);
        switch(d){
            case 1: system("cls");
                    gestionTurnos(&VO,agenda,&listaE);
            break;
            case 2: system("cls");
                    gestionPacientes(&listaE, VO);
            break;
            case 3: system("cls");
                    consultasAgenda(&VO, agenda);
            break;
            case 4: system("cls");
                    estadisticas(&VO, agenda);
            break;
            case 5: system("cls");
                    archivosBackup(&VO, &listaE, agenda);
            break;

            case 0: printf("%cGracias por utilizar nuestro programa!\n",173);return 0;
            break;
        }

    }
    return 0;
}
