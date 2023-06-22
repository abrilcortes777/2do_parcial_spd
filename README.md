# Segundo parcial SPD.
## 📚Alumno : Abril Cortés.
---
## ⬆️⬇️Proyecto: Sistema de incendio con Arduino
![Fabulous Snicket](https://github.com/abrilcortes777/2do_parcial_spd/assets/117781604/2e4882ba-d430-41da-9740-eaac475e089e)

## 📝Decripción.
es un sistema de incendio utilizando Arduino que puede
detectar cambios de temperatura y activar un servo motor en caso de detectar un incendio.
Además, se mostrará la temperatura actual y la estación del año en un display LCD.

## 💻Código fuente
~~~c++
void loop() 
{ 
   modos();
}
~~~
La función principal llama a la funciones **'modos()'** que se encargara de mostrar los modos que tiene el sistema.

## void detectar_temp()
~~~c++

void detectar_temp()
{
	temperatura = map(analogRead(SENSOR), 0, 1023,-50, 450);
    if( temperatura < 8 && temperatura > -4)
    {
      
        lcd.clear();
		lcd.setCursor(0,0);
        lcd.print("Invierno");
		digitalWrite(LED_AZUL, HIGH);
		mostrar_temp();
        delay(lectura_temp);
		
    }
    else if (temperatura > 7 && temperatura < 18)
    {
        lcd.clear();
		lcd.setCursor(0,0);
        lcd.print("Otonio");
		digitalWrite(LED_AZUL, HIGH);
		digitalWrite(LED, HIGH);
		mostrar_temp();
        delay(lectura_temp);
		
	  
    }
    else if (temperatura > 18 && temperatura < 23)
      {
        lcd.clear();
		lcd.setCursor(0,0);
        lcd.print("Primavera");
		digitalWrite(LED_AZUL, HIGH);
		digitalWrite(LED, HIGH);
		mostrar_temp();
        delay(lectura_temp);
		
      }
  	else if (temperatura > 23 && temperatura < 40)
      {
        lcd.clear();
		lcd.setCursor(0,0);
        lcd.print("Verano");
		digitalWrite(LED, HIGH);
		mostrar_temp();
        delay(lectura_temp);
      }
	else
    {
      	lcd.clear();
		digitalWrite(LED, LOW);
		digitalWrite(LED_AZUL, LOW);
		lcd.setCursor(0,0);
        lcd.print("temp. fuera");
		lcd.setCursor(0,1);
        lcd.print("de rango:");
		delay(900);
		lcd.clear();
		mostrar_temp();
        delay(lectura_temp);
    }
}
~~~
Esta función detecta la temperatura utilizando un sensor analógico y muestra el resultado en una pantalla LCD. 
Además, enciende o apaga LEDs dependiendo del rango de temperatura detectado.

## void detectar_temp()
~~~c++
void detector_fuego()
{
	temperatura = map(analogRead(SENSOR), 0, 1023,-50, 450);
	if (temperatura > 60)
    {
	  lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("¡ALERTA!");
	  lcd.setCursor(0,1);
  	  lcd.print("FUEGO");
	  digitalWrite(LED, HIGH);
	  mover_servo();
	  delay(900);
	  lcd.clear();
	  mostrar_temp();
      delay(lectura_temp);
    }
	else if (temperatura < -5)
    {
      lcd.clear();
	  digitalWrite(LED, LOW);
      lcd.setCursor(0,0);
  	  lcd.print("temperatura");
	  lcd.setCursor(0,1);
      lcd.print("muy baja");
	  digitalWrite(LED_AZUL, HIGH);
	  delay(900);
	  lcd.clear();
	  mostrar_temp();
      delay(lectura_temp);

    }
	else
    {
      lcd.clear();
	  digitalWrite(LED, LOW);
	  digitalWrite(LED_AZUL, LOW);
      lcd.setCursor(0,0);
  	  lcd.print("No hay");
	  lcd.setCursor(0,1);
      lcd.print("problemas...");
    }
}
~~~
 Esta función detecta la temperatura utilizando un sensor analógico y muestra información en una pantalla LCD y activa o desactiva LEDs dependiendo de los rangos de temperatura detectados. 
 Además, puede realizar otras acciones como mover un servo motor en caso de detectar un posible fuego.

## void modos()
~~~c++
void modos()
{
          
		  
	if (IrReceiver.decode()) 
    {        
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 
        if (IrReceiver.decodedIRData.decodedRawData == Tecla_1)
        {
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Modo 1: Temp");
			lcd.setCursor(0,1);
			lcd.print("y estacion...");
			delay(1000);
			detectar_temp();

        }
        if (IrReceiver.decodedIRData.decodedRawData == Tecla_2)
        { 
        	lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Modo 2: sistema");
			lcd.setCursor(0,1);
			lcd.print("de alarma...");
			delay(1000); 
			detector_fuego();
        }
        IrReceiver.resume();       
      }  
}
~~~
Esta función utiliza un receptor de infrarrojos para cambiar entre diferentes modos de operación según las señales IR recibidas. 
Dependiendo de la señal IR recibida, se ejecutan diferentes bloques de código para manejar el modo de temperatura o el modo de sistema de alarma.

## void mostrar_temp()
~~~c++
void mostrar_temp()
{
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(5,1);
  lcd.print(temperatura );
  lcd.setCursor(9,1);
  lcd.print(" C");
		
}
~~~
 Esta función configura la posición del cursor en la pantalla LCD y muestra la etiqueta "Temp:" seguida del valor
 numérico de la temperatura y la unidad "C" para indicar que se trata de grados Celsius.

## void mover_servo()
~~~c++
void mover_servo()
  
{
  for (int i = 0; i < 5; i++) {
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(500);
  }
}
~~~
 Esta función realiza un movimiento oscilante del servo motor entre dos posiciones extremas (180 grados y 0 grados) en un patrón de ida y vuelta.
 Este patrón se repite 5 veces, con un tiempo de espera de 500 milisegundos entre cada movimiento.

## 🔗Link al proyecto
* [🤓 Proyecto sistema de alarmas](https://www.tinkercad.com/things/3wbWHH8nZXx-fabulous-snicket/editel?sharecode=E5BpPzfJv5vH7woznlglqOaIun_BehWi0o3KqJku0rU)
---
