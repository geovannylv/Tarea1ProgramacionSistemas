#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Usuarios.h"
#include "Productos.h"

// Obtener siguiente número de factura
int obtenerSiguienteFactura() {
    FILE *f = fopen("ventas.txt", "r");
    if (!f) return 1;

    int lastFactura = 0;
    int factura;
    char linea[300];

    while (fgets(linea, sizeof(linea), f)) {
        sscanf(linea, "%d,", &factura);
        lastFactura = factura;
    }

    fclose(f);
    return lastFactura + 1;
}

// Obtener fecha actual
void obtenerFecha(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d",
            tm_info->tm_year + 1900,
            tm_info->tm_mon + 1,
            tm_info->tm_mday);
}

int main() {

// el inicio de sesión del usuario
    Usuario *usuarios;
    int totalUsuarios = cargarUsuarios(&usuarios);

    int intentos = 0;
    char usr[50], pass[50];

    while (intentos < 3) {
        printf("Usuario: ");
        scanf("%s", usr);
        printf("Clave: ");
        scanf("%s", pass);

        if (verificarAcceso(usuarios, totalUsuarios, usr, pass)) {
            printf("\nAcceso permitido.\n\n");
            break;
        }
        intentos++;
        printf("Datos incorrectos. Intento %d/3\n", intentos);
    }

    if (intentos == 3) {
        printf("LLego a su limite de intentos, el sistema se cerrará.\n");
        free(usuarios);
        return 0;
    }

  // cargar productos en el inventario
    Producto *productos;
    int totalProductos = cargarProductos(&productos);

// registor de ventas y generacion de factura
    int factura = obtenerSiguienteFactura();
    char fecha[20];
    obtenerFecha(fecha);
    printf("Factura nro: %d\n", factura);
    printf("Fecha: %s\n\n", fecha);
    int seguir = 1;
    typedef struct {
        int indiceProd;
        int cantidad;
    } Detalle;

    Detalle detalles[100];
    int totalDetalles = 0;

    while (seguir == 1) {
        char codigo[20];
        int cant;
        printf("Ingrese el codigo del producto: ");
        scanf("%s", codigo);
        int idx = buscarProducto(productos, totalProductos, codigo);
        if (idx == -1) {
            printf("Producto no existe.\n");
            continue;
        }
        printf("Cantidad a vender: ");
        scanf("%d", &cant);
        if (cant > productos[idx].cantidad) {
            printf("No hay suficiente stock. Disponible: %d\n",
                   productos[idx].cantidad);
            continue;
        }
        detalles[totalDetalles].indiceProd = idx;
        detalles[totalDetalles].cantidad = cant;
        totalDetalles++;

        printf("Deseas agregar otro producto? (1=si / 0=no): ");
        scanf("%d", &seguir);
    }

//mostrar el detalle de la factura
    printf("\n--Detalle de la factura--n");
    float totalGeneral = 0;
    int i;

    for (i = 0; i < totalDetalles; i++) {
        int p = detalles[i].indiceProd;
        int c = detalles[i].cantidad;
        float subtotal = c * productos[p].precioVenta;

        printf("%s - %s | Cant: %d | Unit: %.2f | Subtotal: %.2f\n",
               productos[p].codigo,
               productos[p].nombre,
               c,
               productos[p].precioVenta,
               subtotal);

        totalGeneral += subtotal;
    }

    printf("\nTOTAL: %.2f\n", totalGeneral);
    int confirmar;
    printf("\nDesea confirmar la venta?? (1=si / 0=no): ");
    scanf("%d", &confirmar);

    if (!confirmar) {
        printf("Venta cancelada\n");
        free(productos);
        free(usuarios);
        return 0;
    }

//actualizacion de inventario
    for (i = 0; i < totalDetalles; i++) {
        int p = detalles[i].indiceProd;
        productos[p].cantidad -= detalles[i].cantidad;
    }
    guardarProductos(productos, totalProductos);

 //guardar ventas en ventas.txt
    FILE *f = fopen("ventas.txt", "a");
    for (i = 0; i < totalDetalles; i++) {
        int p = detalles[i].indiceProd;
        int c = detalles[i].cantidad;

        fprintf(f, "%d,%s,%s,%d,%.2f,%.2f,%s\n",
                factura,
                productos[p].codigo,
                productos[p].nombre,
                c,
                productos[p].costo,
                productos[p].precioVenta,
                fecha);
    }
    fclose(f);

    printf("\nVenta registrada con exito.\n");

    free(productos);
    free(usuarios);
    return 0;
}
