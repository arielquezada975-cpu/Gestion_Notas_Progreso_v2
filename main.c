#include <stdio.h>
#include "notas.h"

int main()
{
    struct Registro registros[MAX_REGISTROS];
    int total = cargarDesdeArchivo(registros, "notas.csv");
    int opcion;

    do {
        printf("\n=== GESTION DE NOTAS ===\n");
        printf("1. Registrar materia\n");
        printf("2. Listar materias\n");
        printf("3. Promedio por estudiante\n");
        printf("4. Aprobados/Reprobados\n");
        printf("5. Guardar cambios\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarMateria(registros, &total); break;
            case 2: listarMaterias(registros, total); break;
            case 3: promedioPorEstudiante(registros, total); break;
            case 4: aprobadosReprobados(registros, total, 6); break;
            case 5: guardarEnArchivo(registros, total, "notas.csv"); break;
        }
    } while (opcion != 6);

    guardarEnArchivo(registros, total, "notas.csv"); // guardado automatico al salir
    printf("Programa finalizado.\n");
    return 0;
}
