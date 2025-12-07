#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_LIBROS 10

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio_publicacion;
    int estado;  // 1 = disponible, 0 = prestado
} Libro;

int menu();

int ValidacionNumeros(const char mensaje[]);
int preguntarRepetir(const char *mensaje);

void registrarLibro();
void mostrarLibros();
void buscarPorTitulo(const char *titulo);
int buscarPorID(int id);
void buscarPorID_mostrar(int id);
void actualizarEstado(int id);
void eliminarLibro(int id);
void leerCadena(char *cadena, int n);


#endif
