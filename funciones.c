#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

// Arreglo global donde se almacenarán los libros
Libro libros[MAX_LIBROS];
// Cantidad actual de libros registrados
int cantidadLibros = 0;

// ----------------------- MENU -----------------------
int menu()
{
    int opcion;
    int valido;
    int opcionValida;

    do
    {
        opcionValida = 1; // Asumimos que será válida, y luego verificamos

        printf("\nSISTEMA DE LIBRERIA\n");
        printf("1. Registrar Libro\n");
        printf("2. Mostrar Libros\n");
        printf("3. Buscar Libro por Titulo\n");
        printf("4. Buscar Libro por ID\n");
        printf("5. Actualizar Estado del Libro\n");
        printf("6. Eliminar Libro\n");
        printf("7. Salir\n");
        printf("\nSeleccione una opcion: ");
        valido = scanf("%d", &opcion);

        // Validar entrada numérica
        if (valido != 1)
        {
            printf("Entrada invalida. Intente nuevamente.\n");
            opcionValida = 0;
            while (getchar() != '\n')
                ; // Limpiar espacio de memoria
        }
        else if (opcion < 1 || opcion > 7)
        {
            printf("Opcion fuera de rango. Intente nuevamente.\n");
            opcionValida = 0;
        }
        else if (cantidadLibros == 0 && (opcion >= 2 && opcion <= 6))
        {
            printf("\nNo hay libros registrados.\n"
                   "Debe registrar al menos un libro antes de usar esta opcion.\n");
            opcionValida = 0;
        }

    } while (!opcionValida);

    return opcion;
}

// ----------------------- VALIDAR ENTEROS -----------------------
int ValidacionNumeros(const char mensaje[])
{
    int numero;
    int valido;

    do
    {
        printf("%s", mensaje);
        valido = scanf("%d", &numero);

        // Verifica que sea un número entero válido (mayor o igual a 0)
        if (valido != 1 || numero < 0)
        {
            printf("Entrada invalida. Intente nuevamente.\n");
            while (getchar() != '\n')
                ; // Limpia buffer
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
        opc = toupper(opc); // Convierte a mayúscula para facilitar la comparación

        if (opc == 'S')
        {
            return 1;
        }
        else if (opc == 'N')
        {
            return 0;
        }
        else
        {
            printf("Opcion invalida.\n");
        }

    } while (1);
}

// --------------------- REGISTRAR LIBRO -------------------------
void registrarLibro()
{
    // Verifica si hay espacio disponible
    if (cantidadLibros >= MAX_LIBROS)
    {
        printf("No se pueden registrar mas libros.\n");
        return;
    }

    int id;

    // Validar ID único
    do
    {
        id = ValidacionNumeros("Ingrese ID del libro: ");

        int existe = 0;

        // Verifica si el ID ya está registrado
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

    // Ingreso del título
    printf("Ingrese titulo: ");
    fflush(stdin);
    leerCadena(libros[cantidadLibros].titulo, 100);

    // Ingreso del autor
    printf("Ingrese autor: ");
    fflush(stdin);
    leerCadena(libros[cantidadLibros].autor, 50);

    // Año de publicación
    libros[cantidadLibros].anio_publicacion = ValidarAnio("Ingrese anio de publicacion: ");

    // Estado del libro (0 o 1)
    int estado;
    do
    {
        estado = ValidacionNumeros("Ingrese estado (1 = Disponible, 0 = Prestado): ");

        if (estado == 0 || estado == 1)
        {
            break;
        }
        else
        {
            printf("Estado invalido. Solo 0 o 1.\n");
        }

    } while (1);

    libros[cantidadLibros].estado = estado;

    cantidadLibros++; // Incrementa la cantidad de libros registrados
    printf("Libro registrado exitosamente.\n");
}

// ----------------------- MOSTRAR LIBROS -------------------------
void mostrarLibros()
{
    printf("\n#\tID\tTitulo\t\tAutor\t\tAnio\tEstado\n");

    // Muestra todos los libros registrados
    for (int i = 0; i < cantidadLibros; i++)
    {
        printf("\n%d\t%d\t%s\t\t%s\t\t%d\t%s\n",
               i + 1,
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio_publicacion,
               libros[i].estado == 1 ? "Disponible" : "Prestado");
    }
}

// --------------------- BUSCAR POR TÍTULO -----------------------
void buscarPorTitulo(const char *titulo)
{
    int encontrado = 0;

    // Busca coincidencia exacta ignorando mayúsculas/minúsculas
    for (int i = 0; i < cantidadLibros; i++)
    {
        if (strcasecmp(libros[i].titulo, titulo) == 0)
        {
            printf("\nLibro encontrado:\n");
            printf("ID: %d\n", libros[i].id);
            printf("Titulo: %s\n", libros[i].titulo);
            printf("Autor: %s\n", libros[i].autor);
            printf("Anio: %d\n", libros[i].anio_publicacion);
            printf("Estado: %s\n", libros[i].estado == 1 ? "Disponible" : "Prestado");
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Libro no encontrado.\n");
    }
}

// --------------------- BUSCAR POR ID ---------------------------
int buscarPorID(int id)
{
    // Recorre el arreglo buscando coincidencia de ID
    for (int i = 0; i < cantidadLibros; i++)
    {
        if (libros[i].id == id)
        {
            return i; // Devuelve la posición del libro
        }
    }
    return -1; // No encontrado
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
        printf("Estado: %s\n", libros[index].estado == 1 ? "Disponible" : "Prestado");
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

    // Muestra el estado actual
    printf("Estado actual: %s\n", libros[index].estado == 1 ? "Disponible" : "Prestado");

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

    // Se recorre desde la posición encontrada hacia adelante,
    // "corriendo" los libros a la izquierda para borrar el hueco
    for (int i = index; i < cantidadLibros - 1; i++)
    {
        libros[i] = libros[i + 1];
    }

    cantidadLibros--;

    printf("Libro eliminado exitosamente.\n");
}

// ----------------------- LEER CADENA ---------------------------
void leerCadena(char *cadena, int n)
{
    fgets(cadena, n, stdin); // Lee una línea completa incluyendo espacios
    int len = strlen(cadena) - 1;

    // Reemplaza el salto de línea por fin de cadena
    if (len >= 0 && cadena[len] == '\n')
    {
        cadena[len] = '\0';
    }
}

// Validar Año
int ValidarAnio(const char mensaje[])
{
    int anio;

    do {
        anio = ValidacionNumeros(mensaje);

        // Validación de rangos realistas
        if (anio >= 1000 && anio <= 2025) {
            return anio;
        }

        printf("Año inválido. Debe estar entre 1000 y 2025.\n");

    } while (1);
}
