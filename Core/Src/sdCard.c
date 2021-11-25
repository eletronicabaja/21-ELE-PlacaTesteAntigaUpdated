/*

 */

#include "sdCard.h"

#include "rot.h"
#include "forceGauge.h"

/*
 * 	Função para calcular tamanho de um buffer
 */
int bufsize(char *buf)
{
	int i = 0;
	while (*buf++ != '\0')
		i++;
	return i;
}

/*
 * 	Função para limpar um buffer
 */
void bufclear(char *buf)
{
	for (int i=0; i<bufsize(buf); i++)
		buf->buffer[i] = '\0';
}

/*
 * 	Inicialização do cartão sd
 */
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

	bufclear(sdCard.buffer);

	LDEBUG;
	sdCard.longCounter = 0;
	sdCard.blen = 0;
	sdCard.blenLong = 0;
	sdCard.counter = 0;
	sdCard.timer = 0;

	HAL_TIM_Base_Start_IT(&htim4);

	return fresult;
}

/*
 * 	Função para ler o settings.ini
 */
FRESULT SD_loadSettings(void)
{
	sprintf(sdCard.filname,"settings.ini");
	fresult = f_open(&sdCard.fil, sdCard.filname, FA_OPEN_EXISTING | FA_READ);

	if (fresult == FR_NO_FILE)
	{
		fresult = SD_createSettings();
	}
	else if (fresult == FR_OK)
	{
		fresult = SD_searchSettings();
	}

	return fresult;
}

/*
 * 	Função para criar o settings.ini quando não disponivel
 */
FRESULT SD_createSettings(void)
{
	int len;

	fresult = f_close(&sdCard.fil);

	fresult = f_open(&sdCard.fil, sdCard.filname, FA_OPEN_ALWAYS | FA_WRITE);
	if (fresult != FR_OK)
		return fresult;

	len = sprintf(sdCard.longBuffer,
			";Seleciona o Modo de operação da Placa\n"
			"MODE=0\n");

	fresult = f_write(&sdCard.fil, sdCard.longBuffer, len, &sdCard.bw);
	if (fresult != FR_OK)
		return fresult;

	fresult = f_close(&sdCard.fil);
	if (fresult != FR_OK)
		return fresult;

	sdCard.mode = 0;

	return fresult;
}

/*
 * 	Função que lê o conteudo do settings.ini
 */
FRESULT SD_searchSettings(void)
{
	int index = 0;
	int deindex = 1;

	fresult = f_read(&sdCard.fil, sdCard.longBuffer, SD_BUFFSIZE_LONG*SD_BUFFSIZE-1, &sdCard.br);
	if (fresult != FR_OK)
		return fresult;

	for (index; sdCard.longBuffer[index] != '='; index++);

	if (index >= SD_BUFFSIZE_LONG*SD_BUFFSIZE-2)
	{
		fresult = SD_createSettings();
		return fresult;
	}

	for (deindex; sdCard.longBuffer[index-deindex] >= 65 && sdCard.longBuffer[index-deindex] <= 90; deindex++);
	deindex--;

	for (int i = 0; i < deindex+2; i++)
	{
		sdCard.setting[i] = sdCard.longBuffer[index - deindex + i];
	}

	if (sdCard.setting[0] == 'M' && sdCard.setting[1] == 'O' && sdCard.setting[2] == 'D' && sdCard.setting[3] == 'E')
	{
		if (sdCard.setting[5] >= 48 && sdCard.setting[5] <= 57)
			sdCard.mode = sdCard.setting[5] - 48;
		else
			fresult = SD_createSettings();
	}
	else
		fresult = SD_createSettings();

	return fresult;
}

/*
 * 	Função que cria o fileXXX.txt
 */
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

/*
 * 	Função que escreve em um arquivo
 */
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

/*
 * 	Função de datalogger
 */
FRESULT SD_logger(void)
{
	if (sdCard.counter < 9999)
		sdCard.counter++;
	else
		sdCard.counter = 0;

	switch (sdCard.mode)
	{
	case 0:
			sdCard.blen = sprintf(sdCard.buffer,
					"\n"
					);
	case 1:
			sdCard.blen = sprintf(sdCard.buffer,
					"%04d%04d"
					"%04d"
					"\n",
					rot.value, forceGauge.force,
					sdCard.counter);
	}

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
