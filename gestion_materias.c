#include <stdio.h>
#include <string.h>
#include "notas.h"

// TEMA: ARREGLOS + PUNTEROS
// Registra una nueva materia validando codigo duplicado y rango de notas
int registrarMateria(struct Registro *reg, int *total)
{
    struct Registro nuevo;
    printf("Codigo materia: ");
    scanf(" %15s", nuevo.codigo_materia);

    // Validar que no exista ya el mismo par materia-estudiante
    for (int i = 0; i < *total; i++)
    {
        if (strcmp((reg + i)->codigo_materia, nuevo.codigo_materia) == 0)
        {
            printf("Error: la materia ya existe\n");
            return 0;
        }
    }

    printf("Nombre materia: ");
    scanf(" %49[^\n]", nuevo.nombre_materia);
    printf("Carrera: ");
    scanf(" %49[^\n]", nuevo.carrera);
    printf("Codigo estudiante: ");
    scanf(" %15s", nuevo.codigo_estudiante);
    printf("Nombre estudiante: ");
    scanf(" %49[^\n]", nuevo.nombre_estudiante);

    do {
        printf("Nota Progreso 1: ");
        scanf("%f", &nuevo.nota_p1);
    } while (nuevo.nota_p1 < 1 || nuevo.nota_p1 > 10);

    do {
        printf("Nota Progreso 2: ");
        scanf("%f", &nuevo.nota_p2);
    } while (nuevo.nota_p2 < 1 || nuevo.nota_p2 > 10);

    do {
        printf("Nota Progreso 3: ");
        scanf("%f", &nuevo.nota_p3);
    } while (nuevo.nota_p3 < 1 || nuevo.nota_p3 > 10);

    nuevo.pond_p1 = 30; nuevo.pond_p2 = 30; nuevo.pond_p3 = 40;

    *(reg + *total) = nuevo;  // se guarda en el arreglo usando punteros
    (*total)++;
    printf("Materia registrada correctamente.\n");
    return 1;
}