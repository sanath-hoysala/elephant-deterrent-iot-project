#include"audio_play.h"

bool isSdCardMounted;
bool pauseResumeToggle;

void audio_play_init()
{
	CS43_Init(hi2c1, MODE_I2S);
	CS43_SetVolume(220);//0-255
	CS43_Enable_RightLeft(CS43_RIGHT_LEFT);

	audioI2S_setHandle(&hi2s3);

	isSdCardMounted = 0;
	pauseResumeToggle = 0;
}


void audio_play(const char* wav_file)
{
		if(Appli_state == APPLICATION_START)
		{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		}
		else if(Appli_state == APPLICATION_DISCONNECT)
		{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		  f_mount(NULL, (TCHAR const*)"", 0);
		  isSdCardMounted = 0;
		}

		if(Appli_state == APPLICATION_READY)
		{
		  if(!isSdCardMounted)
		  {
			f_mount(&USBHFatFS, (const TCHAR*)USBHPath, 0);
			isSdCardMounted = 1;
		  }
		  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
		  {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
			HAL_Delay(500);
			wavPlayer_fileSelect(wav_file);
			wavPlayer_play();

			while(!wavPlayer_isFinished())
			{
			  wavPlayer_process();
			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
			  {
				pauseResumeToggle^=1;
				if(pauseResumeToggle)
				{
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
				  wavPlayer_pause();
				  HAL_Delay(200);
				}
				else
				{
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
				  HAL_Delay(1000);
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
				  {
					wavPlayer_stop();
				  }
				  {
					wavPlayer_resume();
				  }
				}
			  }
			}
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_Delay(1000);

		  }
		}
}
