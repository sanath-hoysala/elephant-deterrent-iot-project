/*
 * audio_play.h
 *
 *  Created on: Apr 11, 2024
 *      Author: sanat
 */

#ifndef AUDIO_PLAY_H_
#define AUDIO_PLAY_H_

#include "audioI2S.h"
#include "MY_CS43L22.h"
#include "wav_player.h"

#include "main.h"
#include "fatfs.h"
#include "usb_host.h"

extern I2C_HandleTypeDef hi2c1;
extern I2S_HandleTypeDef hi2s3;
extern DMA_HandleTypeDef hdma_spi3_tx;

#define WAV_FILE1 "bees1.wav"
#define WAV_FILE2 "bees2.wav"
#define WAV_FILE3 "bees3.wav"

extern ApplicationTypeDef Appli_state;



void audio_play_init();
void audio_play(const char* );
#endif /* AUDIO_PLAY_H_ */
