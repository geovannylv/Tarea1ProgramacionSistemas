#ifndef PRODUCTOS_H
#define PRODUCTOS_H

typedef struct {
    char codigo[20];
    char nombre[100];
    int cantidad;
    float costo;
    float precioVenta;
} Producto;


 // cargar el inventario desde el archivo product.txxt , retorna tambien la cantidad de los productos cargados
int cargarProductos(Producto **lista);


 // este metodo sirve para buscar el producto mediante su codigo, retornara -1 si no existe
int buscarProducto(Producto *lista, int total, const char *codigo);


 //guardar el inventario actualizado en productos.txt
void guardarProductos(Producto *lista, int total);

#endif
