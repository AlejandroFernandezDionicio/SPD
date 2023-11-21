![Tinkercad](Imagenes\imagenprincipal.jpg)


## Integrante
- Alejandro Melnic Fernandez Dionicio


## Proyecto: Sistemas de procesamiento de datos.
![Tinkercad](Imagenes\Tinkercard.png)


## Objetivo
El objetivo de este proyecto es diseñar un sistema de incendio utilizando Arduino que pueda
detectar cambios de temperatura y activar un servo motor en caso de detectar un incendio.
Además, se mostrará la temperatura actual y la estación del año en un display LCD.

## Función principal
Esta funcion se encarga de encender o apagar el LCD 

~~~ C (lenguaje en el que esta escrito)
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
~~~

## :robot: Link al proyecto
- [proyecto](https://www.tinkercad.com/things/bfSXb0RYoRy-proyecto-final)