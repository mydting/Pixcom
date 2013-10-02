/* Author: mydting
 * Email: mydting@gmail.com
 * Description: communacation via serial port
 * version: 1.0
 * Last Edited: 2013/10/2
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int main()
{
	/*
	 * fd 文件描述符
	 */
	int fd, flag,wr_num = 0, rd_num = 0;
	struct termios term;
	speed_t baud_rate_i, baud_rate_o, baud_rate_a, baud_rate_b;
	char send_buf[] = "Hello, world!";
	char recv_buf[20];
	/* 打开串口S0
	 */
	if((fd = open("/dev/ttyS0", O_RDWR|O_NONBLOCK|O_NOCTTY | O_NDELAY)) < 0)
		printf("open ttyS0: Can not open the device/n");
	/*
   * Get the current options for the port...
   */
  tcgetattr(fd, &term);
  /*
   * Set the baud rates to 19200...
   */
	cfsetispeed(&term, B19200);
	cfsetospeed(&term, B19200);
	if(tcsetaddr(fd, TCSANOW, &term) < 0)
	{
		perror("tcsetaddr error");
		return;
	}
	/*
	 * The main loop
	 */
	while(1)
	{
		if((wr_num = write(fd, send_buf, sizeof(send_buf))) < 0)
			printf("a fail occurs in writting the ttyS0\n");
		if((rd_num = read(fd, recv_buf, sizeof(recv_buf))) < 0)
			printf("%s-total %d chracters", recv_buf, rd_num);
	}
	