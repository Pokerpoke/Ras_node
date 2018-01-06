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
 * Last Modified:  2018-01-05
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

#include "logger.h"
#include "voice_capture.h"
#include "voice_playback.h"

using namespace an::core;
using namespace std;

int main()
{
	logger_init();
	VoiceCapture c("default");
	VoicePlayback p("default");

	bcg729EncoderChannelContextStruct *encoderChannelContext;
	encoderChannelContext = initBcg729EncoderChannel(0);

	bcg729DecoderChannelContextStruct *decoderChannelContext;
	decoderChannelContext = initBcg729DecoderChannel();

	uint8_t output_buffer[10];
	int16_t output_buffer2[80];
	uint8_t output_buffer_size;

	while (1)
	{
		c.capture();

		bcg729Encoder(encoderChannelContext,
					  (int16_t *)c.output_buffer,
					  output_buffer,
					  &output_buffer_size);

		bcg729Decoder(decoderChannelContext,
					  output_buffer, 10, 0, 0, 0,
					  output_buffer2);

		p.playback((char *)output_buffer2, 80 * sizeof(int16_t));
	}

	getchar();
	closeBcg729EncoderChannel(encoderChannelContext);
	closeBcg729DecoderChannel(decoderChannelContext);
	return 0;
}