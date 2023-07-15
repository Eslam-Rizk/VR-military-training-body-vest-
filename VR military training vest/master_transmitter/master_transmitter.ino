
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

const char* ssid = "Shooting simulator";
const char* password = "11111111";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";       // a string to send back
char  Data[] = "";
int randomIndex;

IPAddress masterIP(192,168,1,10);         //master ip
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress SH1(192,168,1,11);              //shooter1 ip
IPAddress SH2(192,168,1,12);              //shooter2 ip
IPAddress SH3(192,168,1,13);               //shooter3 ip


void setup() {

  WiFi.softAPConfig(masterIP, gateway, subnet);      //configure access point mode
  WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP);
  
  Serial.begin(9600);                               //start serial port at 9600 baud rate
  Serial.println();
  Serial.print("Configuring access point...");

  delay(500);
  if(EEPROM.read(1)>9) {EEPROM.write(1, 1);delay(100);}           //eeprom to change sequence of random() data because it has fixed sequences
  EEPROM.write(1, EEPROM.read(1)+1);
  if(EEPROM.read(1)>9) {EEPROM.write(1, 1);delay(100);}

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.println(incomingPacket);

    if(String(incomingPacket)=="GameOver1"){                 //check received data from unity game
      Serial.write("GameOver1");
      }
    else if(String(incomingPacket)=="GameOver2"){
      Serial.write("GameOver2");
      }
    else if(String(incomingPacket)=="GameOver3"){
      Serial.write("GameOver3");
      }
  }
  if(Serial.available()){
    char z=Serial.read();
    if(z=='x'){
     String shooters[3]={"sh1","sh2","sh3"};
     int h=EEPROM.read(1);
      for(int i=0;i<=10-h;i++){
         randomIndex=(int)random(0,3);                   //get random body part number
        }
     //int randomIndex=(int)random(0,3);
     String unityData=shooters[randomIndex];
     Serial.print(unityData);
     
    if(unityData=="sh1"){//shooter1
      Udp.beginPacket(SH1,4210);
      }//shooter1
    else if(unityData=="sh2"){//shooter2
      Udp.beginPacket(SH2,4210);
      }//shooter2
    else if(unityData=="sh3"){//shooter3
      Udp.beginPacket(SH3,4210);
      }//shooter3
      Udp.write('x');
      Udp.endPacket();
      
    }
    else if(z=='r'){
      Udp.beginPacket(SH1,4210);
      Udp.write('r');
      Udp.endPacket();
      delay(100);
      Udp.beginPacket(SH2,4210);
      Udp.write('r');
      Udp.endPacket();
      delay(100);
      Udp.beginPacket(SH2,4210);
      Udp.write('r');
      Udp.endPacket();
      delay(100);
      }
    }
    delay(1);

}

/*
  test (shell/netcat):
  --------------------
    nc -u 192.168.esp.address 8888
*/
