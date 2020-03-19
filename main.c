#include <stdio.h>
#include <string.h>

// Pedro Antonio Estévez Pérez

// Ejercicio 16

/* Realice un programa que lea el fichero books.xml (que podrá descargar de la página web
 * de la asignatura), el cual contiene información sobre una lista de libros a comprar,
 * busque en él los nombres y precios de los libros y los escriba en un fichero de texto
 * nombre_precios.txt, nombre y precio por línea.*/

/* Al leer el fichero, leerá una línea hasta el final del fichero y luego pasará a la siguiente
 * línea. Por tanto, hay que ejecutar lo que queramos en cada iteración. Lo que haremos será
 * copiar el contencido de la linea a una variable y trabajar con ella. Para identificar dónde se
 * encuentra el contenido que nos interesa, habrá que buscar el substring correspondiente a titulo
 * o precio y hacer la diferencia de las posiciones de memoria para ver el numero de elementos que
 * hay entre medias y saltar lo que haya que saltar. Una vez tenemos en otra variable lo que queremos
 * sólo hay que imprimirla en el fichero nuevo, que se abrirá en modo de escritura sin sobreescribir
 * para ver que hay diferencia entre ejecución u ejecución.*/

int main(void)
{
    char linea[300], titulo[50], precio[10];
    char  *posicion1, *posicion2;
    int inicial, final, i;
    FILE *lectura; //Puntero a fichero del que leeremos
    FILE *escritura; //Puntero a fichero en el que escribiremos

    lectura = fopen("books.xml", "r");
    if (lectura == NULL) // Si no se abre bien, se acaba en programa
    {
        printf("Error. No se pudo abrir el archivo.\n\n");
        return 0;
    }
    else // Si se abre bien, continuamos
    {
        escritura = fopen("nombre_precios.txt", "a"); // Abrimos el fichero donde escribiremos
        if (escritura == NULL)
        {
            printf("Error. No se pudo abrir el archivo.\n\n");
            return 0;
        }
        while(fgets(linea,300,lectura) != NULL) // Mientras no lleguemos al EOF, almacenamos el contenido de la linea en la variable linea
        {
            if (strstr(linea,"<title>"))
            {
                posicion1 = strstr(linea, "<title>"); // Comprobamos que este esta etiqueta
                posicion2 = strstr(linea, "</title>"); // Comprobamos la otra etiqueta para ver la diferencia de posiciones de memoria
                final = posicion2 - posicion1 - 1 + 6; // Diferencia de posiciones de memoria para calcular la posicion, -1 para quitar la posicion del final y + 6 para los espacios iniciales
                inicial = 13; //6 de espacios + 7 de <title>

                fprintf(escritura,"El título es: ");
                for (i=inicial; i<=final; i++) // Por último, escribimos en el fichero
                {
                    titulo[i-inicial] = linea[i];
                    fputc(titulo[i-inicial],escritura);
                }
                fprintf(escritura,"\n");
            }
            else if (strstr(linea,"<price>"))
            {
                posicion1 = strstr(linea, "<price>");
                posicion2 = strstr(linea, "</price>");
                final = posicion2 - posicion1 - 1 + 6;
                inicial = 13;

                fprintf(escritura, "El precio es: ");
                for (i=inicial; i<=final; i++)
                {
                    precio[i-inicial] = linea[i];
                    fputc(precio[i-inicial],escritura);
                }
                fprintf(escritura,"\n\n");
            }
        }
    }
    fclose(lectura);
    fclose(escritura);
}
