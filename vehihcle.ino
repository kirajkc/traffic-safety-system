
 
 #include <SoftwareSerial.h>
int vs =9; // vibration sensor
SoftwareSerial Rfid = SoftwareSerial(2,3);



int enb = 5; 


int in3 = 12; 
int in4 = 13; 

int distancem; 
void setup()
{
   Rfid.begin(9600);
   pinMode(vs, INPUT);  
  Serial.begin(9600);
pinMode(A0,INPUT);
  pinMode(enb, OUTPUT); 


  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);

  
 analogWrite(enb, 0); 

 delay(1000);
 
}


void loop()
{ 
 
  if(Serial.available()>0)
  {
  char n=Serial.read();
  if (n == 'q'||n == 'w')
 control(n);
 if (n=='s')
 limit(n);
 }
 else{ 
 
speedcontrol();
 long measurement =vibration();
  delay(50);
  Serial.println(measurement);
  if (measurement > 0)
   rfid();
 }
   delay(1000);
}

/*-----------------------vibration sensor-------------------------*/
long vibration(){
 
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement

  return measurement;
}

/*------------------Rfid location---------------------*/
void rfid()
{
 int r;
int c=0;
int location = 0;
if (Rfid.available()> 0){
  while(Rfid.available() > 0){
    int r =Rfid.read();
    c=c+r;
    
    if (c==693 || c == 653 || c == 717)
    break;
    Serial.print(r,DEC );
    }
    Serial.println();
Serial.println(c);
  }
if (c== 693)
location =2;
if (c == 653)
location = 1;
switch(location){
  case 1:
  Serial.println("Point A");
  break;
  case 2:
  Serial.println("Point B");
  break;
}
delay(100);
}
/*-------------------------Safe gap maintain-------------------*/
void speedcontrol()
{
  int distance= analogRead(A0);
//int distance = map(distancem, 0 , 1023, 0 ,150); 
Serial.println("Distance = ");
Serial.println(distance);
delay(100);
if(  (distance < 0)   ) 
{
distance = 0; 
} else
if(  (distance >= 0) && (distance<= 30)  ) 
{
  Serial.println("stop");
  analogWrite(enb, 0); 

    digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
  
} else

if(  distance > 30 ) 
{
  Serial.println("go");
  analogWrite(enb, 255); 
 
    digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
 
}
 }
/*----------------------Speed control heavy road----------------*/
void control(char d)
{
  if (d == 'q') 
{
  analogWrite(enb, 110); 
    digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
  Serial.println("Heavy");
  Serial.println();
} 

if(  d == 'w' ) 
{
  analogWrite(enb,255); 
    digitalWrite(in3, HIGH); 
  digitalWrite(in3, LOW);
  Serial.println("gogogog");
}

}
/*-------------------------------Speed Limit Area-----------------*/
 void limit(char p)
 {
 
  if(  p=='s'  ) 
{
  analogWrite(enb, 100); 
    digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
  Serial.println("speed limit");
  Serial.println();
}
else 
{
 
   analogWrite(enb, 255); 
    digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);



}

}
/*------------------*/

 
