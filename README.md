# Rose - Raspberry OS (Experimental)

A project about building an operating system for the Raspberry Pi 4B. The base for this project is the following
tutorial: https://github.com/s-matyukevich/raspberry-pi-os.git

# How to cable

Plug in the black cables of each serial cable into a Ground pin on the Pi (for example pin 6 and 14).

Then **white** of the other cable to 8 (GPIO 14 / TXD)  
Then **green** of one cable to 10 (GPIO 15 / RXD)

The serial cable with **white** connected is transmitting to the computer and has to be plugged into the computer first. It has to show up as `/dev/ttyUSB0`.  
The **green** one is receiving on the Raspberry Pi and has to be `/dev/ttyUSB1`.

![Raspberry Pi pinout](gpio_pins.png)

## Chainloader

`make flash` copies the chainloader onto the boot partition of the sd card (may not work, depends on system
configuration). The chainloader uses the STATUS led ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)
and the POWER led ![#f02015](https://via.placeholder.com/15/f02015/000000?text=+) to indicate its current status. Read
as follows:

- ![#444444](https://via.placeholder.com/15/444444/000000?text=+)![#444444](https://via.placeholder.com/15/444444/000000?text=+)
  ---> Raspberry is off
- ![#444444](https://via.placeholder.com/15/444444/000000?text=+)![#f02015](https://via.placeholder.com/15/f02015/000000?text=+)
  ---> Chainloader makes space. Shouldn't take long. If you see this, your chainloader may be stuck
- ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#444444](https://via.placeholder.com/15/444444/000000?text=+)
  ---> Chainloader is waiting for 32 bit kernel size
- ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#f02015](https://via.placeholder.com/15/f02015/000000?text=+)
  ---> Chainloader is waiting for kernel
