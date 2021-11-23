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
	int len;
	fresult = f_mount(&sdCard.fs, "", 0);
	if (fresult != FR_OK)
		return fresult;

	fresult = SD_createFile();
	if (fresult != FR_OK)
		return fresult;

	len = sprintf(sdCard.buffer,"9999999999999999999999\n");
	fresult = f_write(&sdCard.fil, sdCard.buffer, len, &sdCard.bw);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_close(&sdCard.fil);
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

FRESULT SD_createFile(void)
{
	int filnum = 0;

	do
	{
		sprintf(sdCard.filname,"file%.3d.txt",filnum);
		fresult = f_open(&sdCard.fil, sdCard.filname, FA_CREATE_NEW | FA_WRITE);
		filnum++;
		LDEBUG;
	}while(fresult == FR_EXIST);

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
			"%04d%04d"
			"%04d%04d"
			"%06d"
			"\r\n",
			can_rData.rpm, can_rData.vel,
			can_rData.fuel,can_rData.bateria,
			can_rData.counter);

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
