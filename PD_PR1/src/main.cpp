//-------------------1. Codigo Básico:-----------------------------

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


//-------------------2. Modificar el programa (ON, OFF):-----------------------------

#include <Arduino.h>
#define LED_BUILTIN 48  // Pin del LED
#define DELAY 1000      // Tiempo de espera en milisegundos




void setup() {
    pinMode(LED_BUILTIN, OUTPUT);  // Configurar LED como salida
    Serial.begin(115200);          // Inicializar comunicación serie
}




void loop() {
    digitalWrite(LED_BUILTIN, HIGH);  // Encender LED
    Serial.println("ON");             // Enviar mensaje por serie
    delay(DELAY);                    




    digitalWrite(LED_BUILTIN, LOW);   // Apagar LED
    Serial.println("OFF");            // Enviar mensaje por serie
    delay(DELAY);                    
}

//-------------------3. Modificar programa para que actue en los registros de entrada de salida:-----------------------------

#include <Arduino.h>
#define LED_PIN 48
#define DELAY 1000




void setup() {
    // Configurar el pin como salida directamente en el hardware
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction((gpio_num_t)LED_PIN, GPIO_MODE_OUTPUT);




    // Inicializar el puerto serie
    Serial.begin(115200);
}




void loop() {
    uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG; // Puntero al registro GPIO




    *gpio_out |= (1 << LED_PIN);  // Encender LED
    Serial.println("ON");         // Mensaje serie
    delay(DELAY);




    *gpio_out &= ~(1 << LED_PIN); // Apagar LED
    Serial.println("OFF");        // Mensaje serie
    delay(DELAY);
}

//-------------------4. Medir frecuencia máxima:-----------------------------

#define LED_PIN 48  // Cambia el pin según disponibilidad




void setup() {
    Serial.begin(115200); // Iniciar puerto serie
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction((gpio_num_t)LED_PIN, GPIO_MODE_OUTPUT);
}




void loop() {

//-------------------4.1 Con el envio por puerto série del mensaje y utilizando las funciones del Arduino:-----------------------------

digitalWrite(LED_PIN, HIGH);
Serial.println("ON");
digitalWrite(LED_PIN, LOW);
Serial.println("OFF");


//-------------------4.2 - Con el envio por puerto série y accediendo directamente a los registros:-----------------------------

uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
*gpio_out |= (1 << LED_PIN);
 Serial.println("ON");
 *gpio_out &= ~(1 << LED_PIN);
 Serial.println("OFF");

//-------------------4.3 - Sin el envio por el puerto série del mensaje i utilizando las funciones de Arduino:-----------------------------

digitalWrite(LED_PIN, HIGH);
digitalWrite(LED_PIN, LOW);

//-------------------4.4 - Sin el envio por el puerto série y accedirendo directamente a los registros:-----------------------------

uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
*gpio_out |= (1 << LED_PIN);
*gpio_out &= ~(1 << LED_PIN);
