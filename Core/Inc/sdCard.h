/*

 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include "main.h"
#include "fatfs_sd.h"
#include "fatfs.h"
#include "string.h"
#include "stdio.h"

#define SD_BUFFSIZE	32
#define SD_BUFFSIZE_LONG 10

typedef struct
{
	FATFS fs;
	FIL fil;
	int blen;
	int blenLong;
	char buffer[SD_BUFFSIZE];
	char longBuffer[(SD_BUFFSIZE_LONG*SD_BUFFSIZE)];
	char filname[12];
	uint16_t counter;
	uint16_t timer;
	BYTE longCounter;
	UINT br, bw;
}SD_CARD_typedef;

TIM_HandleTypeDef htim2;

FRESULT fresult;
SD_CARD_typedef sdCard;

int bufsize(char *buf);
void bufclear(void);

FRESULT SD_Init(void);
FRESULT SD_createFile(void);
FRESULT SD_write(int bsize, char wBuf[bsize]);
FRESULT SD_logger(void);

#endif /* INC_SDCARD_H_ */
