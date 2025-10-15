/********************
 * Pontificia Universidad Javeriana
 * Hecho por: Yosefh Steven Pena Rodriguez
 * Fecha: 14/10/2025
 * Clase: Sistemas Operativos
 * Tema: Fork Pipe Named
 * Descripcion:
 * Este programa es el cliente. Se conecta con el servidor por medio
 * de un FIFO (named pipe). El usuario escribe mensajes que se envian
 * al servidor, y este devuelve la misma cadena pero al reves.
 *
 * Hacer una descripcion de cada fichero:
 * Que hace?
 *   El cliente es el proceso que envia los mensajes. Permite que el
 *   usuario escriba texto y lo manda al servidor para que lo procese.
 *
 * Como lo hace?
 *   - Abre o crea el FIFO en la ruta /tmp/fifo_twoway.
 *   - Espera que el usuario escriba texto por consola.
 *   - Envia la cadena al servidor.
 *   - Lee la respuesta (texto invertido) que devuelve el servidor.
 *   - Si el usuario escribe "end", cierra el FIFO y termina.
 *******************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

int main() {
   int fd;               // Descriptor de archivo para el FIFO
   int end_process;      // Variable para verificar si se debe terminar
   int stringlen;        // Longitud de la cadena ingresada
   int read_bytes;       // Cantidad de bytes leidos desde el FIFO
   char readbuf[80];     // Buffer para leer y escribir cadenas
   char end_str[5];      // Palabra clave para finalizar ("end")

   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

   // Abre (o crea si no existe) el FIFO en modo lectura/escritura
   fd = open(FIFO_FILE, O_CREAT | O_RDWR, 0640);

   strcpy(end_str, "end"); // Copia la palabra de finalizacion

   while (1) {
      printf("Enter string: ");
      fgets(readbuf, sizeof(readbuf), stdin); // Lee la entrada del usuario

      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0'; // Elimina el salto de linea del final

      // Compara la cadena ingresada con "end"
      end_process = strcmp(readbuf, end_str);
      
      if (end_process != 0) {
         // Envia el texto al servidor
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

         // Espera la respuesta del servidor (texto invertido)
         read_bytes = read(fd, readbuf, sizeof(readbuf));
         readbuf[read_bytes] = '\0';
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      } else {
         // Si se escribe "end", envia mensaje final y termina el cliente
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd);
         break;
      }
   }

   return 0;
}
