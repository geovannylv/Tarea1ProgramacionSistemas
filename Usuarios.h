#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
    char usuario[50];
    char clave[50];
    char nombre[100];
} Usuario;

// Este metodo carga usuarios definidos en el sistemaa desde el archivo vendedores.txt 
int cargarUsuarios(Usuario **lista);



 // Verifica si el usuario y clave existen en la lista. retorna 1 si existen, 0 si no.
int verificarAcceso(Usuario *lista, int total, const char *usuario, const char *clave);

#endif
