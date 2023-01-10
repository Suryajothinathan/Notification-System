#include<SoftwareSerial.h>
SoftwareSerial Serial1(2,3); //make RX arduino line is pin 2, make TX arduino line is pin 3.
SoftwareSerial gps(10,11);
#include<LiquidCrystal.h>
LiquidCrystal lcd(4,5,6,7,8,9);
#define x A1
#define y A2
#define z A3
int xsample=0;
int ysample=0;
int zsample=0;
#define samples 10
#define minVal -50
#define MaxVal 50
int i=0,k=0;
int  gps status=0;
float latitude=0; 
float logitude=0;                       
String Speed="";
String  gps String="";
String get;
char *test="$GPRMC";
void initModule(String cmd, char *res, int t)
{
while(1)
{
Serial.println(cmd);
Serial1.println(cmd);
delay(100);
while(Serial1.available()>0)
{
if(Serial1.find(res))
}
{
Serial.println(res);
delay(t);
return;
}
else
{
Serial.println("Error");
}
}
}
delay(t);
}
}
void setup() 
{
  Serial1.begin(9600);
  Serial.begin(9600);
  lcd.begin(16,2);  
  lcd.print("Accident Alert  ");
  lcd.setCursor(0,1);
  lcd.print("     System     ");
  delay(2000);
  lcd.clear();
  lcd.print("Initializing");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  delay(1000);
  Serial.println("Initializing....");
  initModule("AT","OK",1000);
  initModule("ATE1","OK",1000);
  initModule("AT+CPIN?","READY",1000);  
  initModule("AT+CMGF=1","OK",1000);     
  initModule("AT+CNMI=2,2,0,0,0","OK",1000);  
  Serial.println("Initialized Successfully");
  lcd.clear();
  lcd.print("Initialized");
  lcd.setCursor(0,1);
  lcd.print("Successfully");
  delay(2000);
  lcd.clear();
  lcd.print("Callibrating ");
  lcd.setCursor(0,1);
  lcd.print("Acceleromiter");
  for(int i=0;i<samples;i++)
  {
    xsample+=analogRead(x);
    ysample+=analogRead(y);
    zsample+=analogRead(z);
  }
  xsample/=samples;
  ysample/=samples;
  zsample/=samples;
  Serial.println(xsample);
  Serial.println(ysample);
  Serial.println(zsample);
  delay(1000);
  lcd.clear();
  lcd.print("Waiting For GPS");
  lcd.setCursor(0,1);
  lcd.print("     Signal    ");
  delay(2000);
  gps.begin(9600);
  get gps();
  show_coordinate();
  delay(2000);
  lcd.clear();
  lcd.print("GPS is Ready");
  delay(1000);
  lcd.clear();
  lcd.print("System Ready");
  Serial.println("System Ready..");
}
void loop() 
{
  int value1=analogRead(x);
  int value2=analogRead(y);
  int value3=analogRead(z);
  int xValue=xsample-value1;
  int yValue=ysample-value2;
  int zValue=zsample-value3;
  Serial.print("x=");
  Serial.println(xValue);
  Serial.print("y=");
  Serial.println(yValue);
  Serial.print("z=");
  Serial.println(zValue);
  if(xValue < minVal || xValue > MaxVal  || yValue < minVal || yValue > MaxVal  || zValue < minVal || zValue > MaxVal)
    {
      get gps();
      show_coordinate();
      lcd.clear();
      lcd.print("Sending SMS ");
      Serial.println("Sending SMS");
      Send();
      Serial.println("SMS Sent");
      delay(2000);
      lcd.clear();
      lcd.print("System Ready");
      }       
}
void gpsEvent()
{
  gpsString="";
  while(1)
  {
   while (gps.available()>0)            //Serial incoming data from GPS
   {
    char inChar = (char)gps.read();
     gpsString+= inChar;                    //store incoming data from GPS to temparary string str[]
     i++;
     if (i < 7)                      
    {
      if(gpsString[i-1] != test[i-1])         //check for right string
      {
        i=0;
        gpsString="";
        }
        }
        if(inChar=='\r')
        {
     if(i>60)
     {
       gps_status=1;
       break;
     }
     else
     {
       i=0;
     }
    }
  }
