
#include <EEPROM.h>

int body[14]={0,0,0,0,0,0,0};//index: 0=head,1=left leg,2=right leg,3=left chest,4=right chest,5=left hand,6=right hand
int randomNumber;
String z="";

void setup(){
  
  delay(100);
  Serial.begin(9600); //start serial port at 115200 baud rate
  Serial.println();
//  EEPROM.begin(512);
  if(EEPROM.read(1)>9) {EEPROM.write(1, 1);delay(100);}           //eeprom to change sequence of random() data because it has fixed sequences
  EEPROM.write(1, EEPROM.read(1)+1);
  if(EEPROM.read(1)>9) {EEPROM.write(1, 1);delay(100);}
  
  pinMode(16,INPUT); 
  
  for(int i=2;i<16;i++){  //set body pins to l
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
    delay(10);
    }
  
  
}

void loop(){
 
  if(Serial.available()){ //if data is ready to read
    char d=Serial.read();
    
    if(d=='x'){                                             //if got shot
      int h=EEPROM.read(1);
      //Serial.println(h);
      for(int i=0;i<=10-h;i++){
         randomNumber=(int)random(0,7);                   //get random body part number
        }                            

      //Serial.println(randomNumber);
      if(randomNumber==0){                                        //if randomNumber is head number, activate led and vibration
        digitalWrite(14,HIGH);
        goto gameOver;}                                               //goto gameOver part
      
      if(body[randomNumber]==0 && randomNumber!=0){                                   //if body[randomNumber] has no damage
        body[randomNumber]=1;                                     //set the damage of body[randomNumber] to 1
        digitalWrite(int(randomNumber*2+1),HIGH);                   //set the 1st damage of body Part((randomNumber*2+1)) led to high
        delay(10);
        
        }
        
        else{                                                      //if there is damage already
          gameOver:                                                    
          Serial.write("GameOver1");                                //shooter is dead ,send gameOver to esp reciever then to esp transmitter then to game to stop shooter weapon from firing
          digitalWrite(int(randomNumber*2),HIGH);             //set the 2nd damage of body Part((randomNumber*2)) led to high
          delay(10);
          while(digitalRead(16)==HIGH){                       //activate the buzzer until reset pin is clicked or 'r' --> (reset) is revcieved
            if(Serial.available()){                            //if 'r' -->(reset) is recieved ,stop buzzer and reset pins to low
              if(Serial.read()=='r'){
                if(digitalRead(14)==HIGH) digitalWrite(14,LOW);
                for(int i=0;i<14;i++){                        //reset body damage by seting body array to 0
                  body[i]=0;
                  }
                  delay(100);
                 for(int i=2;i<16;i++){                        //set body pins to low
                    if(digitalRead(i)==HIGH) digitalWrite(i,LOW); 
                    }
              delay(100);
              goto here;                                                      //break from (while) loop 
              }}
            digitalWrite(15,HIGH);
            delay(250);
            digitalWrite(15,LOW);
            delay(250);
           }
            here:
            if(digitalRead(14)==HIGH) digitalWrite(14,LOW);                                    //set head pin to low
            for(int i=0;i<14;i++){                                     //by pressing push Button, reset body damage by setting body array to 0
              body[i]=0;
              }
            for(int i=2;i<16;i++){                                   //set body pins to low
                digitalWrite(i,LOW);
                }
            }
            delay(100);
      
         }
      
        else if(d=='r'){                                           //reset while shooter still alive when'r' --> (reset) is revcieved
          digitalWrite(14,LOW);
          for(int i=0;i<14;i++){                                      //reset body damage by seting body array to 0
             body[i]=0;
             }
         delay(100);
         for(int i=2;i<16;i++){                                      //set body pins to low
            digitalWrite(i,LOW);
              }
         delay(100);
        }
    }
}
  
