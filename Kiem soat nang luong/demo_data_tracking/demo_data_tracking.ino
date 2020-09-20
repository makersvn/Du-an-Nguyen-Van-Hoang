#include <CayenneMQTTESP8266.h>
#include <SoftwareSerial.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <PZEM004T.h> 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>; 
WiFiClient client;
WiFiServer server(80);
String header;
unsigned long time1 = 0;
unsigned long time2 = 0;

String intro = "     Thiet ke, thi cong mo hinh he thong theo doi chi so dien truc tuyen               ";
LiquidCrystal_I2C lcd(0x3f,20,4); 
PZEM004T pzem(D6,D5);  // RX,TX (D2, D1) 
IPAddress ip(192,168,1,1); 
#define CAYENNE_PRINT Serial
#define resetbutton 16 // D0
float voltage_cayenne=0; 
float current_cayenne=0;
float power_cayenne=0; 
float energy_cayenne=0;
float voltage_cayenne1=0; 
float current_cayenne1=0;
float power_cayenne1=0; 
float energy_cayenne1=0;
float v,i,p,e;

char ssid[] = "Hoang-Giao";
char wifiPassword[] = "Hoanggiao";
char username[] = "c1adc220-594f-11ea-ba7c-716e7f5ba423";
char password[] = "63787269ea7abeffb575ceb8f8240e9b595399ef";
char clientID[] = "cff882c0-594f-11ea-b73d-1be39589c6b2";


unsigned long lastMillis = 0; 
void setup()
{
Serial.begin(115200);  
pinMode(resetbutton,INPUT);
Cayenne.begin(username, password, clientID, ssid, wifiPassword); 
pzem.setAddress(ip);
WiFi.begin(ssid, wifiPassword);
server.begin();
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
lcd.init();                      
lcd.init();
lcd.backlight();
lcd.setCursor(0, 1);
lcd.print("    Webserver IP    ");
lcd.setCursor(4, 2);
lcd.print(WiFi.localIP());
//delay(5000);
//lcd.setCursor(0, 0);
//lcd.print(" __________________ ");    
//lcd.setCursor(0, 1);
//lcd.print("|  Pham Minh Giang |");  
//lcd.setCursor(0, 2);
//lcd.print("| MSSV: 2202180044 |"); 
//lcd.setCursor(0, 3);
//lcd.print(" ------------------ "); 
//delay(5000);
//lcd.setCursor(0, 1);
//lcd.print("        Do an       ");   
//lcd.setCursor(0, 2);
//lcd.print("                    ");  
//lcd.setCursor(0, 2);
//for (int i=0; i<intro.length()-20; i++){
//
//    for (int j=1; j<20; j++){
//
//      lcd.setCursor(j,2);
//
//      lcd.print(intro[i+j]);
//
//    }
//
// delay(300);
//}
//
//
//lcd.setCursor(0, 0);
//lcd.print("        V         A ");  
//lcd.setCursor(0, 1);
//lcd.print("Voltage     Current "); 
//lcd.setCursor(0, 2);
//lcd.print("        W         Wh");  
//lcd.setCursor(0, 3);
//lcd.print(" Power      Energy  "); 
}

