/**
 * 
 * Copyright (c) 2018 NUAA AeroLab
 * 
 * @file
 * @author   Jiang Yang (pokerpoke@qq.com)
 * @date     2018-10
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-23
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include <cmath>
#include "aeronode/logger.h"
#include "aeronode/an-media/voice_base.h"
#include "aeronode/an-media/bandpass_filter.h"

#define FILTERSWEEP_LFO_CENTER 2000.
#define FILTERSWEEP_LFO_DEPTH 1800
#define FILTERSWEEP_LFO_FREQ 0.2
#define FILTER_BANDWIDTH 50

namespace an
{
namespace media
{
BandpassFilter::BandpassFilter()
{
    voice_base = new VoiceBase();
    fs = (float)voice_base->rate;
    channels = voice_base->channels;
    BW = FILTER_BANDWIDTH;
    lfo = 0;
    dlfo = 2. * M_PI * FILTERSWEEP_LFO_FREQ / fs;

    x[0] = (float *)malloc(channels * sizeof(float));
    x[1] = (float *)malloc(channels * sizeof(float));
    x[2] = (float *)malloc(channels * sizeof(float));
    y[0] = (float *)malloc(channels * sizeof(float));
    y[1] = (float *)malloc(channels * sizeof(float));
    y[2] = (float *)malloc(channels * sizeof(float));
}

void BandpassFilter::filter(char *buffer, int r)
{
    short *samples = (short *)buffer;
    for (int i = 0; i < r; i++)
    {
        int chn;
        fc = sin(lfo) * FILTERSWEEP_LFO_DEPTH + FILTERSWEEP_LFO_CENTER;
        lfo += dlfo;
        if (lfo > 2. * M_PI)
            lfo -= 2. * M_PI;
        C = 1. / tan(M_PI * BW / fs);
        D = 2. * cos(2 * M_PI * fc / fs);
        a0 = 1. / (1. + C);
        a1 = 0;
        a2 = -a0;
        b1 = -C * D * a0;
        b2 = (C - 1) * a0;
        for (chn = 0; chn < channels; chn++)
        {
            x[chn][2] = x[chn][1];
            x[chn][1] = x[chn][0];
            y[chn][2] = y[chn][1];
            y[chn][1] = y[chn][0];
            x[chn][0] = samples[i * channels + chn];
            y[chn][0] = a0 * x[chn][0] + a1 * x[chn][1] + a2 * x[chn][2] - b1 * y[chn][1] - b2 * y[chn][2];
            samples[i * channels + chn] = y[chn][0];
        }
    }
}
BandpassFilter::~BandpassFilter()
{
    delete voice_base;
}
} // namespace media
} // namespace an