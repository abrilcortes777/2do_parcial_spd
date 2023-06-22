
#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremote.h>
#define Tecla_1 0xEF10BF00
#define Tecla_2 0xEE11BF00
#define IR  11
#define LED  5
#define LED_AZUL 7
#define SENSOR A0
Servo myServo;
LiquidCrystal lcd (13, 12, 10, 8, 6, 4);
float temperatura = 0;
int lectura_temp = 300;

void setup() 

{
  myServo.attach(2,500,2500);
  Serial.begin(9600);     
  IrReceiver.begin(IR, DISABLE_LED_FEEDBACK); 
  pinMode(LED, OUTPUT); 
  pinMode(LED_AZUL, OUTPUT);
  lcd.begin(16,2);
  lcd.print("Elegir modo:");
  lcd.setCursor(0, 1);
  lcd.print("1 o 2...");
}
void loop() 
{ 
   modos();
}

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

void mostrar_temp()
{
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(5,1);
  lcd.print(temperatura );
  lcd.setCursor(9,1);
  lcd.print(" C");
		
}
void mover_servo()
  
{
  for (int i = 0; i < 5; i++) {
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(500);
  }
}
