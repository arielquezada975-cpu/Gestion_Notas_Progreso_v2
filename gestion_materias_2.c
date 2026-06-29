#include <stdio.h>
#include <string.h>
#include "notas.h"

// TEMA: ARREGLOS + PUNTEROS
// Muestra todos los registros con su nota final calculada
void listarMaterias(struct Registro *reg, int total)
{
    printf("\n%-10s %-15s %-12s %-10s %-15s %-6s %-6s %-6s %-8s\n",
        "Materia","Nombre","Carrera","Estud.","Nombre Est.","P1","P2","P3","Final");
    for (int i = 0; i < total; i++)
    {
        float final = calcularNotaFinal(reg + i);
        printf("%-10s %-15s %-12s %-10s %-15s %-6.2f %-6.2f %-6.2f %-8.2f\n",
            (reg+i)->codigo_materia, (reg+i)->nombre_materia, (reg+i)->carrera,
            (reg+i)->codigo_estudiante, (reg+i)->nombre_estudiante,
            (reg+i)->nota_p1, (reg+i)->nota_p2, (reg+i)->nota_p3, final);
    }
}