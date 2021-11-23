/*

 */

#include "sdCard.h"

int bufsize(char *buf)
{
	int i = 0;
	while (*buf++ != '\0')
		i++;
	return i;
}

void bufclear(void)
{
	for (int i=0; i<SD_BUFFSIZE; i++)
		sdBuffer[i] = '\0';
}

FRESULT SD_Init(void)
{
	fresult = f_mount(&fs, "", 0);
	if (fresult != FR_OK)
		return fresult;

	fresult = SD_createFile();
	if (fresult != FR_OK)
		return fresult;

	strcpy(sdBuffer,"9999999999999999999999999999\n");
	fresult = f_write(&fil, sdBuffer, bufsize(sdBuffer), &bw);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_close(&fil);
	if (fresult != FR_OK)
		return fresult;

	bufclear();

	LDEBUG;
	bufLongCounter = 0;
	sdCounter = 0;

	xTaskCreate(SD_Task, "SD", 128, NULL, 6, &SD_Task_Handler);

	return fresult;
}

FRESULT SD_createFile(void)
{
	int filnum = 0;

	do
	{
		sprintf(filname,"file%.3d.txt",filnum);
		fresult = f_open(&fil, filname, FA_CREATE_NEW | FA_WRITE);
		filnum++;
		LDEBUG;
	}while(fresult == FR_EXIST);

	return fresult;
}

FRESULT SD_write(int bsize, char wBuf[bsize])
{
	fresult = f_open(&fil, filname, FA_OPEN_EXISTING | FA_WRITE);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_lseek(&fil, fil.fsize);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_write(&fil, wBuf, bsize, &bw);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_close(&fil);
	if (fresult != FR_OK)
		return fresult;

	LDEBUG;
	return fresult;
}

FRESULT SD_logger(void)
{

	if (sdCounter <= 9999)
		sdCounter++;
	else
		sdCounter = 0;

	sprintf(sdBuffer,"%04d%04d%04d%04d%04d%04d%04d\n", sdCounter,
			motorRPM,velocidade,
			adcBuf[0],adcBuf[1],
			irTemp[0],irTemp[1]);

	int blen = bufsize(sdBuffer);
	for (int i = 0; i < blen; i++)
		sdLongBuffer[i+(blen*bufLongCounter)] = sdBuffer[i];
	bufLongCounter++;

	if (bufLongCounter >= SD_BUFFSIZE_LONG)
	{
		fresult = SD_write(blen*SD_BUFFSIZE_LONG, sdLongBuffer);
		bufLongCounter = 0;
	}

	LDEBUG;

	return fresult;
}

void SD_Task()
{
	uint32_t TicksDelay = pdMS_TO_TICKS(1000/SD_TASK_HZ);

	while (1)
	{
		fresult = SD_logger();
		if (fresult != FR_OK)
			__NOP();

		vTaskDelay(TicksDelay);
	}
}
