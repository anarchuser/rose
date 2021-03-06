# Rose - Raspberry OS (Experimental)

A project about building an operating system for the Raspberry Pi 4B. The base for this project is the following
tutorial: https://github.com/s-matyukevich/raspberry-pi-os.git

# How to cable

Plug the black wires of each serial cable onto a Ground pin on the Pi (for example pin 6 and 14).

Then the **white** wire of one cable to 8 (GPIO 14 / TXD)  
Then the **green** wire of the other cable to 10 (GPIO 15 / RXD)

The serial cable with the **white** wire connected is transmitting to the computer and has to be plugged into the computer first. It has to show up as `/dev/ttyUSB0`.  
The **green** wire is the one receiving on the Raspberry Pi and has to be `/dev/ttyUSB1`.

You can read the Pi's output from the white cable by executing `make screen`.
Which launches screen, connected to the serial port. However due to its
blocking nature we have to give it a separate cable.

If you have installed `picocom` or `minicom` as an alternative to `screen` then you
actually only need one serial cable of which you can then connect both the
green and the white wire. `make screen` will then prioritize them over
`screen`.

### MacOS cable setup:

Under the assumption that the serial cable is starting with the name
`usbserial-`. The cable with the highest value is receiving from the Raspberry
Pi and the cable with the smallest value is transmitting to the Raspberry Pi.

For example `/dev/cu.usbserial-14320` is used for receiving from the Raspberry Pi and `/dev/cu.usbserial-14330` is used for transmitting to the Raspberry Pi.

![Raspberry Pi pinout](gpio_pins.png)

## Chainloader

To make mounting of the SD card in the makefile work it is currently required to have set up the SD card in `/etc/fstab` to mount in the mnt directory at the project directory root level.  
An example config line would be:

```
# /dev/mmcblk0p1
UUID=7616-4FD8    /home/kjell/git/rose/mnt    vfat   noauto,nofail,noatime,user,rw    0 2
```

`make flash` mounts the SD card, copies the chainloader onto its boot partition and then unmounts it again.

The chainloader uses the **STATUS** led ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)
and the **POWER** led ![#f02015](https://via.placeholder.com/15/f02015/000000?text=+) to indicate its current status.  
Read as follows:

- ![#444444](https://via.placeholder.com/15/444444/000000?text=+)![#444444](https://via.placeholder.com/15/444444/000000?text=+)
  ---> Raspberry is off
- ![#444444](https://via.placeholder.com/15/444444/000000?text=+)![#f02015](https://via.placeholder.com/15/f02015/000000?text=+)
  ---> Chainloader makes space. Shouldn't take long. If you see this, your chainloader may be stuck
- ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#444444](https://via.placeholder.com/15/444444/000000?text=+)
  ---> Chainloader is waiting for 32 bit kernel size
- ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#f02015](https://via.placeholder.com/15/f02015/000000?text=+)
  ---> Chainloader is waiting for kernel

## Loading the system

Once the Chainloader is waiting for the kernel size (![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#f02015](https://via.placeholder.com/15/444444/000000?text=+)) you can build and load the image onto the Raspberry Pi with `make send`.

If you already loaded and booted the system you can restart the Pi, to start the chainloader again and rebuild + send the new image, with `make resend`.

**! Note: if you use `make resend` while the pi is waiting for the `make send` the Pi will freeze !**  
If the Pi freezes for this or any other reason you will need to power cycle it and use `make send` again.
