#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Productos.h"

int cargarProductos(Producto **lista) {
    FILE *f = fopen("productos.txt", "r");
    if (!f) {
        printf("Error: no se pudo abrir productos.txt\n");
        return 0;
    }
    int capacidad = 20;
    int count = 0;
    *lista = malloc(capacidad * sizeof(Producto));
    while (!feof(f)) {
        Producto p;
        if (fscanf(f, "%[^,],%[^,],%d,%f,%f\n",
                   p.codigo, p.nombre, &p.cantidad, &p.costo, &p.precioVenta) == 5) {

            if (count == capacidad) {
                capacidad *= 2;
                *lista = realloc(*lista, capacidad * sizeof(Producto));
            }
            (*lista)[count++] = p;
        }
    }
    fclose(f);
    return count;
}




int buscarProducto(Producto *lista, int total, const char *codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (strcmp(lista[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}



void guardarProductos(Producto *lista, int total) {
    FILE *f = fopen("productos.txt", "w");
    if (!f) {
        printf("No se pudo guardar productos.txt\n");
        return;
    }
    int i;
    for (i = 0; i < total; i++) {
        fprintf(f, "%s,%s,%d,%.2f,%.2f\n",
                lista[i].codigo,
                lista[i].nombre,
                lista[i].cantidad,
                lista[i].costo,
                lista[i].precioVenta);
    }
    fclose(f);
}
