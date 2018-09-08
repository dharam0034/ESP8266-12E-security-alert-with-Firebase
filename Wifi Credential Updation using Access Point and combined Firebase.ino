/*some code blocks used in this code has been borrowed from open sources codes*/

#include <FS.h> 
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FirebaseArduino.h>

#define DeviceID "12345678"
#define DataDelay 2000


#define firebaseURL "iobrains-3d764.firebaseio.com"
#define authcode "T1ZBCtvALAR9vlNbnOCmYOgYdVTzAq70eTgVGNga"

//#define firebaseURL "flexiot-24e43.firebaseio.com"
//#define authcode "ZTu5uiClAig447UHFVOfjuCqwsA9PeHOhr3nuqpR"

int readpin=12;
int state;
int test =0;
double ADC_Value;
double Battery_Level;
long int chipid=0;

void setup() {
   // delay(50);
    pinMode(readpin, INPUT);
    state = digitalRead(readpin);

    pinMode(A0, INPUT);   
    ADC_Value= (unsigned int) analogRead(A0);
    //Battery_Level= (ADC_Value/1024)*6.50;
    Battery_Level= (ADC_Value/1024)*5.94*1.134;
    
    Serial.begin(115200);delay(5);
    Serial.println("CodeStartsHere");
    //chipid=  ESP.getChipId();
    //Serial.println(chipid);
    //String c= String(chipid); 
    
    WiFiManager wifiManager;
    //wifiManager.resetSettings(); // Not needed in case already have saved credentials

    wifiManager.setSTAStaticIPConfig(IPAddress(192,168,0,115), IPAddress(192,168,0,1), IPAddress(255,255,255,0));// set the custum IP for ESP when working as station mode
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    wifiManager.autoConnect();//fetches ssid and pass from eeprom and tries to connect, If not Found then creates an Access point with mentioned credntials

    Serial.println("connected :))");
    Serial.print("ADC_Value=");Serial.println(ADC_Value);
    Serial.print("Battery_Level=");Serial.println(Battery_Level);
    Serial.print("Status");Serial.println(state);
    send_data();
    Serial.println("ESP8266 in sleep mode");
    ESP.deepSleep(DataDelay * 1000000);
    delay(250);
}
void loop(){
}
void send_data()
{
    Firebase.begin(firebaseURL,authcode);
    Firebase.set("123/DeviceID", DeviceID);
    Firebase.set("123/Battery_Level", Battery_Level);
    Firebase.set("123/status", state);

   // Firebase.set(String(chipid,HEX)+"/DeviceID", chipid);
   // Firebase.set(String(chipid,HEX)+"/Battery_Level", Battery_Level);
   // Firebase.set(String(chipid,HEX)+"/status", state);
}
