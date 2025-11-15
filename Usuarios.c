#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuarios.h"

int cargarUsuarios(Usuario **lista) {
    FILE *f = fopen("vendedores.txt", "r");
    if (!f) {
        printf("error : No se pudo abrir vendedores.txt\n");
        return 0;
    }
    int capacidad = 10;
    int count = 0;
    *lista = malloc(sizeof(Usuario) * capacidad);
    while (!feof(f)) {
        Usuario temp;
        if (fscanf(f, "%[^,],%[^,],%[^\n]\n", temp.usuario, temp.clave, temp.nombre) == 3) {
            if (count == capacidad) {
                capacidad *= 2;
                *lista = realloc(*lista, sizeof(Usuario) * capacidad);
            }
            (*lista)[count++] = temp;
        }
    }
    fclose(f);
    return count;
}


int verificarAcceso(Usuario *lista, int total, const char *usuario, const char *clave) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].usuario, usuario) == 0 && strcmp(lista[i].clave, clave) == 0) {
            return 1; 
        }
    }
    return 0; 
}
