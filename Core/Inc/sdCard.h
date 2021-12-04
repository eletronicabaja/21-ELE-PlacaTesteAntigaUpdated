/*
 * sdCard.h
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

/*
	==HEADER PARA APLICAÇÃO DO SD (Módulo Antigo)==

	Arquivos que acompanham:
	-sdCard.c

	INSTRUÇÕES:

	-Inicializar na main.c:

		SD_Init(void);

	-Chamar para salvar os dados:

		SD_logger(void);

 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include "main.h"
#include "fatfs_sd.h"
#include "fatfs.h"
#include "string.h"
#include "stdio.h"

/*
 * 	MACROS QUE DEFINEM O TAMANHO DO BUFFER
 */
#define SD_BUFFSIZE	48
#define SD_BUFFSIZE_LONG 10

/*
 * 	Cria Handler do SDCard
 */
typedef struct
{
	FATFS fs;										/* < ID do Hardware do cartão SD */
	FIL fil;										/* < ID do arquivo que está sendo manipulado */
	int blen;										/* < Quantidade de chars que são salvos no buffer */
	int blenLong;									/* < Quantidade de chars que são salvos no longBuffer */
	char buffer[SD_BUFFSIZE];						/* < buffer para os dados */
	char longBuffer[(SD_BUFFSIZE_LONG*SD_BUFFSIZE)];/* < Buffer grande que opera diretamente o arquivo */
	char filname[16];								/* < String que salva o nome do arquivo sendo operado */
	uint16_t counter;								/* < Contador, conta o numero de salvamentos no buffer */
	uint16_t timer;									/* < Timer para salvar o tempo em segundos, usado como variavel de controle para calcular a frequencia */
	BYTE longCounter;								/* < Variavel de controle, faz contagem de quantos buffers foram salvos dentro do longBuffer */
	UINT br, bw;									/* < Variaveis de controle de escrita e leitura */
	char setting[16];								/* < Variavel que salva as configuração lidas no settings.ini */
	uint16_t mode;									/* < Variavel que salva o modo de operação da placa configurado no settings.ini */
}SD_CARD_typedef;

TIM_HandleTypeDef htim4;

FRESULT fresult;			/* < Variavel de debug */
SD_CARD_typedef sdCard;		/* < Declara variavel do sdCard */

int bufsize(char *buf);
void bufclear(SD_CARD_typedef *buf);

FRESULT SD_Init(void);
FRESULT SD_createSettings(void);
FRESULT SD_searchSettings(void);
FRESULT SD_loadSettings(void);
FRESULT SD_createFile(void);
FRESULT SD_write(int bsize, char wBuf[bsize]);
FRESULT SD_logger(void);

#endif /* INC_SDCARD_H_ */
