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
#ifndef _BANDPASS_FILTER_H_
#define _BANDPASS_FILTER_H_

namespace an
{
namespace media
{
class BandpassFilter
{
  public:
    BandpassFilter();
    ~BandpassFilter();
    void filter(char *buffer, int r);

  private:
    /* filter the sweep variables */
    float lfo, dlfo, fs, fc, BW, C, D, a0, a1, a2, b1, b2, *x[3], *y[3];
    int channels;
    VoiceBase *voice_base;
};
} // namespace media
} // namespace an

#endif // !_BANDPASS_FILTER_H_