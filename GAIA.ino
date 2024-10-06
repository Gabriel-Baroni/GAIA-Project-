#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
#define dht_porta A0
#define DHTTYPE DHT11

DHT dht(dht_porta, DHTTYPE);
int c = 1;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
int ldr;
String sensorData = "<";

void setup() {
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  while (c == 1) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Bem vindo a Gaia");
    delay(5000);
    lcd_1.clear();
    c += 1;
  }

  lcd_1.begin(16, 2);
  ldr = analogRead(A2);
  int Temperatura = dht.readTemperature();
  int Umidade = dht.readHumidity();
  float luz = analogRead(A2);
  float umdS = analogRead(A1);
  sensorData.concat(luz);
  sensorData.concat(", ");
  sensorData.concat(Temperatura);
  sensorData.concat(", ");
  sensorData.concat(Umidade);
  sensorData.concat(", ");
  sensorData.concat(umdS);
  sensorData.concat(">");
  Serial.println(sensorData);
  sensorData="<";
  
  
  
//Condição para temperatura ruim
  if (Temperatura<20 or Temperatura>32){
    lcd_1.setCursor(0,0);
    lcd_1.print("Temp ruim");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" >:( ");
    delay(1000);
    lcd_1.clear();
  }

//Condição para temperatura boa
  if (20<=Temperatura or Temperatura<=32){
    lcd_1.setCursor(0,0);
    lcd_1.print("Temp boa");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" :) ");
    delay(1000);
    lcd_1.clear();
  }
  
//Condição para luz adequada
   if (luz>700){
    lcd_1.setCursor(0,0);
    lcd_1.print("Luz adequada");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" :) ");
    delay(1000);
    lcd_1.clear();
  }

//Condição para luz inadequada
  if (luz<700){
    lcd_1.setCursor(0,0);
    lcd_1.print("Luz inadequada");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" >:( ");
    delay(1000);
    lcd_1.clear();
  }

//Condição para umidade do adequada
  if (umdS>400){
    lcd_1.setCursor(0,0);
    lcd_1.print("Solo umido");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" :) ");
    delay(1000);
    lcd_1.clear();
  }

//Condição para umidade do solo inadequada
  if (umdS<400){
    lcd_1.setCursor(0,0);
    lcd_1.print("Solo seco");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" >:( ");
    delay(1000);
    lcd_1.clear();
  }

//Condição para umidade do ar adequada
  if (Umidade>50){
    lcd_1.setCursor(0,0);
    lcd_1.print("Ar umido");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" :) ");
    delay(1000);
    lcd_1.clear();
  }

//Condição para umidade do ar inadequada
 if (Umidade<=50){
    lcd_1.setCursor(0,0);
    lcd_1.print("Ar seco ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(" >:( ");
    delay(1000);
    lcd_1.clear();
  }
}

  
