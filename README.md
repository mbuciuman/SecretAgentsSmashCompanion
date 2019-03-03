# Secret Agent's Smash Companion
This project implements an in-line Gamecube Controller adapter which can modify GC controller inputs, primarily for practicing against a virtual opponent in Smash Bros. Ultimate (or Melee). The adapter primarily uses an Arduino Nano in conjuction with a logic-level converter to step-down the Arduino Nano's digital logic to the Gamecube's 3.3 V data line.

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

### How to Assemble
I included my own designs of a PCB which should make it simple to put together all the necessary parts.

#### Manufacture PCB
I personally like to use OSH Park's 2-layer prototype offering where they will send you 3 PCBs printed from your schematic for a pretty affordable price. For me it was ~12 bucks with shipping, after which it was printed and arrived after 2 weeks.

Link to website: https://oshpark.com/

#### Board Components
Here are the things you should need:
* Official Arduino Nano: https://www.amazon.com/Arduino-A000005-ARDUINO-Nano/dp/B0097AU5OU/
OR
* Arduino Nano Clone: https://www.amazon.com/ELEGOO-Arduino-ATmega328P-Without-Compatible/dp/B0713XK923/ref=sr_1_4?keywords=arduino+nano&qid=1551589218&s=gateway&sr=8-4

__NOTE:__ If you get the Arduino Nano Clone, you may need to change the `board` var in `platformio.ini` depending on its bootloader.

* Bi-directional Logic Level Converter: https://www.sparkfun.com/products/12009
* Gamecube Controller Extension Cable: https://www.amazon.com/gp/product/B001AI7CF2/ref=oh_aui_search_asin_title?ie=UTF8&psc=1
* Header pins (__NOTE:__ should only be needed if the Arduino or the BLLC do not come with header pins already): https://www.sparkfun.com/products/116
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
The adapter should work immediately after plugging it into the console, and you should be able to see the controller being detected by the Gamecube/Switch as if it was just another controller. The Arduino Nano's light should be on showing that it's powered.

If you notice that inputs are not going through and the Arduino light is on, press and hold L+R+A+B to reset the controller, and if that doesn't work, try holding X+Y+START as well.

If it still doesn't work, I would recommend uncommenting the `#define DEBUG` directive in `Constants.hpp`, and commenting out the `#define WRITE` directive to triage the controller input reading.

## Usage

Once you've connected the adapter to the console and the controller is sending all inputs to the console successfully, you'll be able to use the training modes listed below.

### General
Each training mode is mapped in some way to the D-Pad inputs. With the adapter plugged in, no D-Pad inputs will be sent to the console, but will instead be how you select between different training modes.

Each D-Pad direction has a number of different training modes associated with it. So, in order to select a specific mode, you have to press the associated D-Pad direction a certain number of times to cycle to the desired mode.

There are two ways to exit the current mode and return to sending all user-inputs through to the console.
The first is to continue to press the D-Pad direction in the same direction as the current mode until you reach the last mode, then press the D-Pad in the direction one last time (e.g. When in the Mash Jump mode, tap D-Pad Left twice).
The second is to press the D-Pad direction in a different direction than the current mode (e.g. tap D-Pad Down when in the Random DI training mode).

The modes bound to each D-Pad input are listed below:

### DI Training (D-Pad Left)

There are two training modes on D-Pad Left:

* Left/Right DI: inputs left and right DI with a neutral analog stick input alternating between them
* Random DI: inputs DI in a random direction with a neutral analog stick input alternating between each random DI input

### Escape Option Training (D-Pad Right)

There are two training modes on D-Pad Right:

* Mash Jump: inputs jumps continuously
* Mash Air-dodge: inputs air-dodge inputs in random directions

### Input Recording and Input Playback (D-Pad Down and D-Pad Up)

To be written...

## Specific Configuration Options

To be written...

## How to Add Your Own Training Mode

To be written...

## Utilized Licensed Software

* Nicohood Nintendo Library (see link below for License):
https://github.com/NicoHood/Nintendo

* Arduino Eagle CAD Library (used modified Arduino Nano schematic + board) [GPLv3]:
https://github.com/cyberlink1/Arduino-Eagle-Cad-Library

## Miscellaneous

### Gamecube Controller USB Adapter Compatibility
I have successfully tested this code against an Arduino Nano plugged into a Nintendo Gamecube and the official Nintendo 4-port Gamecube Adapter. While I also tried to test the board against a Mayflash 4-port [W012] adapter, I had no luck. YMMV however as some people have reported some Arduinos using Nicohood's Nintendo library working with the Mayflash adapters.

### Author's Note
Just a heads up, this is my first official open-source, C++, and serious embedded development project, so feel free to send me suggestions and improvements. I primarily have studied and developed in Java, C#, and Python, so C++ has been interesting to work with to say the least.