void appserver(){
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
            client.println("<title>Đồ án: Thiet ke, thi cong mo hinh he thong theo doi chi so dien truc tuyen</title>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"40\" />");
            client.println("<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>");
            client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
            client.println("<style>body{font-size: 30px; background-image: url(\"http://thuthuatphanmem.vn/uploads/2018/06/18/hinh-nen-may-tinh-dep-hinh-nen-mat-go-don-gian_033436280.jpeg\");background-size: cover ;background-repeat: no-repeat; background-position: center;} </style>");
            client.println("<div class=\"container\"><font color= #FFFFFF font size=\"5\">");
            client.println("<img src= \"https://sinhvienspace.com/wp-content/uploads/2012/10/Logo-truong-dai-hoc-cong-nghe-thuc-pham-tp-hcm.jpg\" alt =\"công nghiệp thực phẩm\" width =170px ; heigh= auto ; align= right >");
            client.println("<br>");
            client.println("<p align=left><b>Phạm Minh Giang </b></p>");
            client.println("<p align=left><b>MSSV:2202180044 </b></p>");
            client.println("<p align=left><b>Class:08DHLDT_CT</b></p>");   
            client.println("<br>");
            client.println("<h2 align=center><font color=#003399 size= \"17\"><b> Trường Đại Học Công Nghiệp Thực Phẩm</font></h2>");
            client.println("<h3 align=center><font color=#003399 size= \"15\"><b>Đồ án: Thiết kế, thi công mô hình hệ thống theo dõi chỉ số điện trực tuyến</font></h3>");
            client.println("<br>");
            client.println("<div class=\"row voffset\">");
            client.println("<div class=\"col-md-3\"><font color=#FFFFFF size=\"5\"><i><b>Voltage</font> : </div><div class=\"col-md-3\">" + String(v+5) + String("V") +"</div>");
            client.println("<div class=\"col-md-3\"><font color=#FFFFFF size=\"5\"><i><b>Ampe</font>: </div><div class=\"col-md-3\">" + String(i)+ String("A") +"</div>");
            client.println("<div class=\"col-md-3\"><font color=#FFFFFF size=\"5\"><i><b>Power </font>: </div><div class=\"col-md-3\">" + String(p)+ String("W") + "</div>");
            client.println("<div class=\"col-md-3\"><font color=#FFFFFF size=\"5\"><i><b>Energy</font>: </div><div class=\"col-md-3\">" + String(e) + String("Wh") +"</div>");
            client.println("<br>");
            client.println("<br>");
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
void sensor(){
  v = pzem.voltage(ip);            
if(v >= 0.0)    {                
  voltage_cayenne =v;
  voltage_cayenne1 =v; }              
  if (v < 0.0)         {           
    v = 0.0;           
  voltage_cayenne =0.0;
  voltage_cayenne1 =0.0;}

   i = pzem.current(ip); 
  if(i >= 0.0)  {
  current_cayenne=i; 
  current_cayenne1=i;  }     
  if (i < 0.0) {  
  i = 0.0; 
  current_cayenne= 0.0;
  current_cayenne1= 0.0;}    
   
   p = pzem.power(ip);
  if(p >= 0.0){   
  power_cayenne =p;
  power_cayenne1 =p;                     
 }       
  if (p < 0.0) {
  p = 0.0;
  power_cayenne =0.0;
  power_cayenne1 =0.0;}
  
   e = pzem.energy(ip); 
  if(e >= 0.0){ 
  energy_cayenne =e; 
  energy_cayenne1 =e;
  }
  if (e < 0.0){
    e = 0.0;
    energy_cayenne =0.0;
    energy_cayenne1 =0.0;}   
      
     lcd.setCursor(1, 0);
     lcd.print((v+5),2);
     lcd.setCursor(12, 0);
     lcd.print(i);
     lcd.setCursor(1, 2);
     lcd.print(p,2);
     lcd.setCursor(12, 2);
     lcd.print(e); 
     

  
   if (millis() - lastMillis > 5000) {
       
        lastMillis = millis(); 
        Cayenne.virtualWrite(1,(voltage_cayenne+5)); 
        Cayenne.virtualWrite(2,current_cayenne);
        Cayenne.virtualWrite(3,power_cayenne); 
        Cayenne.virtualWrite(4,energy_cayenne);
        Cayenne.virtualWrite(5,voltage_cayenne1);
        Cayenne.virtualWrite(6,current_cayenne1);
        Cayenne.virtualWrite(7,power_cayenne1);
        Cayenne.virtualWrite(8,energy_cayenne1);
        } 
 
  
  
  }
void loop() 
{  
   
 // sensor();
  appserver();
 //Cayenne.loop(); 

   
  }    
