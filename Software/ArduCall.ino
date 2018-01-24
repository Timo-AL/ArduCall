//ArduCall
//fix for Arduino Nano R3.
//Beveloped By Timo.
//2018.1.1
//GPL V3
//印度的锑粉们大家好，我们今天要发布的是年轻人的第一根应援棒ArduCall（浓雾）
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MsTimer2.h>
int RR=0;
int RG=1;
int RB=2;
int RW=3;
int red=0;
int green=0;
int blue=0;
int white=0;
double battery=0;
LiquidCrystal_I2C lcd(0x3F,16,2);

void batt()                                         //计时器中断函数，检查电池
{                        
  battery=analogRead(6)*0.00488*2;
  if(battery<3.1)
  {
    digitalWrite(13,HIGH);
    sei( );
    lcd.clear();
    lcd.print("low Battery!");
    delay(10000);
    digitalWrite(13,LOW);
  }
}

void(* resetFunc) (void) = 0;                       //软复位函数  

void setup()                                        //开机预设
{
  lcd.init();                                       //初始化IIC1602
  lcd.backlight();
  Serial.begin(9600);
  pinMode(8,INPUT_PULLUP);                          //设置按键内部上拉
  pinMode(4,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(6,OUTPUT);                                //设置灯珠PWM接口
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  MsTimer2::set(600000, batt);                     //电池检查定时器中断
  MsTimer2::start();
  int sensorVal2 = digitalRead(2);                  //开机操作检查
  int sensorVal4 = digitalRead(4);
  if (sensorVal4==0)                                //设备自检
  {
    lcd.clear();
    lcd.print("POST Running");
    delay(2000);
    lcd.clear();
    lcd.print("Battery Test");                       //电池测试
    battery=analogRead(6)*0.00488*2;
    lcd.setCursor(0,1);
    lcd.print(battery);
    lcd.print(" V");
    delay(2000);                                     
    lcd.clear();
    red=analogRead(RR)/4;                            //获取电位器数据
    green=analogRead(RG)/4;
    blue=analogRead(RB)/4;
    white=analogRead(RW)/4;
    delay(2000);                                     //电位器数据回显
    lcd.clear();
    lcd.print("Red  ");
    lcd.print(red);
    lcd.setCursor(0,1);
    lcd.print("Green  ");
    lcd.print(green);
    delay(2000);
    lcd.clear();
    lcd.print("Blue  ");
    lcd.print(blue);
    lcd.setCursor(0,1);
    lcd.print("White  ");
    lcd.print(white);
    delay(2000);
    lcd.clear();
    lcd.print("LED&PWM Test");                      //灯珠及PWM机能测试
    lcd.setCursor(0,1);
    lcd.print("Red");                               //第一路
    analogWrite(6,32);
    delay(500);
    analogWrite(6,64);
    delay(500);
    analogWrite(6,128);
    lcd.setCursor(0,1);
    lcd.print("Blue");                             //第二路
    analogWrite(9,32);
    delay(500);
    analogWrite(9,64);
    delay(500);
    analogWrite(9,128);
    lcd.setCursor(0,1);
    lcd.print("Green");                             //第三路
    analogWrite(10,32);
    delay(500);
    analogWrite(10,64);
    delay(500);
    analogWrite(10,128);
    lcd.setCursor(0,1);
    lcd.print("White");                             //第四路
    analogWrite(11,32);
    delay(500);
    analogWrite(11,64);
    delay(500);
    analogWrite(11,128);
    delay(500);
    resetFunc();
  }
  if (sensorVal2==0)                              //权益声明
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
    lcd.print("Software:GPL V3");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hardware:");
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

void loop()                                           //执行预设
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
