# Secret Agent's Smash Companion
This project implements an in-line Gamecube Controller adapter which can modify GC controller inputs, primarily for practicing against a virtual opponent in Smash Bros. Ultimate (or Melee). It simulates inputs which the Training Mode's CPU cannot, such as inputting frame-perfect DI, various escape options, or recording and playing-back user inputs.

The adapter primarily uses an Arduino Nano in conjuction with a logic-level converter to step-down the Arduino Nano's digital logic to the Gamecube's 3.3 V data line.

## Getting Started
Below are instructions on how to build and upload the code to an Arduino Nano, and how to use the included EAGLE files to get a PCB.

### How to Build and Upload
#### Installing Visual Studio Code
Visual Studio Code was my choice for C++ development. You might have your own preference for IDEs, but this had some nice supportability in inherent functionality and extensions that I found useful. 

You can get Visual Studio Code for free here:
https://code.visualstudio.com/

#### Setting up PlatformIO
I personally found PlatformIO in conjunction with Visual Studio Code to be better than the Arduino IDE for development. Assuming this is expanded to support multiple microcontrollers (ideally with more SRAM), this would make it easy for deployment and testing across a set of enviroments.

PlatformIO can be installed as an extension in Visual Studio Code: https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide

#### Building and Uploading to the Arduino Nano

Connect your Arduino Nano and click on the PlatformIO icon on Visual Studio Code's Activity bar. Select "Upload" from the "Project Tasks", and PlatformIO will begin to build and upload the code to the connected Arduino.

__NOTE:__ You may have to change the `upload_port` variable in `platformio.ini` to match the Arduino's upload port.

Assuming it builds successfully, your code should be on the Arduino and immediately start running.

### How to Put Together
I included my own designs of a PCB which should make it simple to put together all the necessary parts.

#### Manufacture PCB
I personally like to use OSH Park's 2-layer prototype offering where they will send you 3 PCBs printed from your schematic for a pretty affordable price. For me it was ~12 bucks with shipping, after which it was printed and arrived after 2 weeks.

Link to website: https://oshpark.com/

#### Board Components
Here are the things you should need:
* Official Arduino Nano: https://www.amazon.com/Arduino-A000005-ARDUINO-Nano/dp/B0097AU5OU/
OR
* Arduino Nano Clone: https://www.amazon.com/ELEGOO-Arduino-ATmega328P-Without-Compatible/dp/B0713XK923/ref=sr_1_4?keywords=arduino+nano&qid=1551589218&s=gateway&sr=8-4

__NOTE__ If you get the Arduino Nano Clone, you may need to change the `board` var in `platformio.ini` depending on its bootloader.

* Bi-directional Logic Level Converter: https://www.sparkfun.com/products/12009
* Gamecube Controller Extension Cable: https://www.amazon.com/gp/product/B001AI7CF2/ref=oh_aui_search_asin_title?ie=UTF8&psc=1
* Header pins (__NOTE__ should only be needed if the Arduino or the BLLC do not come with header pins already): https://www.sparkfun.com/products/116
* Project box (optional)

#### Assemble Components
Once you have all the parts, you should be able to solder the Arduino Nano and the Bi-directional Logic Level Converter to their header pins, and then directly to the PCB.

For the GC_CONS and GC_CONT pins, you'll have to determine which wires inside of the extension cable corresponds to the pins. There should be 5 wires inside the cable: 5V (for the rumble servo), 3.3V, the Data signal, and two Ground.

There are two methods to determine which ones correspond to which, and both require stripping each individual wire and using a multimeter.

The first method would be to plug in the male-end of the extension cable into a Gamecube (or adapter) and turning it on. Set your multimeter to detect voltage and alternate which wires.

The second method would be to set your multimeter to test continuity, then match up each wire to each termination on the female-end of the socket. The document (also linked with other goodies in the Nicohood/Nintendo repo) has an in-depth guide on how to match up the wires with their associated inputs:

http://www.int03.co.uk/crema/hardware/gamecube/_gc-control1.html

For reference, my wires and their corresponding inputs (on the extension cable I linked in the parts list above) given the image in the document above are listed below:
```
Pin 1: White - 5 V
Pin 2: Red - DATA (3.3V)
Pin 3: Yellow - GND
Pin 4: Black - GND
Pin 5: NOT CONN - NOT CONN
Pin 6: Green - 3.3V
Pin 7: NOT CONN - NOT CONN
```
After determining which wires represent which inputs, you should be able to strip the wires and solder them to the board's pins.

I *HIGHLY* recommend using hot glue on the GC_CONS and GC_CONT inputs as the wires are flimsy and can be easily pulled out of the board.

Also, putting the board into a project box will give it further protection.

#### Connecting to Console
The adapter should work immediately after plugging it into the console, and you should be able to see the controller being detected by the Gamecube/Switch as if it was just another controller.

## Usage

TBD

## Utilized Licensed Software

* Nicohood Nintendo Library (see link below for License):
https://github.com/NicoHood/Nintendo

* Arduino Eagle CAD Library (used modified Arduino Nano schematic + board) [GPLv3]:
https://github.com/cyberlink1/Arduino-Eagle-Cad-Library

## Miscellaneous

### Gamecube Controller USB Adapter Compatibility
I have successfully tested this code against an Arduino Nano plugged into a Nintendo Gamecube and the official Nintendo 4-port Gamecube Adapter. While I also tried to test this against a Mayflash 4-port [W012] adapter, I had no luck. YMMV however as some people have reported it working with the Mayflash adapters.

### Author's Note
Just a heads up, this is my first official open-source, C++, and serious embedded development project, so feel free to send me suggestions and improvements. I primarily have studied and developed in Java, C#, and Python, so C++ has been interesting to work with to say the least.
