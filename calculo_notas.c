#include <stdio.h>
#include <string.h>
#include "notas.h"

// TEMA: FUNCIONES + PUNTEROS
// Calcula la nota final aplicando las ponderaciones de cada progreso
float calcularNotaFinal(struct Registro *r)
{
    return (r->nota_p1 * r->pond_p1 / 100) +
           (r->nota_p2 * r->pond_p2 / 100) +
           (r->nota_p3 * r->pond_p3 / 100);
}

// Calcula el promedio de nota final de cada estudiante a traves de sus materias
void promedioPorEstudiante(struct Registro *reg, int total)
{
    printf("\n--- PROMEDIO POR ESTUDIANTE ---\n");
    for (int i = 0; i < total; i++)
    {
        float suma = 0; int contador = 0;
        for (int j = 0; j < total; j++)
        {
            if (strcmp((reg+i)->codigo_estudiante, (reg+j)->codigo_estudiante) == 0)
            {
                suma += calcularNotaFinal(reg + j);
                contador++;
            }
        }
        printf("%s -> Promedio: %.2f\n", (reg+i)->nombre_estudiante, suma / contador);
    }
}
