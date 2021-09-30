#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define KERNEL_IMG "../kernel8.img"
#define PORT       "/dev/ttyUSB0"

int send_file (FILE * fp);

int set_interface_attribs (int fd, int speed, int parity);

void set_blocking (int fd, int should_block);

int main (int argc, char * argv[]) {
    // Open file in binary read mode
    FILE * fp = fopen (KERNEL_IMG, "r");
    
    
    if (! fp) {
        fprintf (stderr, "Kernel image '" KERNEL_IMG "'not found!\n");
        return EXIT_FAILURE;
    }
    
    int status = send_file (fp);
    
    fclose (fp);
    
    return status;
}

int send_file (FILE * fp) {
    // Read out file size
    fseek (fp, 0, SEEK_END);
    int size = ftell (fp);
    fseek (fp, 0, SEEK_SET);
    printf ("File size: %d\n", size);
    
    // Write file into buffer
    char buffer[size];
    fread (buffer, sizeof (buffer), 1, fp);
    
    // Send buffer over UART
    int uart = fopen (PORT, "w");
    if (uart < 0) {
        fprintf (stderr, "error %d opening %s: %s\n", errno, PORT, strerror (errno));
        return EXIT_FAILURE;
    }
    set_interface_attribs (uart, B115200, 0);
    set_blocking (uart, 0);
    write (uart, (char *) & size, sizeof (int));
    write (uart, buffer, size);
    
    // sleep for long enough to send everything
//    usleep (size * 100);
    
    return EXIT_SUCCESS;
}

int set_interface_attribs (int fd, int speed, int parity) {
    struct termios tty;
    if (tcgetattr (fd, & tty) != 0) {
        fprintf (stderr, "error %d from tcgetattr\n", errno);
        return - 1;
    }
    
    cfsetospeed (& tty, speed);
    cfsetispeed (& tty, speed);
    
    tty.c_cflag = (tty.c_cflag & ~ CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~ IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN] = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
    
    tty.c_iflag &= ~ (IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    
    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag &= ~ (PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~ CSTOPB;
    tty.c_cflag &= ~ CRTSCTS;
    
    if (tcsetattr (fd, TCSANOW, & tty) != 0) {
        fprintf (stderr, "error %d from tcsetattr\n", errno);
        return - 1;
    }
    return 0;
}

void set_blocking (int fd, int should_block) {
    struct termios tty;
    memset (& tty, 0, sizeof tty);
    if (tcgetattr (fd, & tty) != 0) {
        fprintf (stderr, "error %d from tggetattr\n", errno);
        return;
    }
    
    tty.c_cc[VMIN] = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
    
    if (tcsetattr (fd, TCSANOW, & tty) != 0) {
        fprintf (stderr, "error %d setting term attributes", errno);
    }
}