#**McMaster Sumobot - Team Eh?**

##Overview
Welcome to the location of all of **Team Eh?**'s code for the [McMaster Sumobot](http://sumobot.ca/) Competition!!! This is the spot to download and contribute to our amazing robots!

Lets go Jeff/Geoff/JFff!!!

Team members: 
- **Braden** - [ItsNotaDollar](https://github.com/ItsNotaDollar)
- **BoHan** - Nope...
- **Jack** - Naaaa....
- **Patrick** - Sorry...

To start working on the project just download/clone in which ever way tickles your fancy.

When you're ready to upload **Submit A Pull Request** and I will merge in changes ASAP. If it's just not good enough... you'll find out...

##Master
The **master arduino** will handle the direct inputs from sonar sensors in order to seek out other robots. It also directly controls the motors. 

##Slave
The **slave arduino** will handle the 4 QRD's as well as the pressure sensors. It takes these 6 analog inputs and outputs to 2 interrupt channels on the **master**. It also has 6 digital output pins to communicate values to the **master** \*cough cough\* and commander. Each is going to be an indicator for which sensors have tripped for the master. An interrupt will be sent to tell the **master** to read these inputs, otherwise they will be ignored.

|Input Pin -> Output Pin|        Sensor         |
|:---------------------:|:---------------------:|
| A0 -> D0              | Front Left QRD        |
| A1 -> D1              | Front Right QRD       |
| A2 -> D2              | Back Left QRD         |
| A3 -> D3              | Back Right QRD        |
| A4 -> D4              | Front Pressure Sensor |
| A5 -> D5              | Back Pressure Sensor  |

- RX - QRD Interrupt
- TX - Pressure Sensor
