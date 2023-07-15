# Project overview
This project can be used to provide realistic experience while playing video games or even provide realistic training to military personnel.The idea is to connect the vest to a video game through usb port using **Esp8266 NodeMCU** board and receive hits and injuries data from the game and make it felt using sounds, lights and vibration motors.

# Components
* 2 x Esp8266 NodeMcu (transmitter & receiver).
* 1 x Arduino Mega2560.
* 2 x 3.7v Li-ion battery in series.
* 1 x LM7805.
* 1 x 0.01 uf ceramic capacitor.
* 1 x 0.1 uf radial capacitor.
* 1 x toggle switch.
* 7 x mini vibration motors.
* 1 x buzzer.
* 7 x yellow & red LEDs.
* 2 x green LEDs.
* 7 x 2n2222 transisors.
* 8 x 1k ohm, 14 x 100 ohm and 7 x 27 ohm resistors.
* PCBs and Ethernet wires

# Code
* Check out the transmitter NodeMcu code [here](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/master_transmitter/master_transmitter.ino).
* Check out the receiver NodeMcu code [here](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/shooter1_receiver/shooter1_receiver.ino)
* Check out the Arduino Mega2560 code [here](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/shooter1_code/shooter1_code.ino)

# Steps
* At first we program the 2 NodeMcu and the arduino mega2560 using Arduino IDE and the codes above.
* Design the body PCBs on **Proteus Ares** using the circuit diagram below:
  
  ![ody circuit](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/body%20circuit.png)

  here is the body PCB:
  
  ![body pcb](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/body%20pcb.png)
  ![body pcb](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/pics/chest%20pcb.png)
  
* Design the head PCB using the circuit diagram below:
  
  ![head](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/head%20circuit.png)

  here is the head PCB:
  
  ![head pcb](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/head%20pcb.png)
  
* Design the alarm PCB using the circuit diagram below:
  
  ![alarm](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/alarm%20circuit.png)

  and here is the alarm pcb:
  
  ![alarm pcb](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/alarm%20pcb.png)
  ![alarm pcb](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/pics/chest%20alarm.png)
  
* Connect one Esp8266 NodeMcu (transmitter) to computer using usb cable.
* Then we wire up the other Esp8266 NodeMcu (receiver) to the Arduino board as shown below:
  
  ![main circuit](https://github.com/Eslam-Rizk/VR-military-training-body-vest-/blob/main/VR%20military%20training%20vest/main%20circuit.png)

# Notes
* There are 7 PCBs, one for each arm and Legs, two for chest, one for head and one for alarm.
* Each PCB is connected to te arduino through 2 pins, one fo each LED Exept for head and alarm they are connected through 1 pin only.
* For the PCBs connected through 2 pins, the yellow LED means 1 shot and the red LED means 2 shot and alarm is activated meaning **GAMEOVER**.
* From pin 2 to pin 13, pin 2 and pin 3 is connected to the right arm PCB, pin 4 and 5 is connected to the left arm PCB and so on.
* Pin 14 is connected to the head PCB and pin 15 is the alarm pin. 
