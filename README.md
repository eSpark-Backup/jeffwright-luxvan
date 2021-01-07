# LuxVan_FirmwareDev
To collaborate upon the hardware development of LuxVan.



The repository contains
- The Source Code for the Arduino Framework.
- The block diagram for circuit connections.


## Instructions
These instructions assume you already have ESP32 BSP (Board Support installed on your Arduino IDE). If the ESP32 BSP is not installed, please refer to the following link for instructions on how to install the BSP.

https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/


1. Start by cloning the repository to your drive.
2. Open the folder, Embedded Development and open the sketch "Sensors_Slave.ino".
3. When the file opens, compile the sketch in Arduino IDE with "ESP32 Dev Module" selected as the Board. There are some libraries that need to be installed prior to compilation in order for the code to compile properly. Skip to "Library Installation" section for further info.
4. After successful compilation, find the circuit connection diagram present in "Board_Design" folder.
5. Try to build up the same circuit as in the sketch and afterwords, press the upload button with the ESP32 connected to the system via MicroUSB cable (remember to select the correct COM port on which the ESP32 is communicating).
6. When the code is uploaded, open serial monitor by navigating towards the top right icon or by pressing CTRL+SHIFT+M keys.
7. Observe the response and debugging information on the Serial Monitor.

### Library Installation
1. Open your Arduino IDE and go to Sketch > Include Library > Manage Libraries. The Library Manager should open.
2. Search for “DHT” on the Search box and install the DHT library from Adafruit. Make sure that "Type" and "Topic" fields are set to "All".
3. After installing the DHT library from Adafruit, type “Adafruit Unified Sensor” in the search box. Scroll all the way down to find the library and install it.
4. After installing the libraries, restart your Arduino IDE.
5. Follow the given pinout for DHT11 connection.
    VCC  -> 3.3V
    GND  -> GND (Common)
    Data -> Pin D15 of ESP32


## LuxVan Components List
The following link contains the currently shortlisted parts to be used inside the Van. We will add more parts as the project commences.

https://docs.google.com/spreadsheets/d/1jJy_U2NoEfE6qIPrXMqqqc--L85cTw6fI8Ediz0iSCw/edit#gid=0
