# Rose - Raspberry OS (Experimental)

A project about building an operating system for the Raspberry Pi 4B. The base for this project is the following
tutorial: https://github.com/s-matyukevich/raspberry-pi-os.git

## Chainloader

```make flash``` copies the chainloader onto the boot partition of the sd card (may not works, depends on system
configuration). The chainloader uses the status led () and the POWER led () to indicate its current status. Read as
follows:

* ![#444444](https://via.placeholder.com/15/444444/000000?text=+)![#444444](https://via.placeholder.com/15/444444/000000?text=+)
  ---> Raspberry is off
* ![#444444](https://via.placeholder.com/15/444444/000000?text=+)![#f02015](https://via.placeholder.com/15/f02015/000000?text=+)
  ---> Chainloader makes space. Shouldn't take long. If you see this, your chainloader may be stuck
* ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#444444](https://via.placeholder.com/15/444444/000000?text=+)
  ---> Chainloader is waiting for 32 bit kernel size
* ![#80f015](https://via.placeholder.com/15/80f015/000000?text=+)![#f02015](https://via.placeholder.com/15/f02015/000000?text=+)
  ---> Chainloader is waiting for kernel