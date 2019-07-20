# Arduino-Console-Firmware


<h2> What is this </h1>
This project is an Arduino based game console, that will use cartidges to store game logic. Essentially it aims to be an Arduino Gameboy.

<h2> How does it work? </h2>
The cartridges contain an ATMega138p chip that will run all the games logic, and send the graphics data for the console to draw through I2C.
The console also handles the inputs and will send them to the cartridge when requested.

<h2>What is the purpose of this?</h2>
The purpose of this console is to allow myself to develop many different games for arduino while maintaining one hardware platform for them to run from.

<h2>Current Features</h2>
Almost complete support for primitive graphics from the ADAFRUIT_gfx library.

<a href="https://github.com/leviaviv28/Arduino-Console-Interface"> Library to facilitate communication between cartidges and console. </a>

<h2>Future Improvements</h2>
I am in the proccess of creating a circuit board with just the ATMega1280 and other required componenets (Screen, buttons, etc.) to shrink the footprint of the console down to allow me to create a 3D-Printed case and make the console portable.

I also plan to add additional features such as sound and a system menu.
