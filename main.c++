#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Inicializamos la libreria LCD con sus respectivos puertos de configuracion

#include <IRremote.hpp>
const int rcvPin=11;
IRrecv irrecv(rcvPin);
decode_results results;
bool mostrarDatosLCD = true; // Variable para controlar la visualización en el LCD

#define TMP A0
float temperatura = 0;

#include <Servo.h>
Servo ServoAzul;

void setup()
{ 
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicia el receptor de infrarrojos
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT);
  lcd.begin(16, 2); // Configuramos la pantalla LCD para el numero de columnas y filas (16x2)
  ServoAzul.attach(9); // Asocia el servo al pin 9
  
}
void loop() 
{
  temperatura = tempactual(); // Actualiza la temperatura
  int incendio = DetectorIncendio(); // Verifica si hay incendio
  handleIRControl(); // Maneja el control infrarrojo
  ServoAzul.write(0); // Mueve el servo a la posición 0 grados
  Estaciones(temperatura); // Muestra la estación según la temperatura
  
  if (mostrarDatosLCD && incendio != 1) // Si se debe mostrar en el LCD y no hay incendio
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperatura);
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    delay(500);
  } 
  else 
  {
    lcd.clear(); // Limpiar la pantalla si no se deben mostrar datos
  }
}
void handleIRControl()
{
  if(IrReceiver.decode()) // Si se recibe un código IR
  {
    auto value= IrReceiver.decodedIRData.decodedRawData; 	
    
      if (value == 4278238976)
      {        
        Serial.println("LCD ENCENDIDO");
        mostrarDatosLCD = true; // Mantener la visualización en el LCD
      }
      else if (value == 4244815616)
      {
        Serial.println("LCD APAGADO");
        lcd.clear();
        ServoAzul.write(0);
        mostrarDatosLCD = false; // Dejar de mostrar los datos en el LCD
      }
    IrReceiver.resume(); // Recibe el siguiente valor
  }
}
float tempactual() 
{
  int lectura = analogRead(TMP);
  float temp = map(lectura, 0, 1023, -50, 450); // Mapea el valor leído a un rango de temperatura
  return temp;
}

int DetectorIncendio() 
{
  if (temperatura > 60) // Si la temperatura es mayor a 60 grados
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PELIGRO");
    lcd.setCursor(0, 1);
    lcd.print("INCENDIO");
    ServoAzul.write(90); // Mueve el servo a 90 grados
    delay(500);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
    return 1; // Indica que se detectó un incendio
  } 
  else 
  {
    return 0; // No se detecta un incendio
  }
}
void Estaciones(float temp) 
{
  if (mostrarDatosLCD) // Si se debe mostrar en el LCD
  {
    if (temp > 20 && temp < 30) // Si la temperatura está entre 20 y 30 grados
    {
      lcd.setCursor(0, 1);
      lcd.print("Primavera/Verano");
      delay(500);
    }
    if (temp >= 30 && temp < 60) // Si la temperatura está entre 30 y 60 grados
    {
      lcd.setCursor(0, 1);
      lcd.print("VERANO");
      delay(500);
    }
    if (temp >= 0 && temp < 20) // Si la temperatura está entre 0 y 20 grados
    {
      lcd.setCursor(0, 1);
      lcd.print("INVIERNO");
      delay(500);
    }
  }
}