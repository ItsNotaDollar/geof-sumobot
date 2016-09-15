#**slave Code Info**

The **slave** arduino should be polling the sensors and waiting to trip an interrupt to the master.

###Sensor Loop
Right from the get go the **slave** can start polling for information, no need to wait for the master to start.
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
| RX            | QRD Interrupt             |
| TX            | Pressure Sensor Interrupt |