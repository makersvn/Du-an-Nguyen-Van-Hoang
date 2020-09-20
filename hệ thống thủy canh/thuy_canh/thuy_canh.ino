#include <ESP8266WiFi.h>
#include <WiFiClient.h>; 
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1307.h>
#define BLYNK_PRINT Serial
#define phao 2 // D4
#define relay 16 // D0
#define coi 14 // D5
#define DHTPIN 12  // D6  
#define PHSensor A0 
#define datsensor 13 // D7 
LiquidCrystal_I2C lcd(0x3f,16,2);

DS1307 rtc;
int bom,chedo;
float PH;
int doamdat;
int doamdat1;
char auth[] = "dPj40fO07oAE2mXU5En3s0RePhefWYLz";
char ssid[] = "vanhanh";
char pass[] = "vanhanh123";
WiFiClient client;
WiFiServer server(80);
String header;
String State = "tat";
int outbom1 = 0;
int outbom2 = 0;

#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
int h,t;
int timer1,timer2;
unsigned long time1 = 0;
unsigned long time2 = 0;
BlynkTimer timer;
WidgetLED led (V5);
WidgetLED led1 (V8);
BLYNK_WRITE(V3)
{
  bom = param.asInt(); 

}
BLYNK_WRITE(V6)
{
  chedo = param.asInt(); 

}

 BLYNK_WRITE(V10)
{
  timer1 =param.asInt();
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

BLYNK_WRITE(V11)
{
  timer2 = param.asInt();
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}
unsigned long int avgValue;  
float b;
int buf[10],temp;

void hienthi(){
 uint8_t sec, min, hour, day, month;
 uint16_t year;
 
  rtc.get( &sec, &min, &hour, &day, &month, &year);
  lcd.setCursor(0,0);
  lcd.print(hour/10, DEC);
  lcd.setCursor(1,0);
  lcd.print(hour%10, DEC);
  
  lcd.setCursor(3,0);
  lcd.print(min/10, DEC);
  lcd.setCursor(4,0);
  lcd.print(min%10, DEC);
  
  lcd.setCursor(6,0);
  lcd.print(sec/10, DEC);
  lcd.setCursor(7,0);
  lcd.print(sec%10, DEC);
  
  lcd.setCursor(1,1);
  lcd.print(day/10, DEC);
  lcd.setCursor(2,1);
  lcd.print(day%10, DEC);
  
  lcd.setCursor(4,1);
  lcd.print(month/10, DEC);
  lcd.setCursor(5,1);
  lcd.print(month%10, DEC);

    
 }


void cambienPH(){
  for(int i=0;i<10;i++)       //lấy mẫu của 10 lần
  { 
    buf[i]=analogRead(PHSensor);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sắp xếp giá trị từ nhỏ đến lớn
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //Lấy số trung bình của 6 lần đo
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6;           //Chuyển từ Analog sang milivol
  PH=3.5*phValue;                      //Chuyển Milivol sang độ PH
  lcd.setCursor(11,1);
  lcd.print(PH,1);

}
void mucnuoc(){
    if(digitalRead(phao)==1){
    digitalWrite(coi,1);
    }
  else {
    digitalWrite(coi,0);
    } 

  
  
  }

void bangtay(){

    
  if (bom==1 ){
    digitalWrite(relay,1);led.on();
    lcd.setCursor(11,0);
    lcd.print("ON ");
    }  
  else if (bom==0 ){ 
    digitalWrite(relay,0);led.off();
    lcd.setCursor(11,0);
    lcd.print("OFF");}
  
  }

  
void setup()  
{
Serial.begin(115200);
lcd.init(); 
lcd.backlight(); 
WiFi.begin(ssid, pass);
server.begin();
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
pinMode(coi,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(phao,INPUT_PULLUP);
pinMode(datsensor,INPUT_PULLUP);
digitalWrite(coi,0);
digitalWrite(relay,1);
Blynk.begin(auth, ssid, pass);
dht.begin(); 
//rtc.set( 0, 41, 22, 22, 3, 2020); //08:00:00 24.12.2014 //sec, min, hour, day, month, year 
rtc.start();
lcd.setCursor(0, 0);
lcd.print("De tai: He thong");
lcd.setCursor(0, 1);
lcd.print("   thuy canh    ");
delay(5000);
lcd.setCursor(0, 0);
lcd.print("Nguyen Van Hanh ");
lcd.setCursor(0, 1);
lcd.print("Mssv: 2202180015");
delay(5000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("   IP address:  ");
lcd.setCursor(2, 1);
lcd.print(WiFi.localIP());
delay(4000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  :  :     Off  ");
lcd.setCursor(0,1);
lcd.print("   /   PH:      ");
timer.setInterval(2000L, sendSensor);
}
void webserver(){
WiFiClient client = server.available();   
  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {  
        char c = client.read();          
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                  
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE html><html>");
            client.println("<meta charset=\"utf-8\">");
            client.println("<head>");
            client.println("<title>Hệ thống thủy canh thông minh</title>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"60\" />");
            client.println("<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>");
            client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
            client.println("<style>body{font-size: 24px;} .voffset {margin-top: 30px;}</style>");
            client.println("<div class=\"container\">");
            client.println("<p><b>Nguyễn Văn Hạnh </b></p>");
            client.println("<p><b>MSSV:2202180015 </b></p>");
            client.println("<p><b>Lớp:08DHLDT_CT </p>");
            client.println("<p><b>Trường đại học Công Nghiệp Thực Phẩm </b></p>");
            client.println("<h1><font color=#dd0000 size= \"15\">Hệ thống thủy canh thông minh</font></h1>");
            client.println("<div class=\"row voffset\">");
            client.println("<div class=\"col-md-3\"><font color=#00cc33 size=\"5\">Nhiệt độ</font> : </div><div class=\"col-md-3\">" + String(t) + String("&degC") +"</div>");
            client.println("<div class=\"col-md-3\"><font color=#00cc33 size=\"5\">Độ ẩm không khí</font>: </div><div class=\"col-md-3\">" + String(h)+ String("%") +"</div>");
            client.println("<div class=\"col-md-3\"><font color=#00cc33 size=\"5\">Độ PH </font>: </div><div class=\"col-md-3\">" + String(PH)+ "</div>");
            client.println("<div class=\"col-md-3\"><font color=#00cc33 size=\"5\">Độ ẩm đất</font>: </div><div class=\"col-md-3\">" + String(doamdat1) + String("%") +"</div>");
            client.println("</div>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style>");
            client.println("</script>");
            client.println("</head>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    client.stop();
  }
  }


void loop()
{

  if(chedo==0){
    mucnuoc();
    hienthi();
    cambienPH();
    webserver();
    Blynk.run();
    timer.run();
    if((digitalRead(datsensor)== 1)){
     digitalWrite(relay,1);led.on();
    lcd.setCursor(11,0);
    lcd.print("ON ");
    Blynk.notify("Do am dat< 30%, ban can cung cap them duong chat !");
     }
    else if((timer1==1 )|| (timer2== 1)){
     digitalWrite(relay,1);led.on();
    lcd.setCursor(11,0);
    lcd.print("ON ");
     }
    else if(digitalRead(datsensor)== 0 && (timer1==0 ) && (timer2== 0)){ 
     digitalWrite(relay,0);led.off();
     lcd.setCursor(11,0);
     lcd.print("OFF");
    }}
    
else { 
      
     mucnuoc();  
     hienthi();
     cambienPH();
     webserver();
     Blynk.run();
     timer.run(); 
         

   if((bom==1 )||(timer1==1 )|| (timer2== 1)){
    digitalWrite(relay,1);led.on();
    lcd.setCursor(11,0);
    lcd.print("ON ");
     }
   else if( (bom==0 )||((timer1==0 ) && (timer2== 0))){ 
     digitalWrite(relay,0);led.off();
     lcd.setCursor(11,0);
     lcd.print("OFF");
     
     }}
     
}


void sendSensor(){
  h = dht.readHumidity();
  t = dht.readTemperature(); 
  doamdat= digitalRead(datsensor);
  if(doamdat==1){
    doamdat1=15;
    }
  if(doamdat==0){
    doamdat1=75;
    }
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t); 
  Blynk.virtualWrite(V2, PH); 
 Blynk.virtualWrite(V9, doamdat1); 
}
