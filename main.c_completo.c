#include <stdio.h>
#include <string.h>

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

// TEMA: FUNCIONES + PUNTEROS
// Calcula la nota final aplicando las ponderaciones de cada progreso
float calcularNotaFinal(struct Registro *r)
{
    return (r->nota_p1 * r->pond_p1 / 100) +
           (r->nota_p2 * r->pond_p2 / 100) +
           (r->nota_p3 * r->pond_p3 / 100);
}

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

// TEMA: FUNCIONES + ARREGLOS
// Calcula cuantos estudiantes aprobaron o reprobaron cada materia
void aprobadosReprobados(struct Registro *reg, int total, float umbral)
{
    printf("\n--- APROBADOS Y REPROBADOS (umbral %.1f) ---\n", umbral);
    for (int i = 0; i < total; i++)
    {
        float final = calcularNotaFinal(reg + i);
        printf("%s (%s) -> %s\n", (reg+i)->nombre_estudiante, (reg+i)->codigo_materia,
               final >= umbral ? "APROBADO" : "REPROBADO");
    }
}

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

// ===========================================================
// MAIN - Menu principal del programa
// ===========================================================
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