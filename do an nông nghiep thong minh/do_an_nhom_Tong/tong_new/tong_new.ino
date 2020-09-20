#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1307.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

char auth[] = "9Xw3O-C3TgknySe06abK2AVaL1oPdiFX";
char ssid[] = "Hoang-Hao"; //VIETTEL_RXk4yD
char pass[] = "2anhdeptrai";  //0353326024
WiFiClient client;
WiFiServer server(80);
String header;
String output5State = "tat";
String output4State = "tat";
LiquidCrystal_I2C lcd(0x27,20,4);
DS1307 rtc;
int as,asvalue,dat,datvalue;
int pinAS, SW; 
float t,h;
#define DHTPIN 0      //D3 
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

#define sensor A0
#define anhsang 14// D4
#define doamdat 2 //D5
#define pump 12  //D6
#define button 13  //D7
#define relay 15  //D8
BlynkTimer timer;
int dem=0,vong=0;
int pinValue,pinValue1;
void hienthi(){
 uint8_t sec, min, hour, day, month;
 uint16_t year;
 rtc.get(&sec, &min, &hour, &day, &month, &year);
  lcd.setCursor(10,0);
  lcd.print(hour/10, DEC);
  lcd.setCursor(11,0);
  lcd.print(hour%10, DEC);
  
  lcd.setCursor(13,0);
  lcd.print(min/10, DEC);
  lcd.setCursor(14,0);
  lcd.print(min%10, DEC);

  lcd.setCursor(8,1);
  lcd.print(day/10, DEC);
  lcd.setCursor(9,1);
  lcd.print(day%10, DEC);
  
  lcd.setCursor(11,1);
  lcd.print(month/10, DEC);
  lcd.setCursor(12,1);
  lcd.print(month%10, DEC);
    
  lcd.setCursor(14,1);
  lcd.print(year, DEC);

  
  }

BLYNK_WRITE(V5)
    {
      pinValue = param.asInt(); 
    }
 BLYNK_WRITE(V6)
    {
      pinValue1 = param.asInt(); 
    }
BLYNK_WRITE(V10)
    {
      SW = param.asInt(); 
    }
  BLYNK_WRITE(V7)
{
 pinAS = param.asInt(); 
  }
