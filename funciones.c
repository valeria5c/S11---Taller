#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

Libro libros[MAX_LIBROS];
int cantidadLibros = 0;

// ----------------------- MENU -----------------------
int menu()
{
    int opcion, valido;

    do
    {
        printf("\nSISTEMA DE LIBRERIA\n");
        printf("1. Registrar Libro\n");
        printf("2. Mostrar Libros\n");
        printf("3. Buscar Libro por Titulo\n");
        printf("4. Buscar Libro por ID\n");
        printf("5. Actualizar Estado del Libro\n");
        printf("6. Eliminar Libro\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");

        valido = scanf("%d", &opcion);

        if (valido != 1 || opcion < 1 || opcion > 7)
        {
            printf("Opcion invalida. Intente nuevamente.\n");
            while (getchar() != '\n')
                ;
        }

    } while (valido != 1 || opcion < 1 || opcion > 7);

    return opcion;
}

// ----------------------- VALIDAR ENTEROS -----------------------
int ValidacionNumeros(const char mensaje[])
{
    int numero, valido;

    do
    {
        printf("%s", mensaje);
        valido = scanf("%d", &numero);

        if (valido != 1 || numero < 0)
        {
            printf("Entrada invalida. Intente nuevamente.\n");
            while (getchar() != '\n')
                ;
        }

    } while (valido != 1 || numero < 0);

    return numero;
}

// -------------------- PREGUNTAR REPETIR -------------------------
int preguntarRepetir(const char *mensaje)
{
    char opc;

    do
    {
        printf("%s (s/n): ", mensaje);
        scanf(" %c", &opc);
        opc = toupper(opc);

        if (opc == 'S')
            return 1;
        if (opc == 'N')
            return 0;

        printf("Opcion invalida.\n");

    } while (1);
}

// --------------------- REGISTRAR LIBRO -------------------------
void registrarLibro()
{
    if (cantidadLibros >= MAX_LIBROS)
    {
        printf("No se pueden registrar mas libros.\n");
        return;
    }

    int id;

    do
    {
        id = ValidacionNumeros("Ingrese ID del libro: ");

        int existe = 0;
        for (int i = 0; i < cantidadLibros; i++)
        {
            if (libros[i].id == id)
            {
                existe = 1;
                break;
            }
        }

        if (existe)
        {
            printf("El ID ya existe. Ingrese otro.\n");
        }
        else
        {
            break;
        }

    } while (1);

    libros[cantidadLibros].id = id;

    printf("Ingrese titulo: ");
    fflush(stdin);
    leerCadena(libros[cantidadLibros].titulo, 100);

    printf("Ingrese autor: ");
    fflush(stdin);
    leerCadena(libros[cantidadLibros].autor, 50);

    libros[cantidadLibros].anio_publicacion =
        ValidacionNumeros("Ingrese anio de publicacion: ");

    int estado;
    do
    {
        estado = ValidacionNumeros("Ingrese estado (1 = Disponible, 0 = Prestado): ");

        if (estado == 0 || estado == 1)
            break;

        printf("Estado invalido. Solo 0 o 1.\n");

    } while (1);

    libros[cantidadLibros].estado = estado;

    cantidadLibros++;
    printf("Libro registrado exitosamente.\n");
}

// ----------------------- MOSTRAR LIBROS -------------------------
void mostrarLibros()
{
    printf("\n#\tID\tTitulo\t\tAutor\t\tAnio\tEstado\n");

    for (int i = 0; i < cantidadLibros; i++)
    {
        printf("\n%d\t%d\t%s\t\t\t%s\t\t%d\t%s\n",
               i + 1,
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio_publicacion,
               libros[i].estado==1 ? "Disponible" : "Prestado");
    }
}

// --------------------- BUSCAR POR TÍTULO -----------------------
void buscarPorTitulo(const char *titulo)
{
    int encontrado = 0;

    for (int i = 0; i < cantidadLibros; i++)
    {
        if (strcasecmp(libros[i].titulo, titulo) == 0)
        {
            printf("\nLibro encontrado:\n");
            printf("ID: %d\n", libros[i].id);
            printf("Titulo: %s\n", libros[i].titulo);
            printf("Autor: %s\n", libros[i].autor);
            printf("Anio: %d\n", libros[i].anio_publicacion);
            printf("Estado: %s\n", libros[i].estado==1 ? "Disponible" : "Prestado");
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("Libro no encontrado.\n");
}

// --------------------- BUSCAR POR ID ---------------------------
int buscarPorID(int id)
{
    for (int i = 0; i < cantidadLibros; i++)
        if (libros[i].id == id)
            return i;

    return -1;
}

void buscarPorID_mostrar(int id)
{
    int index = buscarPorID(id);

    if (index != -1)
    {
        printf("\nLibro encontrado:\n");
        printf("ID: %d\n", libros[index].id);
        printf("Titulo: %s\n", libros[index].titulo);
        printf("Autor: %s\n", libros[index].autor);
        printf("Anio: %d\n", libros[index].anio_publicacion);
        printf("Estado: %s\n", libros[index].estado==1 ? "Disponible" : "Prestado");
    }
    else
    {
        printf("Libro no encontrado.\n");
    }
}

// ------------------ ACTUALIZAR ESTADO --------------------------
void actualizarEstado(int id)
{
    int index = buscarPorID(id);

    if (index == -1)
    {
        printf("Libro no encontrado.\n");
        return;
    }

    printf("Estado actual: %s\n", libros[index].estado==1 ? "Disponible" : "Prestado");

    int nuevo;
    do
    {
        nuevo = ValidacionNumeros("Ingrese nuevo estado (1 = Disponible, 0 = Prestado): ");

        if (nuevo == 0 || nuevo == 1)
            break;

        printf("Estado invalido.\n");

    } while (1);

    libros[index].estado = nuevo;

    printf("Estado actualizado exitosamente.\n");
}

// --------------------- ELIMINAR LIBRO --------------------------
void eliminarLibro(int id)
{
    int index = buscarPorID(id);

    if (index == -1)
    {
        printf("Libro no encontrado.\n");
        return;
    }

    for (int i = index; i < cantidadLibros - 1; i++)
    {
        libros[i] = libros[i + 1];
    }

    cantidadLibros--;

    printf("Libro eliminado exitosamente.\n");
}

void leerCadena(char *cadena, int n)
{
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n')
    {
        cadena[len] = '\0';
    }
}