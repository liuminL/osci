#ifndef MOVE_H
#define MOVE_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <memory.h>
//#include "move.h"

#define MODE (O_WRONLY | O_TRUNC)

/* static char *gpio_addr[] = {
 *          "/sys/class/gpio/export",
 *          "/sys/class/gpio/gpio61/direction/",
 *          "/sys/class/gpio/gpio61/value/",
 *          "/sys/class/gpio/gpio62/direction/",
 *          "/sys/class/gpio/gpio62/value/",
 *          "/sys/class/gpio/gpio63/direction/",
 *          "/sys/class/gpio/gpio63/value/",
 *          "/sys/class/gpio/gpio64/direction/",
 *          "/sys/class/gpio/gpio64/value/" };
*/

void rio_setreg32(unsigned int addrBase,unsigned int addrOffset,unsigned int value);
int rio_getreg32(unsigned int addrBase,unsigned int addrOffset);
int hlMaintWrite(unsigned int dstId,unsigned short hopcount, unsigned int offset, unsigned int writedata);
int hlMaintRead(unsigned int dstId,unsigned short hopcount, unsigned int offset, int mrdataAdr);

//static int fd;

//#define MODE (O_WRONLY | O_TRUNC)
#define SECSIZE 65536
#define XPAR_AXI_EMC_0_S_AXI_MEM0_BASEADDR 0x80000000
#define WAIT_TICKS 0xffffffff
typedef unsigned short u16;
void flash_set16(unsigned int addrBase,unsigned int addrOffset,unsigned int value);
int flash_get16(unsigned int addrBase,unsigned int addrOffset);
int Erase_Flash(int sectorNum);
int Write_Sector(int sectorNum,int offset,u16 *src_addr,int wr_num);
int Read_Sector(int sectorNum,int rd_num,unsigned short *buf);


#endif // MOVE_H
