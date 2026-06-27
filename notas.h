#ifndef NOTAS_H
#define NOTAS_H

#define MAX_REGISTROS 100

// TEMA: ESTRUCTURAS - Agrupa todos los datos de un registro de notas
struct Registro {
    char codigo_materia[16];
    char nombre_materia[50];
    char carrera[50];
    char codigo_estudiante[16];
    char nombre_estudiante[50];
    float nota_p1, nota_p2, nota_p3;
    float pond_p1, pond_p2, pond_p3; // ponderaciones (deben sumar 100)
};

// Funciones de gestion (gestion_materias.c)
int registrarMateria(struct Registro *reg, int *total);
void listarMaterias(struct Registro *reg, int total);

// Funciones de calculo (calculo_notas.c)
float calcularNotaFinal(struct Registro *r);
void promedioPorEstudiante(struct Registro *reg, int total);
void aprobadosReprobados(struct Registro *reg, int total, float umbral);

// Funciones de manejo de archivos (archivo_csv.c)
int cargarDesdeArchivo(struct Registro *reg, const char *nombreArchivo);
void guardarEnArchivo(struct Registro *reg, int total, const char *nombreArchivo);

#endif