WidgetLED led(V8);
WidgetLED led1(V9);
void setup() { 
  pinMode(pump,OUTPUT); 
 digitalWrite(pump,1);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 server.begin();
  dht.begin();
  rtc.start();
 //rtc.set(10, 43, 10, 1, 11, 2019); //08:00:00 24.12.2014 //sec, min, hour, day, month, year
 lcd.clear();
  lcd.init(); 
  lcd.backlight(); 
  pinMode(button,INPUT_PULLUP);
  pinMode(doamdat,OUTPUT);
  pinMode(anhsang,OUTPUT);
  pinMode(relay,OUTPUT); 
 digitalWrite(anhsang,0);
 digitalWrite(doamdat,0);
 digitalWrite(relay,0);
lcd.setCursor(0, 0);
lcd.print(" Truong dai hoc SPKT");
lcd.setCursor(0, 1);
lcd.print("    Bao Cao Do An   ");
lcd.setCursor(0, 2);
lcd.print("  He Thong Giam Sat ");
lcd.setCursor(0, 3);
lcd.print(" Vuon Cay Thong Minh");
delay(3500);
lcd.setCursor(0, 0);
lcd.print("GVHD:               ");
lcd.setCursor(0, 1);
lcd.print("  Nguyen Thanh Nghia");
lcd.setCursor(0, 2);
lcd.print("SVTH:    Ho Van Tong");
lcd.setCursor(0, 3);
lcd.print("    Dang T.Hong Loan");
delay(4000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("  Time:     :       ");
lcd.setCursor(0, 1);
lcd.print("  Date:   /  /      ");
lcd.setCursor(0, 2);
lcd.print("AS:    %   DAD:    %");
lcd.setCursor(0, 3);
lcd.print("ND:    C  DAKK:    %");
Blynk.begin(auth, ssid, pass);
 timer.setInterval(1000L, cambien);
}

void cambien(){
 digitalWrite(anhsang,1);
 delay(100);
 as= analogRead(sensor);
 asvalue= map(as,0,1023,100,0);
 digitalWrite(anhsang,0);
 digitalWrite(doamdat,1);
 delay(100);
 dat=map(analogRead(sensor),0,1023,100,0);
 datvalue=dat-40;
 digitalWrite(doamdat,0); 
 t = dht.readTemperature();
 h = dht.readHumidity();
 lcd.setCursor(3, 2);
 lcd.print(asvalue/100);
 lcd.setCursor(4, 2);
 lcd.print(asvalue/10);
 lcd.setCursor(5, 2);
 lcd.print(asvalue%10);
 lcd.setCursor(15, 2);
 lcd.print(datvalue/100);
 lcd.setCursor(16, 2);
 lcd.print(datvalue/10);
 lcd.setCursor(17, 2);
 lcd.print(datvalue%10);
 lcd.setCursor(3, 3);
 lcd.print(t,1);
 lcd.setCursor(15, 3);
 lcd.print(h,1); 
 Blynk.virtualWrite(V1, h);
 Blynk.virtualWrite(V2, t);
 Blynk.virtualWrite(V3, asvalue);
 Blynk.virtualWrite(V4, datvalue);

 
  }

void manu(){
if(digitalRead(button)==0){
delay(50);dem++;while(digitalRead(button)==0);}
if(dem==2){dem=0;}
if((dem==1)){digitalWrite(pump,0);led.on();}
if((dem==0)){digitalWrite(pump,1);led.off();}
if(pinValue==1 && dem==0){dem=1;}
if(pinValue1==1 && dem==1){dem=0;}
if(pinAS==1){digitalWrite(relay,1); led1.on();}
if(pinAS==0){digitalWrite(relay,0);led1.off();}

}
void automatic(){

 if((asvalue<20) ){Blynk.notify("Troi da toi roi! Mo den len nao"); digitalWrite(relay,1);led1.on();}
 if((asvalue>40) ){ digitalWrite(relay,0);led1.off();}
 if((datvalue<35) ){Blynk.notify("Dat kho ! Yeu cau tuoi them nuoc"); digitalWrite(pump,0);led.on();}
 if((datvalue>35) ){ digitalWrite(pump,1);led.off();}
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

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<meta charset=\"utf-8\">");
            client.println("<head>");
            client.println("<title>Äá»“ Ãn Tá»‘t Nghiá»‡p</title>");
            client.println("<meta http-equiv=\"refresh\" content=\"5\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"60\" />");
            client.println("<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>");
            client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
            client.println("<style>body{font-size: 24px;} .voffset {margin-top: 30px;}</style>");
            client.println("<div class=\"container\">");
            client.println("<p><b>TrÆ°á»ng Ä‘áº¡i há»c SÆ° Pháº¡m Ká»¹ Thuáº­t TP.HCM</b></p>");
             client.println("<p><b>Äá» TÃ i: Há»‡ Thá»‘ng GiÃ¡m SÃ¡t VÆ°á»n CÃ¢y ThÃ´ng Minh</b></p>");
            client.println("<p><b>Class:186410SP2 </b></p>");
            client.println("<p><b>GiÃ¡o viÃªn hÆ°á»›ng dáº«n</b>: Tháº§y Nguyá»…n Thanh NghÄ©a</p>");
            client.println("<p><b>ThÃ nh viÃªn</b>: Há»“ VÄƒn TÃ²ng</p>");
            client.println("<p> Äáº·ng TrÆ°Æ¡ng Há»“ng Loan</p>");
            client.println("<h1><font color=#dd0000>Sensor value</font></h1>");
            client.println("<div class=\"row voffset\">");
            client.println("<div class=\"col-md-3\"><font color=#00cc33>Nhiá»‡t Ä‘á»™</font> : </div><div class=\"col-md-3\">" + String(t) + String("&degC") +"</div>");
            client.println("<div class=\"col-md-3\"><font color=#00cc33>Äá»™ áº©m khÃ´ng khÃ­</font>: </div><div class=\"col-md-3\">" + String(h)+ String("%") +"</div>");
            client.println("<div class=\"col-md-3\"><font color=#00cc33>Ãnh sÃ¡ng </font>: </div><div class=\"col-md-3\">" + String(asvalue)+ String("%")+ "</div>");
            client.println("<div class=\"col-md-3\"><font color=#00cc33>Äá»™ áº©m Ä‘áº¥t</font>: </div><div class=\"col-md-3\">" + String(datvalue)+ String("%")+ "</div>");
            
            client.println("</div>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style>");
            client.println("</script>");
            client.println("</head>");
            
            // Web Page Heading
           /* client.println("<body><h1><font color=#dd0000>Wemos control</font></h1>");
            client.println("<p>BÆ M </p>");
            // If the output5State is off, it displays the ON button       
            if (digitalRead(pump)==1) {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">ON</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>ÄÃˆN </p>");
            // If the output4State is off, it displays the ON button       
            if (digitalRead(relay)==0) {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">ON</button></a></p>");
            }
*/

            client.println("</body></html>");
            
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


void loop() { 
 Blynk.run();
 timer.run();
 hienthi();
 webserver(); 
 if (SW==0){
  automatic(); 
  }  
 if (SW==1){
  manu();
  }
 cambien();


  
}
