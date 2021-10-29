# Rose - Raspberry OS (Experimental)

A project about building an operating system for the Raspberry Pi 4B. The base for this project is the following
tutorial: https://github.com/s-matyukevich/raspberry-pi-os.git

## Chainloader

To make mounting of the SD card in the makefile work it is currently required to have set up the SD card in `/etc/fstab` to mount in the mnt directory at the project directory root level.  
An example config line would be:

```
# /dev/mmcblk0p1
UUID=7616-4FD8    /home/kjell/git/rose/mnt    vfat   auto,nofail,noatime,user,rw    0 2
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
