#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Shooting simulator";
const char* password = "11111111";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

IPAddress SH1(192,168,1,11);
IPAddress masterIP(192,168,1,10);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


void setup()
{
  delay(500);
  Serial.begin(9600);
  Serial.println();
  pinMode(2,OUTPUT); 
  digitalWrite(2,HIGH);
  Serial.printf("Connecting to %s ", ssid);
  
  WiFi.begin(ssid, password);WiFi.config(SH1, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
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
    //Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write('k');
    Udp.endPacket();
    if(incomingPacket[0]=='x' || incomingPacket[0]=='0'|| incomingPacket[0]=='1'|| incomingPacket[0]=='2'|| incomingPacket[0]=='3'|| incomingPacket[0]=='4'|| incomingPacket[0]=='5'|| incomingPacket[0]=='6'){//verify this is my shooter1 data
      Serial.write(incomingPacket[0]);          //send data to arduino mega
      digitalWrite(2,LOW);                    //flash built in LED
      delay(100);
      digitalWrite(2,HIGH);
      }
    else if(incomingPacket[0]=='r'){         //check for reset data
      Serial.write("r");
      }
  }
  if(Serial.available()){
    String z=Serial.readString();
    
    Udp.beginPacket(masterIP, localUdpPort);
    if(z=="GameOver1"){                    //if "gameover", notify master esp
      Udp.write("GameOver1");
      }
    Udp.endPacket();
    Serial.flush();
    delay(1);
    }
}
