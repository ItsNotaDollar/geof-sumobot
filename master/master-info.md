#**master Code Info**

The master arduino should be in control of the overall function of the robot. 

###Set Up
Set up code starts by getting an initial sensor reading so that we can precompute where the opponent is and then starts the **5 second**.
<!--Add in screen shot of code here to get nice syntax highlighting instead of code tag-->
```
void setup() {
	
}
```

###Main Loop
The main loop has a very basic implementation, seek & destroy. Each loop we will read from the sonar sensors and determine how to adjust where its going. If an interrupt is triggered then it will read the data from the sensors and adjust accordingly.
<!--Add in screen shot of code here to get nice syntax highlighting instead of code tag-->
```
void loop() {

}
```

###Pins in Use
| Pin           | Function                  |
|:-------------:|:-------------------------:|
| in A0, out D0 | Front Left QRD            |
| in A1, out D1 | Front Right QRD           |
| in A2, out D2 | Back Left QRD             |
| in A3, out D3 | Back Right QRD            |
| in A4, out D4 | Front Pressure Sensor     |
| in A5, out D5 | Back Pressure Sensor      |
|               |                           |
| RX?           | QRD Interrupt             |
| TX?           | Pressure Sensor Interrupt |