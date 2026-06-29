#include <stdio.h>
#include <string.h>
#include "notas.h"


// Guarda todos los registros en el archivo plano (sobreescribe)
// fopen() en modo "w" crea o sobreescribe el archivo
void guardarEnArchivo(struct Registro *reg, int total, const char *nombreArchivo)
{
    FILE *f = fopen(nombreArchivo, "w");  // Apertura de archivo en modo escritura
    if (f == NULL)
    {
        printf("Error: no se pudo abrir %s para escritura.\n", nombreArchivo);
        return;
    }

    // fputs() escribe una cadena de texto directamente en el archivo
    fputs("codigo_materia;nombre_materia;carrera;codigo_estudiante;nombre_estudiante;nota_p1;nota_p2;nota_p3\n", f);

    // fprintf() escribe datos formateados en el archivo, igual que printf()
    for (int i = 0; i < total; i++)
    {
        fprintf(f, "%s;%s;%s;%s;%s;%.2f;%.2f;%.2f\n",
            (reg+i)->codigo_materia, (reg+i)->nombre_materia, (reg+i)->carrera,
            (reg+i)->codigo_estudiante, (reg+i)->nombre_estudiante,
            (reg+i)->nota_p1, (reg+i)->nota_p2, (reg+i)->nota_p3);
    }

    fclose(f);  // Cierre formal del archivo a nivel de Sistema Operativo
    printf("Datos guardados correctamente en %s\n", nombreArchivo);
}