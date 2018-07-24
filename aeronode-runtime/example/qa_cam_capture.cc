/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    摄像头捕获例程
 * @version  0.0.1
 * 
 * Last Modified:  2018-04-24
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aeronode/cam_capture.h"
#include "aeronode/logger.h"

using namespace an::core;

int main()
{
    logger_init();

    FILE *fp;
    CamCapture c("/dev/video0");
    c.capture();

    fp = fopen("test_lambda.jpg", "wb+");
    c.capture([&] {
        fwrite(c.output_buffer, c.output_buffer_size, 1, fp);
    });
    fclose(fp);

    fp = fopen("test_copy.jpg", "wb+");
    c.capture();
    fwrite(c.output_buffer, c.output_buffer_size, 1, fp);
    fclose(fp);

    // fp = fopen("test_lambda_stream.jpg", "wb");
    // c.capture();
    // while (1)
    // {
    //     c.capture([&] {
    //         fseek(fp, 0, SEEK_SET);
    //         fwrite(c.output_buffer, c.output_buffer_size, 1, fp);
    //     });
    // };
    // fclose(fp);

    fp = fopen("test_copy_stream.jpg", "wb");
    c.capture();
    while (1)
    {
        c.capture();
        fseek(fp, 0, SEEK_SET);
        fwrite(c.output_buffer, c.output_buffer_size, 1, fp);
    };
    fclose(fp);

    return 0;
}