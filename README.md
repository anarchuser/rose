# Rose - Raspberry OS (Experimental)

A project about building an operating system for the Raspberry Pi 4B. The base for this project is the following
tutorial: https://github.com/s-matyukevich/raspberry-pi-os.git

## Setup

### Prerequisites

* Install the cross-compiler `aarch64-none-elf`
* Install `screen` to show output from miniUART
* Install `stty` to send the kernel to the chainloader

### Wiring

We use two serial cables:

* `screen` connects to the first one which only receives. Connect cable `RX` to Pi `TX` (Pin 8 / GPIO 14), and `GND`
* `stty` connects to the second one which only transmits. Connect cable `TX` to Pi `RX` (Pin 10 / GPIO 15), and `GND`

### Repository

Clone this repo and change current working dir into it:

```shell
git clone https://github.com/anarchuser/rose.git
cd rose/
```

### Run

* `make flash`: copy the compiled chainloader onto the sd card (only needed once)
* `make screen`: set up screen connection to first serial cable found
* Put the sd card into the raspberry
* power it and wait for the chainloader to print a ready message
* `make send`: compile and send the kernel for the chainloader to boot

## Structure

In the project directory, each subdirectory holds one operating system:

* `chainloader` loads another operating system (potentially itself) and boots it
* `thorn` is our main operating system were working on

Each directory is divided into `src` and `include`, each of which is again divided into `common` and `kernel`:

* `src`: all C and assembly files
* `include`: all header files
* `common`: everything not closely linked to hardware (distinction not very clear yet)
* `kernel`: everything directly linked to hardware (mailbox calls, system registers, peripherals)

## Virtual Memory

Our current approach to virtual memory is

* `kernel/boot.S`: go to exception level 1,
* `kernel/kernel.c`: boot kernel_main
    * initialise UART and interrupts
    * `kernel/mmu.c`: initialise MMU
    * enable MMU -> system freeze

Note: we only have processor 0 running, all other cores hang indefinitely.