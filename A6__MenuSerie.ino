#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define button 4
#define led 2

bool ledState=false;
unsigned long currentTime=millis();
unsigned long previousTime=0;
int debounceTimeInterval=700;
void menu(){
  Serial.println("\f\r\t#########################");
  Serial.println("\r\t#  Elige una opcion     #");
  Serial.println("\r\t#  (a) funcion A        #");
  Serial.println("\r\t#  (b) funcion B        #");
  Serial.println("\r\t#  (c) funcion C        #");
  Serial.println("\r\t#  (x) Terminar         #");
  Serial.println("\r\t#########################"); 
}
void funcionA(){
  limpiarOpcionesLCD();
  Serial.println("funcionA");
  lcd.setCursor(2,0);
  lcd.print("x");
  lcd.setCursor(0,1);
  lcd.print("  Ejecutando A  ");
}
void funcionB(){
  limpiarOpcionesLCD();
  Serial.println("funcionB");
  lcd.setCursor(6,0);
  lcd.print("x");
  lcd.setCursor(0,1);
  lcd.print("  Ejecutando B  ");
}
void funcionC(){
  limpiarOpcionesLCD();
  Serial.println("funcionC");
  lcd.setCursor(10,0);
  lcd.print("x");
  lcd.setCursor(0,1);
  lcd.print("  Ejecutando C  ");
}
void finalizar(){
  limpiarOpcionesLCD();
  Serial.println("finalizado");
  lcd.setCursor(14,0);
  lcd.print("x");
  lcd.setCursor(0,1);
  lcd.print("  finalizando   ");
}
void limpiarOpcionesLCD(){
  lcd.setCursor(2,0);
  lcd.print(" ");
  lcd.setCursor(6,0);
  lcd.print(" ");
  lcd.setCursor(10,0);
  lcd.print(" ");
  lcd.setCursor(14,0);
  lcd.print(" ");
}
void setup() {
  lcd.init();
  Serial.begin(115200);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  Serial.print("\f \t \t \n antideBouncing system \n");
  digitalWrite(16,LOW);
  digitalWrite(17,LOW);
  digitalWrite(5,LOW);
  lcd.backlight();
  lcd.setCursor(0,0);
  //         0123456789012345 
  lcd.print("A( )B( )C( )S( )");
  menu();
  while(true)
  {
    currentTime=millis();
    if(Serial.available()){
    char dato=Serial.read();
    if(dato=='x'){
      finalizar();
      break;
    }
    switch(dato){
      case 'a': funcionA(); 
                break;
      case 'b': funcionB();
                break;
      case 'c':funcionC();
                break;
       default: break;
    }
  }
  
  
  
  if(!digitalRead(button)){
    ledState=!digitalRead(led);
    digitalWrite(led,ledState);
    Serial.print("\n \r \t \t El led esta en --> "+ String(ledState)); 
    lcd.setCursor(0,1);
    lcd.print("El led esta en "+ String(ledState));
    while((currentTime-previousTime)<debounceTimeInterval){
      currentTime=millis();
    }
    previousTime=currentTime;
  }
  }
}

void loop() {
  
  
}
