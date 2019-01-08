/*
 *  Para mas informacion sobre como trabajan los puertos:
 *  https://www.arduino.cc/en/Reference/PortManipulation
 *  
 *  Pins digitales 1 a 13, constantemente HIGH.
 *  Pins analogicos A0, A1, A2 parpadean rapido.
 *  Pins analogicos A3, A4 parpadean lento.
 *  Pin analogico A5 parpadea super lento.
 *  
 */
 
int currentTime; // Guarda el tiempo actual en milisegundos.

// Guarda el tiempo en milisegundos en que se ejecuto cada grupo por ultima vez.
int lastTimeGroup1 = 0;
int lastTimeGroup2 = 0;
int lastTimeGroup3 = 0;

// Guardamos el estado de cada grupo, inicialmente todos estan apagados.
bool group1isOn = false;
bool group2isOn = false;
bool group3isOn = false;

void blinkGroup1(int delayTime) {
  if (currentTime - lastTimeGroup1 >= delayTime) { 
    if (group1isOn) {
      analogWrite(A0, 0);
      analogWrite(A1, 0);
      analogWrite(A2, 0);
      group1isOn = false;
    } else {
      analogWrite(A0, 255);
      analogWrite(A1, 255);
      analogWrite(A2, 255);
      group1isOn = true;
    }
    lastTimeGroup1 = millis();
  }
}

void blinkGroup2(int delayTime) {
  if (currentTime - lastTimeGroup2 >= delayTime) { 
    if (group2isOn) {
      analogWrite(A3, 0);
      analogWrite(A4, 0);
      group2isOn = false;
    } else {
      analogWrite(A3, 255);
      analogWrite(A4, 255);
      group2isOn = true;
    }
    lastTimeGroup2 = millis();
  }
}

void blinkGroup3(int delayTime) {
  if (currentTime - lastTimeGroup3 >= delayTime) { 
    if (group3isOn) {
      analogWrite(A5, 0);
      group3isOn = false;
    } else {
      analogWrite(A5, 255);
      group3isOn = true;
    }
    lastTimeGroup3 = millis();
  }
}

void setup() {
  /*
   * En este proyecto estamos utilizando TODOS los pins del arduino, 
   * como antes de utilizar un pin, debemos declarar si va a ser entrada (INPUT) o salida (OUTPUT), utilizando el metodo pinMode(numeroDePin, INPUT/OUTPUT);
   * necesitariamos repetir entonces 18 llamadas a pinMode, una vez con cada pin.
   * 
   * Por suerte, tenemos otras opciones, en este caso, vamos a utilizar los Port Registers.
   * 
   * Los Port Registers nos permiten una forma rapida de manipular los pines del Arduino.
   * En este caso, el Arduino UNO tiene un microcontrolador ATMEGA328P, podemos revisar la hoja de datos para mas informacion, pero tiene 3 puertos (B, C y D).
   * Estos puertos corresponden a shift-registers de 8 bits.
   * 
   * De esta forma podemos acceder rapidamente a un grupo de pins, refiriendonos al puerto al que pertenecen.
   * El puerto B incluye los pines digitales del 0 al 7,
   * el C los pines analogicos del 0 al 5, y el D incluye los pines digitales del 8 al 13.
   * 
   * Cada uno de estos puertos guardan su estado en variables, que podemos acceder desde nuestro codigo, de esta forma, llamando a DDRB (Data Direction Register)
   * podemos especificar si es un pin de entrada (0) o de salida (1) para cada uno de los 8 pins.
   * de esta manera DDRB = B11111111; setea los 8 pines del puerto B como salida.
   * otro ejemplo es DDRC = B11110000; setea los 4 primeros pines del puerto C como entrada, y los siguientes 4 pines como salida.
   */
   
  DDRB = B11111111; // Port B como output
  DDRC = B11111111; // Port C como output
  DDRD = B11111111; // Port D como output

  /*
   *  Arduino utiliza otra variable para guardar el estado de los datos de cada puerto.
   *  PORTB = B11111111; setea los pines del 0 al 7 como HIGH.
   *  PORTD = B00111111; setea los pines del 8 y 9 como LOW y del 10 al 13 como HIGH.
  */
  
  PORTB = B11111111; // Esto prende todos los pins digitales, del 0 al 7 
  PORTD = B11111111; // Esto prende todos los pins digitales, del 8 al 13
}

void loop() {
  currentTime = millis(); // Guardamos el tiempo actual en una variable.
  // Hacemos parpadear cada grupo con un tiempo de retardo distinto.
  // Cambiar los valores para tener distintos tiempos de retardo en cada grupo.
  blinkGroup1(500);
  blinkGroup2(2000);
  blinkGroup3(10000);
}
