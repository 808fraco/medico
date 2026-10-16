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

#endif
