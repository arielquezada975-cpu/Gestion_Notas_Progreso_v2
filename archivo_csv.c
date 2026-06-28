#include <stdio.h>
#include <string.h>
#include "notas.h"

// ===========================================================
// TEMA: MANEJO DE ARCHIVOS (Semana 13)
// Puntero a archivo de tipo FILE para comunicar el programa
// con el archivo en el sistema (notas.csv)
// ===========================================================

// Carga los registros desde el archivo plano notas.csv al iniciar el programa
int cargarDesdeArchivo(struct Registro *reg, const char *nombreArchivo)
{
    FILE *f = fopen(nombreArchivo, "r");  // Apertura de archivo en modo lectura
    if (f == NULL)
    {
        printf("No se encontro %s, se iniciara vacio.\n", nombreArchivo);
        return 0;
    }

    char linea[256];
    int total = 0;

    fgets(linea, sizeof(linea), f); // saltar la cabecera del CSV

    while (fgets(linea, sizeof(linea), f) != NULL)
    {
        sscanf(linea, "%15[^;];%49[^;];%49[^;];%15[^;];%49[^;];%f;%f;%f",
            (reg+total)->codigo_materia, (reg+total)->nombre_materia,
            (reg+total)->carrera, (reg+total)->codigo_estudiante,
            (reg+total)->nombre_estudiante, &(reg+total)->nota_p1,
            &(reg+total)->nota_p2, &(reg+total)->nota_p3);
        (reg+total)->pond_p1 = 30; (reg+total)->pond_p2 = 30; (reg+total)->pond_p3 = 40;
        total++;
    }

    fclose(f);  // Cierre formal del archivo, evita perdida de datos
    printf("Se cargaron %d registros desde %s\n", total, nombreArchivo);
    return total;
}
