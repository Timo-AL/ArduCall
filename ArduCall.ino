#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int RR=0;
int RG=1;
int RB=2;
int RW=3;
int red=0;
int green=0;
int blue=0;
int white=0;
LiquidCrystal_I2C lcd(0x3F,16,2);

void(* resetFunc) (void) = 0; //软复位函数  

void setup()                 //开机预设
{
  lcd.init();                //初始化IIC1602
  lcd.backlight();
  Serial.begin(9600);
  pinMode(8,INPUT_PULLUP);  //设置按键内部上拉
  pinMode(4,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(6,OUTPUT);        //设置灯珠PWM接口
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  int sensorVal2 = digitalRead(2);
  if (sensorVal2==0)       //权益声明
  {
    lcd.clear();
    lcd.print("ArduCall");
    lcd.setCursor(0,1);
    lcd.print("Develop by Timo");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Licens");
    lcd.setCursor(0,1);
    lcd.print("software:GPL V3");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hardware");
    lcd.setCursor(0,1);
    lcd.print("CC BY-SA 3.0");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Never remver");
    lcd.setCursor(0,1);
    lcd.print("this.   Thanks");
    delay(4000);
    resetFunc();
  }
}

void loop()                        //执行预设
{
  int sensorVal8 = digitalRead(8);
  int sensorVal4 = digitalRead(4);
  int sensorVal2 = digitalRead(2);
  red=analogRead(RR)/4;
  green=analogRead(RG)/4;
  blue=analogRead(RB)/4;
  white=analogRead(RW)/4;
  Serial.println(red);
  analogWrite(6,red);
  Serial.println(green);
  analogWrite(9,green);
  Serial.println(blue);
  analogWrite(10,blue);
  Serial.println(white);
  analogWrite(11,white);
  Serial.print("DP8:");
  Serial.println(sensorVal8);
  Serial.print("DP4:");
  Serial.println(sensorVal4);
  Serial.print("DP2:");
  Serial.println(sensorVal2);
  delay(5000);
}
