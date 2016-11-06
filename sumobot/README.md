#**Sumobot - THE Code**

###Program Overview
For this years competition we used QRDs for white line sensors, 2 ultrasonic sensors for locating our opponent and a current sensor to signal when the motors are approaching stall current.

###Use of "Threads"
The use of pseudo threads was very important to the design of the program. It allowed us to poll sensor data at anytime in our loop and interrupt the main code when needed based on that data.



###Sensors
####QRDs
We used the [QRD1113](http://www.digikey.ca/product-detail/en/fairchild-semiconductor/QRD1113/QRD1113-ND/402766) for our white line sensors. They have a simple circuit and are easy to handle in our `qrdThread`. 

####Ultrasonic
We used [HC-SR04](https://www.sparkfun.com/products/13959) for our range sensors. The came with an easy to use [library](http://tutorial.cytron.com.my/2012/10/11/testing-ultrasonic-ranging-module-sn-hc-sr04/) that converted sensor readings directly into cm that made it easy to build logic around. These are the only sensors that are used in the main loop and not a "thread".

####Current Monitor
We added in a current monitor to add even more circuit protection to our robot. Along with circuit protection, this sensor is polled by its thread every 20ms. If the reading is more than the calibrated value it automatically shuts the motors off for a period of time as to not damage any of the hardware.
