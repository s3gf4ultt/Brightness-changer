/*
	This program changes the brightness of screen by
	altering the value of the file /sys/class/leds/lcd-backlight/brightness
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "lcd_brightness_changer.h"

#define BRIGHTNESS_FILE "/sys/class/leds/lcd-backlight/brightness"

int main(int argc, char **args)
{
	if (argc < 2)
	{
		char cmd[100];
		memset(cmd, 0, 100);
		
		sprintf(cmd, "%s brightness_value", args[0]);
		
		print_usage(cmd);
	}
	
	if (geteuid() != 0)
	{
		fputs("This program requires root privileges", stderr);
		
		exit(EXIT_FAILURE);
	}

	int value = strtol(args[1], NULL, 0);

	if (value <= 0)
	{
		fputs("invalid input", stderr);
		
		exit(EXIT_FAILURE);
	}
	else
		set_brightness(value);
	
	return 0;
}

int set_brightness(int brightness)
{
	int fd = open(BRIGHTNESS_FILE, O_WRONLY | O_TRUNC);

	if (fd == -1)
		_exit_err("open syscall failed", fd);

	char data[10];
	memset(data, 0, 10);

	sprintf(data, "%d", brightness);

	int stts = write(fd, data, strlen(data));

	if (stts < 0)
		_exit_err("write error", stts);

	close(fd);

	printf("brightness set to %d successfully\n", brightness);
	
	return 0;
}

void print_usage(char *msg)
{
	fprintf(stderr, "Usage: %s\n", msg);

	exit(EXIT_FAILURE);
}

void _exit_err(char *msg, int ret_value)
{
	const char *err_msg = strerror(ret_value);
	
	fprintf(stderr, "%s: %s\n", msg, err_msg);
	
	exit(EXIT_FAILURE);
}