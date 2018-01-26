//ArduCall
//fix for Arduino Nano R3.
//Beveloped By Timo.
//2018.1.1
//GPL V3
//印度的锑粉们大家好，我们今天要发布的是年轻人的第一根应援棒ArduCall（浓雾）
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int RR=0;                                           //电位器引脚
int RG=1;
int RB=2;
int RW=3;
int LR=6;                                           //PEM引脚
int LG=9;
int LB=10;
int LW=11;
int red=0;
int green=0;
int blue=0;
int white=0;
double battery=0;
LiquidCrystal_I2C lcd(0x3F,16,2);

void batt()                                         //计时器中断函数，检查电池
{                        
    digitalWrite(13,HIGH);
    sei( );
    lcd.clear();
    lcd.print("low Battery!");
    delay(10000);
    digitalWrite(13,LOW);
}

void(* resetFunc) (void) = 0;                       //软复位函数  

void setup()                                        //开机预设
{
  lcd.init();                                       //初始化IIC1602
  lcd.backlight();
  Serial.begin(9600);
  pinMode(12,INPUT_PULLUP);                         //设置按键内部上拉
  pinMode(8,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(LR,OUTPUT);                                //设置灯珠PWM接口
  pinMode(LB,OUTPUT);
  pinMode(LG,OUTPUT);
  pinMode(LW,OUTPUT);
  pinMode(13,OUTPUT);                               //D13上接的是无源蜂鸣器啦
  int KeyVal2 = digitalRead(2);                     //开机操作检查
  int KeyVal4 = digitalRead(4);
  if (KeyVal2==0)                                   //设备自检
  {
    lcd.clear();
    lcd.print("POST Running");
    delay(2000);
    lcd.clear();
    lcd.print("Battery Test");                       //电池测试
    battery=analogRead(7)*0.00488*2;
    lcd.setCursor(0,1);
    lcd.print(battery);
    lcd.print(" V");
    delay(2000);                                     
    lcd.clear();
    lcd.print("Potentiometer Test");
    lcd.setCursor(0,1);
    lcd.print("Test");
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
    analogWrite(LR,32);
    delay(500);
    analogWrite(LR,64);
    delay(500);
    analogWrite(LR,128);
    lcd.setCursor(0,1);
    lcd.print("Blue");                             //第二路
    analogWrite(LB,32);
    delay(500);
    analogWrite(LB,64);
    delay(500);
    analogWrite(LB,128);
    lcd.setCursor(0,1);
    lcd.print("Green");                             //第三路
    analogWrite(LG,32);
    delay(500);
    analogWrite(LG,64);
    delay(500);
    analogWrite(LG,128);
    lcd.setCursor(0,1);
    lcd.print("White");                             //第四路
    analogWrite(LW,32);
    delay(500);
    analogWrite(LW,64);
    delay(500);
    analogWrite(LW,128);
    delay(500);
    resetFunc();
  }
  if (KeyVal4==0)                                      //权益声明
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
  int switch_12= digitalRead(12);                     //判断执行功能
  if (switch_12==0)
    {manual();}
  else
    {automatic();}
}

void manual()                                         //无级调光
{
  while (1)
  {
    battery=analogRead(7)*0.00488*2;
    if(battery<6.2){batt();}
    red=analogRead(RR)/4;
    green=analogRead(RG)/4;
    blue=analogRead(RB)/4;
    white=analogRead(RW)/4;
    Serial.println(red);
    analogWrite(LR,red);
    Serial.println(green);
    analogWrite(LG,green);
    Serial.println(blue);
    analogWrite(LB,blue);
    Serial.println(white);
    analogWrite(LW,white);    
    lcd.setCursor(0,0);
    lcd.print("R ");
    lcd.setCursor(2,0);
    lcd.print(red);
    lcd.setCursor(8,0);
    lcd.print("G ");
    lcd.setCursor(10,0);
    lcd.print(green);
    lcd.setCursor(0,1);
    lcd.print("B ");
    lcd.setCursor(2,1);
    lcd.print(blue);
    lcd.setCursor(8,1);
    lcd.print("W ");
    lcd.setCursor(10,1);
    lcd.print(white);
    delay(1000);
    lcd.clear();
  }
}

void automatic()
{
  while(1)
  {
    
  }
}
