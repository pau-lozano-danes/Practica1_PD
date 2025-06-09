# Práctica 1: BLINK - Parpadeo de LED con ESP32-S3

En esta práctica vamos a generar un parpadeo de un LED utilizando el microprocesador **ESP32-S3**.

---

## 1. Código Básico

### main.cpp

```cpp
#include <Arduino.h>
#define LED_BUILTIN 48
#define DELAY 500

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(DELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(DELAY);
}
```
En este primer programa configuramos el pin del LED como salida y creamos un parpadeo con un retardo de 500 ms entre los cambios de estado.


---

## 2. Modificación: ON/OFF con Serial

### main.cpp

```cpp
#include <Arduino.h>
#define LED_BUILTIN 48  // Pin del LED
#define DELAY 1000      // Tiempo de espera en milisegundos

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);  // Configurar pin como salida
    Serial.begin(115200);          // Inicializar puerto serie
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);  // Encender LED
    Serial.println("ON");             // Enviar mensaje 'ON'
    delay(DELAY);

    digitalWrite(LED_BUILTIN, LOW);   // Apagar LED
    Serial.println("OFF");            // Enviar mensaje 'OFF'
    delay(DELAY);
}
```


---

## 3. Control Directo por Registros

###main.cpp

```cpp
#include <Arduino.h>
#define LED_PIN 48
#define DELAY 1000

void setup() {
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction((gpio_num_t)LED_PIN, GPIO_MODE_OUTPUT);
    Serial.begin(115200);
}

void loop() {
    uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG; // Puntero al registro

    *gpio_out |= (1 << LED_PIN);  // Encender LED
    Serial.println("ON");
    delay(DELAY);

    *gpio_out &= ~(1 << LED_PIN); // Apagar LED
    Serial.println("OFF");
    delay(DELAY);
}
```


---

## 4. Medición de Frecuencia Máxima

Se conectó un pin libre al osciloscopio para medir la frecuencia de parpadeo en cuatro situaciones:

### 4.1 Con serial + funciones Arduino

```cpp
digitalWrite(LED_PIN, HIGH);
Serial.println("ON");
digitalWrite(LED_PIN, LOW);
Serial.println("OFF");
```
Frecuencia medida: 30 kHz

### 4.2 Con serial + registros directos

```cpp
uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
*gpio_out |= (1 << LED_PIN);
Serial.println("ON");
*gpio_out &= ~(1 << LED_PIN);
Serial.println("OFF");
```
Frecuencia medida: 30 kHz

### 4.3 Sin serial + funciones Arduino

```cpp
digitalWrite(LED_PIN, HIGH);
digitalWrite(LED_PIN, LOW);
```
Frecuencia medida: 1.7MHz

### 4.4 Sin serial + Registros directos

```cpp
uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
*gpio_out |= (1 << LED_PIN);
*gpio_out &= ~(1 << LED_PIN);
```
Frecuencia medida: 4.7MHz
