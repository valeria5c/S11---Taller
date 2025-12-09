#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                do {
                    registrarLibro();
                } while (preguntarRepetir("Desea registrar otro libro"));
                break;

            case 2:
                mostrarLibros();
                break;

            case 3:
                do {
                    char titulo[50];
                    printf("Ingrese titulo a buscar: ");
                    fflush(stdin);
                    leerCadena(titulo, 50);
                    buscarPorTitulo(titulo);
                } while (preguntarRepetir("Desea buscar otro titulo"));
                break;

            case 4:
                do {
                    int id = ValidacionNumeros("Ingrese ID del libro: ");
                    buscarPorID_mostrar(id);
                } while (preguntarRepetir("Desea buscar otro ID"));
                break;

            case 5:
                do {
                    int id = ValidacionNumeros("Ingrese ID del libro a actualizar: ");
                    actualizarEstado(id);
                } while (preguntarRepetir("Desea actualizar otro libro"));
                break;

            case 6:
                do {
                    printf("\n=== LISTA DE LIBROS REGISTRADOS ===\n");
                    mostrarLibros();   // Mostramos la tabla antes de pedir el ID
                    int id = ValidacionNumeros("Ingrese ID del libro a eliminar: ");
                    eliminarLibro(id);
                } while (preguntarRepetir("Desea eliminar otro libro"));
                break;

            case 7:
                printf("Programa finalizado.\n");
                return 0;
        }

    } while (preguntarRepetir("Desea regresar al menu principal"));

    printf("Programa finalizado.\n");
    return 0;
}
