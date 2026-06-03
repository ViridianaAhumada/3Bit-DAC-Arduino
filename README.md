# 3-Bit DAC con Arduino y R-2R

Este es un convertidor digital-analógico (DAC) de 3 bits armado en hardware para generar una onda senoidal. 

## Cómo funciona
* **Generación de onda:** El Arduino saca una secuencia senoidal de 3 bits a una velocidad constante por los pines analógicos configurados como salida digital.
* **Control de tiempos:** El código usa `micros()` en lugar de `delay()` para evitar bloqueos en el procesador y manejar la lectura del potenciómetro, la onda y el reloj al mismo tiempo.
* **Muestreo (ZOH):** Un potenciómetro controla la velocidad del pulso de reloj. Con esto, un Flip-Flop 74LS374 "atrapa" los datos del Arduino simulando un Zero-Order Hold.
* **Salida analógica:** Una red de resistencias R-2R convierte la señal digital a voltaje, y un op-amp TL081 acondiciona la señal de salida.

## Evidencia
<img width="1600" height="1562" alt="7073c081-fef3-45c4-812a-b109adaa9bce" src="https://github.com/user-attachments/assets/d93d7f3f-de74-41ff-96ca-6d46c76ffcf8" />
