# Practica 1. ADC, UART, PWM, I2C, TIMER

Esta práctica tiene como objetivo familiarizarse con los periféricos típicos de cualquier microcontrolador, conversor analógico a digital (ADC), protocolos de comunicaciones (UART, I2C), Timers… El microcontrolador utilizado es el ESP32-WROOM-32, un dispositivo de ultra bajo consumo, frecuencia ajustable hasta 80Mhz y que integra módulos Wifi y Bluetooth.
Se utiliza el entorno de desarrollo de Arduino con librerías propias, de fabricantes de sensores, usuarios y la capa HAL proporcionada por Espressif.

## Ejercicio 1 

En el ejercicio 1 Se realiza la lectura de la conversión analógica a digital de una señal generada por un potenciómetro de 10K, con tensión máxima de 3V3. El conversor tiene 12 bits de resolución, por tanto, el valor máximo de lectura será  de 4095bits. 

## Ejercicio 2

En este ejercicio se obtiene la lectura cada 10s del ADC, la interrupción es generada por un timer hardware. Se ha hecho uso de la capa HAL proporcionada por Espressif para la configuración del timer y de la rutina de interrupción.

Generar interrupciones periódicas en vez de utilizar la función delay, evita que el microcontrolador pare la ejecución del programa y por lo tanto pueda atender a otras interrupciones o continuar con la ejecución del bucle principal.

## Ejercicio 3
A partir de la lectura anterior del ADC se genera una señal PWM proporcional, para ello, se hace uso del periférico LEDC, su propósito es poder controlar la intensidad de los LED’s pero puede usarse para para otros propósitos como generar señales PWM.

## Ejercicio 4
Desarrollados los bloques ADC, PWM y TIMER, se utiliza el protocolo UART (universal asynchronous receiver transmitter) para que el usuario mandando una consigna desde un ordenador conectado al microcontrollador por el puerto serie, reciba los datos deseados de la siguiente forma.

a.	ADC: Envíe la lectura del ADC actual
b.	ADC(x): envíe la lectura del ADC cada x segundos. Si x=0, deja de mandar datos
c.	PWM(x): comanda el duty cycle del módulo PWM con números del 0 al 9.

Para captar el mensaje correctamente se extrae, en caso de que lo haya, el número del string recibido mediante la función string2num, posteriormente dependiendo del string obtenido se envía la información según el protocolo mostrado.

## Ejercicio 5
En este último apartado se establece la comunicación entre el microcontrolador y el módulo GY-91 ( modulo que cuenta con un acelerómetro, un magnetómetro un giroscopio y un barómetro ) mediante el protocolo I2C. El objetivo, es tomar muestras de uno de los sensores cada 100ms y enviarlas por puerto serie al ordenador.
I2C es un protocolo de comunicaciones maestro – esclavo, bidireccional, con un bus de dos señales, data (SDA) y reloj (SCL) la cual mediante la señal de clock proporciona el sincronismo de la comunicación.

Para la comunicación por I2C y la obtención de datos del sensor se ha utilizado la libreria proporcionada por asukiaaa.

## Enlace.
Los siguientes ejercicios se pueden consultar en [git](https://github.com/joaquinuza/Practica1)