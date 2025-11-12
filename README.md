# Wireless Distance Detector
A simple schematic that enables two arduinos to wirelessly communicate. When the arduino with an ultrasonic sensor detects the distance to fall under 10cm, it transmits this to the other arduino. The other arduino then lights an LED to indicate this.

This code can be extended to allow two Arduinos to communicate in a way besides distance. For example, this code can be extended to make a radio-based messaging system.

## Components Used
- 2x Arduino
- Lora REYAX RYLR998
- Ultrasonic Sensor
- 2x LEDs

# Schematic Diagrams
The schematic diagram for the transmitter is shown below, for an example board (Arduino Mega). A similar schematic diagram for the receiver is implied, where instead of the ultrasonic sensor, are two LEDs.
![Transmitter-Schematic](https://github.com/user-attachments/assets/4d9b05dd-53ee-43ca-96f7-8e0385cce6b3)
