#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "dQLLyPJ7tQfmtvBJxM3KuYCt7ARm-OpC";
char ssid[] = "khoi-binh";
char pass[] = "123456789";

WidgetLED ledon(V1);
WidgetLED ledoff(V2);
BlynkTimer timer;
#define sensor 2
#define relay 14
int clap = 0;
int button,sensorValue;

BLYNK_WRITE(V3)                                       
{
 button = param.asInt();                                  
}


void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  digitalWrite(relay,1);
  Blynk.begin(auth, ssid, pass);
 
}

void loop()
{ sensorValue = digitalRead(sensor);
  if(sensorValue==0 ){clap++;}
  if(button==0){clap++;}
  if(clap==2){clap=0;}
  if(clap==1){digitalWrite(relay,0);ledon.on();ledoff.off();}
  if(clap==0){digitalWrite(relay,1);ledon.off();ledoff.on();}
  Serial.println(sensor);
  Blynk.run();
  timer.run();
}
