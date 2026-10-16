#ifndef TDAFECHA_H_INCLUDED
#define TDAFECHA_H_INCLUDED

//CONVENCION INTERNA: 1 = LIBRE, 0=OCUPADO
#define LIBRE 1
#define OCUPADO 0

/** ESTRUCTURACION DE DATOS **/
typedef struct{
    int dia;
    int mes; // DEL 1 AL 12
    int anio; // FIJO en 2026
    int hora; // FORMATO 0 a 23HS
    int minuto; //  SOLO SE PERMITE 0 O 30
    int disponible; // (LIBRE=1, OCUPADO=0)
}Fecha;


// FUNCION AUXILIAR: IDENTIFICA EL MES Y RETORNA LA CANTIDAD DE DIAS QUE TIENE ESE MES EN 2026.
int diaEnMes(int mes){
    switch(mes){
        case 2: // CASO DE FEBRERO, RETORNA 28 DIAS.
            return 28;
        case 4: case 6: case 9: case 11: // CASOS DE MESES CON 30 DIAS.
            return 30;
        default:// CASO DEFAULT, RETORNA 31 DIAS.
            return 31;
    }
}


// INICIALIZACION: INICIALIZA LA FECHA CON VALORES POR DEFECTO (01/01/2026, 08:00HS, LIBRE).
void initFecha(Fecha *f){
    (*f).dia=1;
    (*f).mes=1;
    (*f).anio=2026;
    (*f).hora=8;
    (*f).minuto=0;
    (*f).disponible=LIBRE; // LIBRE==1
}

/**OPERACIONES DEL TDA_FECHA:**/

// SETTERS

// ASIGNA EL DIA RECIBIDO POR PARAMETRO AL CAMPO DEL DIA DE LA FECHA.
void setDia(Fecha *f, int d){
    (*f).dia=d;
}

// ASIGNA MES RECIBIDO POR PARAMETRO AL CAMPO DEL MES DE LA FECHA.
void setMes(Fecha *f, int m){
    (*f).mes=m;
}

// ASIGNA LA HORA RECIBIDA POR PARAMETRO AL CAMPO HORA DE LA FECHA.
void setHora(Fecha *f, int h){
    (*f).hora=h;
}

// ASIGNA LOS MINUTOS RECIBIDOS POR PARAMETRO AL CAMPO MINUTO DE LA FECHA.
void setMinuto(Fecha *f, int min){
    (*f).minuto=min;
}

// ASIGNA LA DISPONIBILIDAD RECIBIDA (1=LIBRE, 0=OCUPADO) AL CAMPO DISPONIBLE DE LA FECHA.
void setDisponible(Fecha *f, int disp){
    (*f).disponible=disp;
}

// ASIGNA TODOS LOS CAMPOS DE LA FECHA (DIA, MES, HORA, MINUTO Y DISPONIBLE) CON LOS VALORES RECIBIDOS POR PARAMETRO.
void setFecha(Fecha *f, int d, int m, int h, int min, int disp){
    (*f).dia=d;
    (*f).mes=m;
    (*f).hora=h;
    (*f).minuto=min;
    (*f).disponible=disp;
}

//GETTERS

// RETORNA EL DIA DE LA FECHA.
int getDia(Fecha f){
    return f.dia;
}
// RETORNA EL MES DE LA FECHA.
int getMes(Fecha f){
    return f.mes;
}
// RETORNA EL AÑO DE LA FECHA.
int getAnio(Fecha f){
    return f.anio;
}
// RETORNA LA HORA DE LA FECHA.
int getHora(Fecha f){
    return f.hora;
}
// RETORNA LOS MINUTOS DE LA FECHA.
int getMinuto(Fecha f){
    return f.minuto;
}
//RETORNA LA DISPONIBILIDAD DE LA FECHA (1=LIBRE, 0=OCUPADO).
int getDisponible(Fecha f){
    return f.disponible;
}
//RETORNA UNA COPIA DE LA ESTRUCTURA Fecha COMPLETA.
Fecha getFecha(Fecha f){
    return f;
}

//CONSTRUCTOR DE FECHA.
Fecha creaFecha(int d, int m, int h, int min, int disp){
    Fecha f;
    f.dia=d;
    f.mes=m;
    f.anio=2026;
    f.hora=h;
    f.minuto=min;
    f.disponible=disp;
    return f;
}

//! Todo esto de abajo no es necesario pq el control de fechas se hace en el main y por id_fecha
// COMPARACION DE FECHAS CRONOLOGICAMENTE:
// RETORNA NEGATIVO SI f1 < f2, CERO SI SON IGUALES, POSITIVO SI f1 > f2.
int compararFechas(Fecha f1, Fecha f2){
    if (f1.anio!=f2.anio)       return f1.anio-f2.anio;
    if (f1.mes!=f2.mes)         return f1.mes-f2.mes;
    if (f1.dia!=f2.dia)         return f1.dia-f2.dia;
    if (f1.hora!=f2.hora)       return f1.hora-f2.hora;
    return f1.minuto-f2.minuto;
}

// RETORNA EL DIA DE LA SEMANA: (0=DOMINGO, 1=LUNES, 2=MARTES, 3=MIERCOLES, 4=JUEVES, 5=VIERNES, 6=SABADO).
// SE CALCULA SABIENDO QUE EL 01/01/2026 FUE JUEVES (DIA 4).
int diaSemana(Fecha f){
    int diaDelAnio=f.dia;
    int m;
//SUMA TODOS LOS DIAS DE LOS MESES ANTERIORES EN 2026
    for (m=1;m<f.mes;m++){
        diaDelAnio+=diaEnMes(m);
        }
//FORMULA: (DIAS+3)%7
    return (diaDelAnio+3)%7;
}

// RETORNA 1 SI ES DE LUNES A VIERNES, 0 SI ES FIN DE SEMANA.
int esDiaHabil(Fecha f){
    int ds=diaSemana(f);
    if (ds>=1&&ds<=5){
        return 1;
        }
    return 0;
}
// RETORNA 1 SI LA FECHA ES FERIADO, 0 SI NO LO ES.
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
#endif
