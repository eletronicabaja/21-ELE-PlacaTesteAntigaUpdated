/*

 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include "main.h"
#include "fatfs_sd.h"
#include "fatfs.h"
#include "string.h"
#include "stdio.h"

#define SD_BUFFSIZE	(4*7 + 2)
#define SD_BUFFSIZE_LONG 2
#define SD_TASK_HZ 100 //Frequencia da task do SD

#define LDEBUG HAL_GPIO_TogglePin(LEDB_GPIO_Port, LEDB_Pin)

TaskHandle_t SD_Task_Handler;

FATFS fs;
FIL fil;
FRESULT fresult;
char sdBuffer[SD_BUFFSIZE];
char sdLongBuffer[(SD_BUFFSIZE_LONG*SD_BUFFSIZE)];
char filname[12];
BYTE bufLongCounter;
uint16_t sdCounter;

UINT br, bw;

void bufclear(void);

FRESULT SD_Init(void);
FRESULT SD_createFile(void);
FRESULT SD_write(int bsize, char wBuf[bsize]);
FRESULT SD_logger(void);

extern int motorRPM, velocidade;
extern int irTemp[2];
extern uint16_t adcBuf[];

void SD_Task();

#endif /* INC_SDCARD_H_ */
