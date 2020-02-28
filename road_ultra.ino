#include <SoftwareSerial.h>
SoftwareSerial gsm(2, 3);
#define trigpin1 4 
#define echopin1 7
#define trigpin2 5
#define echopin2 6 
#define trigpin3 8
#define echopin3 9
 int currentState = 0,currentState2=0;
 int previousState = 0,previousState2=0;
 int duration1, distance1,duration2,duration3, distance2,c=0;

void setup()
{
Serial.begin(9600);
gsm.begin(9600);
pinMode(trigpin1, OUTPUT);
pinMode(echopin1, INPUT);
 pinMode(trigpin2, OUTPUT);
pinMode(echopin2, INPUT);
 pinMode(trigpin3, OUTPUT);
pinMode(echopin3, INPUT);


}
 
void loop()
{
  int p;
if (Serial.available()>0)
{
  char n = Serial.read();
  if ( n == 'a')
  {
 msg(77,1);
 delay(100);

  }
 if (n == 's')
 {
 msg(77,2);
 delay(100);

 }
}
else{
 ult1();
ult2();
 count();
 p = ult3();
 Serial.println(p);
 Serial.print("count=");
 Serial.print(c);
 Serial.print("------------------");
Serial.println();
delay(100);
}
delay(1000);
}

/* ----------------------------Ultrasonic 1------------------------------*/
void ult1()
{
  digitalWrite(trigpin1, HIGH);
 
delayMicroseconds(1000);  
digitalWrite(trigpin1, LOW);
 
 
duration1 = pulseIn(echopin1,HIGH);
 
distance1 = ( duration1 / 2) / 29.1;
Serial.print("inches1:"); 
Serial.println(distance1);
 }

 /* ----------------------------Ultrasonic 2------------------------------*/
void ult2()
{
  digitalWrite(trigpin2, HIGH);
 
delayMicroseconds(1000);  
digitalWrite(trigpin2, LOW);
 
 
duration2 = pulseIn(echopin2,HIGH);
 
distance2 = ( duration2 / 2) / 29.1;
Serial.print("inches2:"); 
Serial.println(distance2);
 }
 /*--------------ult 3-----------------*/
 int ult3()
{
  int distance3,l;
  digitalWrite(trigpin3, HIGH);
 
delayMicroseconds(1000);  
digitalWrite(trigpin3, LOW);
 
 
duration3 = pulseIn(echopin3,HIGH);
 
distance3 = ( duration3 / 2) / 29.1;
Serial.print("inches3:"); 
Serial.println(distance3);
if (distance3 <= 5)
{ l=1;
 Serial.println(l);}
if (distance3 > 5)
{
 l=0;
 Serial.println(l);
}
return l;
 }
 
/* ----------------------------Count Vehicle------------------------------*/
 
void count()
{
  if ((distance1 <=5) && (distance1 !=0))
  {
 currentState = 1;
 }
 else {
 currentState = 0;
 }
 
 delay(200);
 if(currentState != previousState){
 if(currentState == 1){
 c = c + 1;

 delay(1200);
 }
}

if ((distance2 <=5) && (distance2 !=0))
  {
 currentState2 = 1;
 }
 else {
 currentState2 = 0;
 }
 
 delay(200);
 if(currentState2 != previousState2){
 if(currentState2 == 1){
 c = c - 1;

 delay(1200);
 }
}
}

/* ----------------------------GSM module------------------------------*/

void msg(int m, int l)

{ 
  if(m>70)
  {
    Serial.println("send");
      gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     if(l==1)
     {Serial.println("senda");
     gsm.println("AT+CMGS=\"+9779805968955\""); // Replace x with mobile number
     delay(1000);
     gsm.println("Accident occured at ");// The SMS text you want to send
     delay(100);
     gsm.println("Point B");// The SMS text you want to send
     delay(100);
      gsm.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
     }
     if (l==2)
     {Serial.println("sends");
       gsm.println("AT+CMGS=\"+9779818200278\""); // Replace x with mobile number
     delay(1000);
     gsm.println("Accident occured at ");// The SMS text you want to send
     delay(100);
     gsm.println("Point A");// The SMS text you want to send
     delay(100);
      gsm.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
     }
  
      
  }
}
