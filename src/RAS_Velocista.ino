/*  IEEE RAS UTN-FRBA
  Proyecto: Robot Educativo Velocista - Seguidor de linea
  prueba sensores y motores III
  configuracion  de sensores:
        MMM
  !oo!  MMM  !oo!
  !  !  MMM  !  !
        MMM
  Autor: Marcelo Acevedo, Elias Reuter.
  GitHub: https://github.com/EliasReuter/RAS_Velocista
  Robot: Velocista v0.2
  - Motor: amarillo 6v.
  - Placa control Arduino UNO (actual Mega para pruebas).
  - Sensor: TRCT5000 plava azul - sensor perpendicular.

*/

#include <Arduino.h>

const byte  VelMAX  = 190;    //Velocidad maxima de robot
const byte  VelMIN  = 128;    //Velocidad minima de robot

const int pinMotor1A = 5;      //(pwm) pin 5 conectado a pin A-IA
const int pinMotor1B = 4;      //(pwm) pin 4 conectado a pin A-IB
const int pinMotor2A = 3;      //(pwm) pin 3 conectado a pin B-IA
const int pinMotor2B = 2;      //(pwm) pin 2 conectado a pin B-IB

const int TCRTDer = A1;       //Sensor derecho
const int TCRTIzq = A0;       //Sensor izquierdo
boolean   valorDer;           //Variable auxiliar
boolean   valorIzq;           //Variable auxiliar

boolean   fueHaciaDerecha = 0;    //
boolean   fueHaciaIzquierda = 0;  //


void setup() {
  Serial.begin(9600);

  pinMode(TCRTDer, INPUT);
  pinMode(TCRTIzq, INPUT);
  pinMode(pinMotor1A, OUTPUT);
  pinMode(pinMotor1B, OUTPUT);
  pinMode(pinMotor2A, OUTPUT);
  pinMode(pinMotor2B, OUTPUT);
}


void loop() {

  //Avanzar();
  //while(!EncontroLinea()){}
  
  valorDer = DetectarLinea(analogRead(TCRTDer));
  valorIzq = DetectarLinea(analogRead(TCRTIzq));

  Serial.print("Dato der: ");
  Serial.print(valorIzq);
  Serial.print(" Dato izq: ");
  Serial.println(valorDer);

  //cuatro opciones:
  //sensores en 1: siguiendo linea
  //sensor izq 0: se fue hacia derecha -> correguir hacia izquierda
  //sensor der 0: se fue hacia izquierda -> correguir hacia derecha
  //sensores en 0: parar
  
  
  if (valorIzq && valorDer) {
    Avanzar();
  }
  if (!valorIzq && valorDer) { //salio hacia derecha
      GiroDerecha();
  }
  if (valorIzq && !valorDer) { //salio por derecha
      GiroIzquierda();
  }
  if (!valorIzq && !valorDer){
    Detener();
  }
}

/* void EncontroLinea()

  Return:
  - boolean. si detecta linea con algun sensor retorna Verdadero.
  Parameters: nada
*/
boolean EncontroLinea(){
  valorDer = DetectarLinea(analogRead(TCRTDer));
  valorIzq = DetectarLinea(analogRead(TCRTIzq));
  return valorDer || valorIzq;
}


/* void DetectarLinea()

  Return:
  - boolean. si blanco retorna Verdadero.
  Parameters:
  - int ByteSensor: lectura analogica de sensor
*/
boolean DetectarLinea(int ByteSensor) {
  //Serial.print("Dato sensor: ");
  //Serial.println(ByteSensor);
  //Serial.print(" : ");
  if (ByteSensor < 600) {
    //Serial.println("Negro");
    return true;
  }
  else {
    //Serial.println("Blanco");
    return false;
  }
}


/* void Avanzar(byte Vel)
  Avanza a velocidad definida por variable.
  Return: nada
  Parameters:
  - byte Vel: velocidad en formato PWM 0 - 255
*/
void AvanzarVel(byte Vel) {
  analogWrite(pinMotor1A, 0);
  analogWrite(pinMotor1B, Vel);
  analogWrite(pinMotor2A, 0);
  analogWrite(pinMotor2B, Vel);
  Serial.print("AvanzarVel: ");
  Serial.println(Vel);
}


/* void Avanzar()
  Avanza a maxima velocidad
  Return: nada
  Parameters: nada
*/
void Avanzar() {
  analogWrite(pinMotor1A, 0);
  analogWrite(pinMotor1B, VelMAX);
  analogWrite(pinMotor2A, 0);
  analogWrite(pinMotor2B, VelMAX);
  Serial.print("Avanzar: ");
  Serial.println(VelMAX);
}


/* void Retroceder()
  Retroceder a maxima velocidad
  Return: nada
  Parameters: nada
*/
void Retroceder() {
  analogWrite(pinMotor1A, VelMAX);
  analogWrite(pinMotor1B, 0);
  analogWrite(pinMotor2A, VelMAX);
  analogWrite(pinMotor2B, 0);
  Serial.println("Retroceder");
}


/* void GiroIzquierda()
  Giro Izquierda a maxima velocidad
  Return: nada
  Parameters: nada
*/
void GiroIzquierda() {
  analogWrite(pinMotor1A, VelMAX);
  analogWrite(pinMotor1B, 0);
  analogWrite(pinMotor2A, 0);
  analogWrite(pinMotor2B, VelMAX);
  Serial.println("GiroIzquierda");
}


/* void GiroDerecha()
  Giro Derecha a maxima velocidad
  Return: nada
  Parameters: nada
*/
void GiroDerecha() {
  analogWrite(pinMotor1A, 0);
  analogWrite(pinMotor1B, VelMAX);
  analogWrite(pinMotor2A, VelMAX);
  analogWrite(pinMotor2B, 0);
  Serial.println("GiroDerecha");
}


/* void GiroIzquierdaVel(byte Vel1, byte Vel2)
  Giro Izquierda a maxima velocidad
  Return: nada
  Parameters:
  - byte Vel1: Velocidad de motor de rueda contrario al giro
  - byte Vel2: Velocidad de motor en rueda de giro
*/
void GiroIzquierdaVel(byte Vel1, byte Vel2) {
  if (Vel1 < VelMAX) {
    analogWrite(pinMotor1A, 0);
    analogWrite(pinMotor1B, Vel1);
    analogWrite(pinMotor2A, 0);
    analogWrite(pinMotor2B, Vel2);
    Serial.print("GiroIzquierdaVel: ");
    Serial.println(Vel1);
  }
}


/* void GiroDerechaVel(byte Vel1, byte Vel2)
  Giro Derecha a maxima velocidad
  Return: nada
  Parameters:
  - byte Vel1: Velocidad de motor de rueda contrario al giro
  - byte Vel2: Velocidad de motor en rueda de giro
*/
void GiroDerechaVel(byte Vel1, byte Vel2) {
  if (Vel1 < VelMAX) {
    analogWrite(pinMotor1A, 0);
    analogWrite(pinMotor1B, Vel2);
    analogWrite(pinMotor2A, 0);
    analogWrite(pinMotor2B, Vel1);
    Serial.print("GiroDerechaVel: ");
    Serial.println(Vel1);
  }
}

/* void Detener()
  Detencion
  Return: nada
  Parameters: nada
*/
void Detener() {
  analogWrite(pinMotor1A, 0);
  analogWrite(pinMotor1B, 0);
  analogWrite(pinMotor2A, 0);
  analogWrite(pinMotor2B, 0);
  Serial.println("Detencion");
}