/*
 * OS independent serial interface
 *
 * Heavily based on Pirate-Loader:
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 */
#ifndef MYSERIAL_H_
#define MYSERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#ifdef USE_WINDOWS_OS
#include <windows.h>
#include <time.h>

#define B115200 115200
#define B921600 921600

typedef long speed_t;
#else // WIN32

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#endif

#ifdef IS_DARWIN
#include <IOKit/serial/ioss.h>
#include <sys/ioctl.h>

#define B1500000 1500000
#define B1000000 1000000
#define B921600  921600
#endif

int serial_setup(int fd, unsigned long speed);
int serial_write(int fd, const char *buf, int size);
int serial_read(int fd, char *buf, int max_size, int timeout);
int serial_open(const char *port);
int serial_close(int fd);

#ifdef __cplusplus
}
#endif

#endif
