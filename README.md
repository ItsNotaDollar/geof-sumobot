#**McMaster Sumobot - Team Eh**

###Overview
Welcome to the location of all of **Team Eh?**'s code for the [McMaster Sumobot](http://sumobot.ca/) Competition!!! This is the spot to download and contribute to our amazing robots!

Lets go Jeff/Geoff/JFff/Geoph/Jeph/Djeoph!!!

Team members: 
- **Braden** - [ItsNotaDollar](https://github.com/ItsNotaDollar)
- **BoHan** - Nope...
- **Jack** - Naaaa....
- **Patrick** - [pswitchskates](https://github.com/pswitchskates)

To start working on the project just download/clone in which ever way tickles your fancy.

When you're ready to upload **Submit A Pull Request** and I will merge in changes ASAP. If it's just not good enough... you'll find out...

<!-- ###Master
The **master arduino** will handle the direct inputs from sonar sensors in order to seek out other robots. It also directly controls the motors. 

###Slave
The **slave arduino** will handle the 4 QRD's as well as the pressure sensors. It takes these 6 analog inputs and outputs to 2 interrupt channels on the **master**. It also has 6 digital output pins to communicate values to the **master** \*cough cough\* and commander. Each is going to be an indicator for which sensors have tripped for the master. An interrupt will be sent to tell the **master** to read these inputs, otherwise they will be ignored.
 -->
<!-- ###Arduino Mini Pin Layout
<table style="border: solid 1px black;">
  <tr>
    <th style="border: solid 1px black;">Pin Row 1</th>
    <th style="border: solid 1px black;">Assignment</th>
    <th style="border: solid 1px black;">Pin Row 2</th>
    <th style="border: solid 1px black;">Assignment</th>
  </tr>

  <tr>
    <td style="border: solid 1px black;">D13</td>
    <td style="border: solid 1px black; background-color: rgb(187,255,201)">SONAR RIGHT RECEIVE</td>
    <td style="border: solid 1px black;">D12</td>
    <td style="border: solid 1px black; background-color: rgb(187,255,201)">SONAR LEFT SEND</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">3V3</td>
    <td style="border: solid 1px black; background-color: rgb(140,203,255)">ACCEL PWR</td>
    <td style="border: solid 1px black;">D11</td>
    <td style="border: solid 1px black; background-color: rgb(132,213,0)">SONAR RIGHT RECEIVE</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">AREF</td>
    <td style="border: solid 1px black;"></td>
    <td style="border: solid 1px black;">D10</td>
    <td style="border: solid 1px black; background-color: rgb(132,213,0)">SONAR RIGHT SEND</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A0</td>
    <td style="border: solid 1px black; background-color: rgb(217,137,255)">FRONT LEFT QRD BIN</td>
    <td style="border: solid 1px black;">D9</td>
    <td style="border: solid 1px black; background-color: rgb(255,207,0)">MOTOR RIGHT FORWARD PWM</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A1</td>
    <td style="border: solid 1px black; background-color: rgb(217,137,255)">FRONT RIGHT QRD BIN</td>
    <td style="border: solid 1px black;">D8</td>
    <td style="border: solid 1px black; background-color: rgb(255,207,0)">MOTOR RIGHT FORWARD ON</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A2</td>
    <td style="border: solid 1px black; background-color: rgb(217,137,255)">BACK LEFT QRD BIN</td>
    <td style="border: solid 1px black;">D7</td>
    <td style="border: solid 1px black; background-color: rgb(255,207,0)">MOTOR RIGHT REVERSE ON</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A3</td>
    <td style="border: solid 1px black; background-color: rgb(217,137,255)">BACK RIGHT QRD BIN</td>
    <td style="border: solid 1px black;">D6</td>
    <td style="border: solid 1px black; background-color: rgb(255,207,0)">MOTOR RIGHT REVERSE PWM</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A4</td>
    <td style="border: solid 1px black; background-color: rgb(189,255,255)">ACCEL X-AXIS</td>
    <td style="border: solid 1px black;">D5</td>
    <td style="border: solid 1px black; background-color: rgb(255,148,0)">MOTOR LEFT REVERSE PWM</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A5</td>
    <td style="border: solid 1px black; background-color: rgb(189,255,255)">ACCEL Y-AXIS</td>
    <td style="border: solid 1px black;">D4</td>
    <td style="border: solid 1px black; background-color: rgb(255,148,0)">MOTOR LEFT REVERSE ON</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A6</td>
    <td style="border: solid 1px black;">MOTOR CURRENT SENSOR</td>
    <td style="border: solid 1px black;">D3</td>
    <td style="border: solid 1px black; background-color: rgb(255,148,0)">MOTOR LEFT FORWARD PWM</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">A7</td>
    <td style="border: solid 1px black;"></td>
    <td style="border: solid 1px black;">D2</td>
    <td style="border: solid 1px black; background-color: rgb(255,148,0)">MOTOR LEFT FORWARD ON</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">+5V</td>
    <td style="border: solid 1px black;"></td>
    <td style="border: solid 1px black;">GND</td>
    <td style="border: solid 1px black;"></td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">RST</td>
    <td style="border: solid 1px black;"></td>
    <td style="border: solid 1px black;">RST</td>
    <td style="border: solid 1px black;"></td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">GND</td>
    <td style="border: solid 1px black;"></td>
    <td style="border: solid 1px black;">RX0-&gt;</td>
    <td style="border: solid 1px black; background-color: rgb(217,137,255)">FRONT PRESSURE BIN</td>
  </tr>

  <tr>
    <td style="border: solid 1px black;">VIN</td>
    <td style="border: solid 1px black;"></td>
    <td style="border: solid 1px black;">TX1 &lt;-</td>
    <td style="border: solid 1px black; background-color: rgb(217,137,255)">BACK PRESSURE BIN</td>
  </tr>

</table> -->

###Contributing
If you would like to contribute download the git desktop software and check out this repo. Once you have checked out the master branch create a new branch. **PLEASE** follow the naming convention of `feature-[your username]` as your branch. This will allow me to track which user is creating which pull request to be merged into the master branch.

When committing it is best practice to add commit messages so that debugging can be traced. When creating a pull request please add a description of the features you have added, especially if there are no commit messages...