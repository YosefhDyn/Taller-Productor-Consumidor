# Taller-Productor-Consumidor
# Proyecto: Comunicacion entre procesos con FIFO (Named Pipe)

## Pontificia Universidad Javeriana
**Autor:** Yosefh Steven Pena Rodriguez  
**Fecha:** 14/10/2025  
**Clase:** Sistemas Operativos  
**Tema:** Fork Pipe Named  

---

## Descripcion general

Este proyecto muestra un ejemplo basico de comunicacion entre procesos en Linux usando **FIFOs** (tambien llamados *named pipes*).  
Incluye dos programas en C:

- **server.c:** actua como servidor. Espera los mensajes del cliente, los invierte y devuelve el resultado.  
- **client.c:** actua como cliente. Envia mensajes al servidor y muestra las respuestas que este retorna.

Ambos procesos se comunican a traves del archivo FIFO `/tmp/fifo_twoway`.

---

## Objetivo

Entender como dos procesos independientes pueden comunicarse entre si usando un FIFO, sin compartir memoria ni usar sockets.  
Este ejercicio ayuda a comprender los conceptos basicos de **IPC (Inter Process Communication)** en sistemas operativos.

---

## Estructura del proyecto

