/********************
 * Pontificia Universidad Javeriana
 * Hecho por: Yosefh Steven Pena Rodriguez
 * Fecha: 14/10/2025
 * Clase: Sistemas Operativos
 * Tema: Fork Pipe Named
 * Descripcion:
 * Este programa es el servidor. Se comunica con el cliente usando
 * un FIFO (named pipe). Recibe cadenas, las invierte y las envia
 * de vuelta hasta que recibe la palabra "end".
 *
 * Hacer una descripcion de cada fichero:
 * Que hace?
 *   El servidor espera los mensajes que le envia el cliente,
 *   los procesa invirtiendo el texto y devuelve la respuesta.
 *
 * Como lo hace?
 *   - Crea el FIFO si no existe con mkfifo().
 *   - Lo abre en modo lectura y escritura.
 *   - Lee los mensajes que llegan desde el cliente.
 *   - Invierte las cadenas recibidas con una funcion auxiliar.
 *   - Envia la respuesta de nuevo al cliente.
 *   - Si recibe "end", cierra el FIFO y termina.
 *******************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

// Funcion que invierte una cadena
void reverse_string(char *);

int main() {
   int fd;               // Descriptor del FIFO
   char readbuf[80];     // Buffer para lectura y escritura
   char end[10];         // Palabra clave de finalizacion
   int to_end;           // Variable de control para terminar el bucle
   int read_bytes;       // Numero de bytes leidos del FIFO
   
   // Crea el FIFO si no existe
   mkfifo(FIFO_FILE, S_IFIFO | 0640);
   strcpy(end, "end"); // Define la palabra de terminacion

   // Abre el FIFO en modo lectura/escritura
   fd = open(FIFO_FILE, O_RDWR);

   while (1) {
      // Espera un mensaje del cliente
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));

      // Compara si el mensaje es "end"
      to_end = strcmp(readbuf, end);
      
      if (to_end == 0) {
         // Si es "end", cierra el FIFO y termina
         close(fd);
         break;
      }

      // Invierte la cadena recibida
      reverse_string(readbuf);

      // Muestra y envia la cadena invertida al cliente
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));
      write(fd, readbuf, strlen(readbuf));

      // Espera 2 segundos para permitir la lectura del cliente
      sleep(2);
   }

   return 0;
}

// Funcion que invierte una cadena de texto
void reverse_string(char *str) {
   int last, limit, first;
   char temp;
   last = strlen(str) - 1;
   limit = last / 2;
   first = 0;
   
   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
}

