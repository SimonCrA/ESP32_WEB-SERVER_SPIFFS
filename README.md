# ESP32_WEB-SERVER_SPIFFS


###  WEB SERVER USING SPIFFS
---
Este código le permite al ESP32 crear un web server que servirá un página web, pero esta vez la página será montada primero en la memoria flash del esp32, usando SPIFFS (SPI Flash file system).

 para esto creamos una carpeta en el directorio src, llamado data

 ```
 -src
 --data
 ----index.html
 ----style.css
 ```

El ESP32 esta programado para conectarse a una red WiFi. usando las credenciales que se especifican en esta sección del código.

#### Side Note: LA primera vez el esp32 montará primero los archivos de la página web en el SPIFFS, luego ya no lo hará.

```
const char* ssid = "noShar3";
const char* password = "holacomoestas";
```
---

Al conectarse a la red wifi el esp32 nos dará a través del puerto serial una dirección ip que es a la que debemos acceder para poder visualizar la página WEB.

En la página WEB nos encontraremos con dos botones que cambian el estado de las GPIO:
```
GPIO 26
GPIO 27
```
Debemos conectar un led en cada PIN del ESP32.

---
Para finalizar debemos accionar los botones, y veremos cómo los LEDs cambiarán su estado (ON/OFF).
