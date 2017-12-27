/*******************************************************************************
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-26
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
#include <bcg729/encoder.h>
#include <bcg729/decoder.h>
#ifdef __cplusplus
}
#endif

#include <stdio.h>

#include "logger.h"
#include "voice_capture.h"
#include "voice_playback.h"

using namespace an::core;
using namespace std;

void enc();

int main()
{
	logger_init();
	VoiceCapture c("default");
	VoicePlayback p("default");

	bcg729EncoderChannelContextStruct *encoderChannelContext;
	encoderChannelContext = initBcg729EncoderChannel(0);

	bcg729DecoderChannelContextStruct *decoderChannelContext;
	decoderChannelContext = initBcg729DecoderChannel();

	int16_t input_buffer[80];
	uint8_t output_buffer[10];
	int16_t output_buffer2[80];
	uint8_t output_buffer_size;

	LOG(INFO) << sizeof(int);

	// while (1)
	for (size_t i = 0; i < 10; i++)
	{

		c.capture();
		char *temp;
		temp = (char *)malloc(c.output_buffer_size);
		memcpy(temp, c.output_buffer, c.output_buffer_size);
		// memset(temp, 3, 80);

		bcg729Encoder(encoderChannelContext,
					  (int16_t *)temp,
					  output_buffer,
					  &output_buffer_size);

		printf("temp\n");
		for (size_t i = 0; i < 80; i++)
		{
			printf("%hd ", temp[i]);
		}
		printf("\n");

		printf("output_buffer\n");
		for (size_t i = 0; i < 10; i++)
		{
			printf("%hd ", output_buffer[i]);
		}
		printf("\n");

		bcg729Decoder(decoderChannelContext, output_buffer, 10, 1, 0, 0, output_buffer2);

		printf("output_buffer2\n");
		for (size_t i = 0; i < 128; i++)
		{
			printf("%d ", output_buffer2[i]);
		}
		printf("\n");
		// p.playback((char *)output_buffer2, sizeof(output_buffer2));
	}

	getchar();
	closeBcg729EncoderChannel(encoderChannelContext);
	closeBcg729DecoderChannel(decoderChannelContext);
	return 0;
}