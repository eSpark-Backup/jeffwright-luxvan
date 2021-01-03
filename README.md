# LuxVan_FirmwareDev
To collaborate upon the hardware development of LuxVan.



The repository contains
- The Source Code for the Arduino Framework.
- The block diagram for circuit connections.


#Instructions

- These instructions assume you already have ESP32 BSP (Board Support installed on your Arduino IDE). If the ESP32 BSP is not installed, please refer to the following link for instructions on how to install the BSP.

https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/


1. Start by cloning the repository to your drive.
2. Open the folder, Embedded Development and open the sketch "Sensors_Slave.ino".
3. When the file opens, compile the sketch in Arduino IDE with "ESP32 Dev Module" selected as the Board.
4. After successful compilation, find the circuit connection diagram present in "Board_Design" folder.
5. Try to build up the same circuit as in the sketch and afterwords, press the upload button with the ESP32 connected to the system via MicroUSB cable (remember to select the correct COM port on which the ESP32 is communicating).
6. When the code is uploaded, open serial monitor by navigating towards the top right icon or by pressing CTRL+SHIFT+M keys.
7. Observe the response and debugging information on the Serial Monitor.
