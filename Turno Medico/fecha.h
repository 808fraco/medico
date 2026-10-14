#ifndef TDAFECHA_H_INCLUDED
#define TDAFECHA_H_INCLUDED

#include <stdio.h>

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

/** OPERACIONES DEL TDA_FECHA: SETTERS **/

// MODIFICA EL MES (1 A 12). SI EL DIA PREVIO SUPERO EL NUEVO MES, LO AJUSTA.
int setMes(Fecha *f, int mes){
if (mes>=1 && mes<=12){
    (*f).mes=mes;
    int max_dias=diaEnMes(mes);
    if ((*f).dia>max_dias){
        (*f).dia=max_dias;
        }
        return 1;
    }
    return 0;
}

// MODIFICA EL DIA SEGUN EL MES ACTUAL (1 A MAX_DIAS).
int setDia(Fecha *f, int dia){
int max_dias=diaEnMes((*f).mes);
if (dia>=1 && dia<=max_dias){
    (*f).dia=dia;
    return 1;
    }
return 0;
}

// MODIFICA LA HORA (0 A 23HS).
int setHora(Fecha *f, int hora){
if (hora>=0 && hora <=23){
    (*f).hora=hora;
    return 1;
    }
return 0;
}

// MODIFICA LOS MINUTOS (SOLO ACEPTA 0 O 30).
int setMinuto(Fecha *f, int minuto){
if (minuto==0 || minuto==30){
    (*f).minuto=minuto;
    return 1;
    }
return 0;
}

// MODIFICA EL ESTADO DE DISPONIBILIDAD (1=LIBRE, 0=OCUPADO).
int setDisponible(Fecha *f, int disp){
if (disp==LIBRE || disp==OCUPADO){
    (*f).disponible=disp;
    return 1;
    }
return 0;
}

// CONSTRUCTOR: CREA Y VALIDA UNA FECHA COMPLETA. SI FALLA, RETORNA UNA FECHA POR DEFECTO.
Fecha crearFecha(int dia, int mes, int hora, int minuto, int disponible){
Fecha f;
initFecha(&f);
if (!setMes(&f, mes) || !setDia(&f, dia) || !setHora(&f, hora) || !setMinuto(&f, minuto) || !setDisponible(&f, disponible)){
    printf("ADVERTENCIA: Parametros de fecha invalidos. Se retorna fecha por defecto.\n");
    initFecha(&f);
    }
    return f;
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

//CARGA LOS DATOS DE UNA FECHA COMPLETA.
void cargarFechaCompleta(Fecha *f){
    int d,m,h,minu, disp;

    initFecha(f);

    //1. MES
    printf("Ingrese Mes (1 al 12): ");
    while(scanf("%d", &m)!=1 || (!setMes(f, m))){
        while(getchar()!='\n');
        printf("ERROR: Mes invalido. Debe ser un número del 1 al 12.\n", m);
        printf("Reingrese el mes(1 a 12): ");
    }


    //2. DIA
    int max_dias=diaEnMes((*f).mes);
    printf("Ingrese Dia (1 a %d): ", max_dias);
    while(scanf("%d", &d)!=1|| !setDia(f, d)){
        while(getchar()!='\n');
        printf("ERROR: Dia invalido. debe ser un numero del 1 al %d.\n", max_dias);
        printf("Reingrese el dia(1 a %d): ", max_dias);
    }

    //3. HORA
    printf("Ingrese hora (0 a 23): ");
    while(scanf("%d", &h)!=1 || !setHora(f,h)){
        while(getchar()!='\n');
        printf("ERROR: Hora inválida, debe ser de 0 a 23.\n");
        printf("Reingrese la hora(0 a 23): ");
    }

    //4. MINUTOS
        printf("Ingrese Minutos (0 o 30): ");
    while(scanf("%d", &minu)!=1 || !setMinuto(f,minu)){
        while(getchar()!='\n');
        printf("ERROR: Los turnos se fraccionan cada media hora. Solo se permite 0 o 30.\n");
        printf("Reingrese Minutos (0 o 30): ");
    }

    //5. DISPONIBILIDAD
    printf("Disponibilidad (1= Libre, 0= Ocupado): ");
    while(scanf("%d", &disp)!=1 || !setDisponible(f,disp)){
        while(getchar()!='\n');
        printf("ERROR: Opcion inválida, Ingrese 1 para 'Libre' o 0 para 'Ocupado'. \n");
        printf("Reingrese Disponibilidad(1 o 0): ");
        }
}

//FUNCION PARA MOSTRAR FECHA.
void mostrarFecha(Fecha f){
    printf("%02d/%02d/%d %02d:%02d hs [%s]",
       f.dia, f.mes, f.anio, f.hora, f.minuto,
       (f.disponible==LIBRE)?"Libre":"Ocupado");
}

// COMPARACION DE FECHAS CRONOLOGICAMENTE:
// RETORNA NEGATIVO SI f1 < f2, CERO SI SON IGUALES, POSITIVO SI f1 > f2.
int compararFechas(Fecha f1, Fecha f2){
if (f1.anio!=f2.anio)      return f1.anio-f2.anio;
if (f1.mes!=f2.mes)        return f1.mes-f2.mes;
if (f1.dia!=f2.dia)        return f1.dia-f2.dia;
if (f1.hora!=f2.hora)      return f1.hora-f2.hora;
return f1.minuto-f2.minuto;
}

// RETORNA EL DIA DE LA SEMANA: (0=DOMINGO, 1=LUNES, 2=MARTES, 3=MIERCOLES, 4=JUEVES, 5=VIERNES, 6=SABADO).
// SE CALCULA SABIENDO QUE EL 01/01/2026 FUE JUEVES (DIA 4).
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

// RETORNA 1 SI ES DE LUNES A VIERNES, 0 SI ES FIN DE SEMANA.
int esDiaHabil(Fecha f){
    int ds=diaSemana(f);
    if (ds>=1&&ds<=5){
        return 1;
        }
    return 0;
}
#endif
