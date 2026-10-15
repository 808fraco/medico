#include <stdio.h>
#include <stdlib.h>
#include "listaEstatica.h"
#include "paciente.h"
int main(){
LPaciente LP,aux;
inic(&LP);

Paciente p1, p2;

init(&p1);
setNombre(&p1, "Carlos");
setApellido(&p1, "Perez");
setDNI(&p1, 48526543);
setOSocial(&p1, 1);

init(&p2);
setNombre(&p2, "Thiago");
setApellido(&p2, "Lucero");
setDNI(&p2, 48294423);
setOSocial(&p2, 0);

printf("%s \n", getNombre(p1));
printf("%d \n", getDNI(p1));
printf("%d \n", getOSocial(p1));
printf("LISTA: \n");
insert(&LP, p1);
insert(&LP, p2);
reset(&LP);
while(!isOos(LP)){
    Paciente actual = copy(LP);
    char *nom = getNombre(actual);
    char *ape = getApellido(actual);
    printf("DNI: %d\n Paciente: %s, %s\nObra social: %s\n", getDNI(actual), getNombre(actual), getApellido(actual), getOSocial(actual) ?"SI" :"NO");
    free(nom);
    free(ape);
    forwards(&LP);
}
    return 0;
}
