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
		sdCard.buffer[i] = '\0';
}

FRESULT SD_Init(void)
{
	fresult = f_mount(&sdCard.fs, "", 0);
	if (fresult != FR_OK)
		return fresult;

	fresult = SD_loadSettings();
	if (fresult != FR_OK)
		return fresult;


	fresult = SD_createFile();
	if (fresult != FR_OK)
		return fresult;

	bufclear();

	LDEBUG;
	sdCard.longCounter = 0;
	sdCard.blen = 0;
	sdCard.blenLong = 0;
	sdCard.counter = 0;
	sdCard.timer = 0;

	HAL_TIM_Base_Start_IT(&htim2);

	return fresult;
}

FRESULT SD_loadSettings(void)
{
	int len;

	sprintf(sdCard.filname,"settings.ini");
	fresult = f_open(&sdCard.fil, sdCard.filname, FA_OPEN_EXISTING | FA_READ);

	if (fresult == FR_NO_FILE)
	{
		fresult = f_open(&sdCard.fil, sdCard.filname, FA_OPEN_ALWAYS | FA_WRITE);
		if (fresult != FR_OK)
			return fresult;

		len = sprintf(sdCard.buffer,"MODE=0\n");
		fresult = f_write(&sdCard.fil, sdCard.buffer, len, &sdCard.bw);
		if (fresult != FR_OK)
			return fresult;

		fresult = f_close(&sdCard.fil);
		if (fresult != FR_OK)
			return fresult;
	}
	else if (fresult == FR_OK)
	{
		fresult = f_read(&sdCard.fil, sdCard.longBuffer, SD_BUFFSIZE_LONG*SD_BUFFSIZE-1, &sdCard.br);
		if (fresult != FR_OK)
			return fresult;

		char setting[16];


	}

	return fresult;
}

FRESULT SD_createFile(void)
{
	int len;

	int filnum = 0;

	do
	{
		sprintf(sdCard.filname,"file%.3d.txt",filnum);
		fresult = f_open(&sdCard.fil, sdCard.filname, FA_CREATE_NEW | FA_WRITE);
		filnum++;
		LDEBUG;
	}
	while(fresult == FR_EXIST);

	len = sprintf(sdCard.buffer,"\n");
	fresult = f_write(&sdCard.fil, sdCard.buffer, len, &sdCard.bw);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_close(&sdCard.fil);
	if (fresult != FR_OK)
		return fresult;

	return fresult;
}

FRESULT SD_write(int bsize, char wBuf[bsize])
{
	fresult = f_open(&sdCard.fil, sdCard.filname, FA_OPEN_EXISTING | FA_WRITE);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_lseek(&sdCard.fil, sdCard.fil.fsize);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_write(&sdCard.fil, wBuf, bsize, &sdCard.bw);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_close(&sdCard.fil);
	if (fresult != FR_OK)
		return fresult;

	LDEBUG;

	return fresult;
}

FRESULT SD_logger(void)
{
	if (sdCard.counter < 9999)
		sdCard.counter++;
	else
		sdCard.counter = 0;

	sdCard.blen = sprintf(sdCard.buffer,
			"\n"
			);

	for (int i = 0; i < sdCard.blen; i++)
		sdCard.longBuffer[i+sdCard.blenLong] = sdCard.buffer[i];
	sdCard.longCounter++;
	sdCard.blenLong += sdCard.blen;

	if (sdCard.longCounter >= SD_BUFFSIZE_LONG)
	{
		fresult = SD_write(sdCard.blenLong, sdCard.longBuffer);
		sdCard.longCounter = 0;
		sdCard.blenLong = 0;
	}

	//LDEBUG;

	return fresult;
}
