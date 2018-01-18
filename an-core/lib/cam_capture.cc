/*******************************************************************************
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    摄像头捕获类
 * @version  0.0.1
 * 
 * Last Modified:  2018-01-18
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 ******************************************************************************/
#include <unistd.h>
#include <string.h>
#include <string>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "logger.h"
#include "cam_capture.h"

namespace an
{
namespace core
{
CamCapture::CamCapture(const std::string &dev)
    : _dev(dev.c_str())
{
    // 初始化相关结构体
    memset(&_cap, 0, sizeof(_cap));
    memset(&_fmt, 0, sizeof(_fmt));
    memset(&_req, 0, sizeof(_req));
    memset(&_buf, 0, sizeof(_buf));
    memset(&_tv, 0, sizeof(_tv));

    _fd = 0;
    _nbuffers = 4;

    buffers = new buffer[_nbuffers];

    // 超时初始化
    FD_ZERO(&_fds);
    FD_SET(_fd, &_fds);

    INITED = false;
}

/** 
 * @brief   初始化相机
 * 
 */
int CamCapture::init()
{
    INITED = false;

    if (open_device() < 0 ||
        query_capabilities() < 0 ||
        set_picture_format() < 0 ||
        request_buffers() < 0 ||
        query_buffer() < 0 ||
        memory_map() < 0 ||
        queue_buffer() < 0 ||
        stream_on() < 0 ||
        set_time_out() < 0)
        return -1;

    INITED = true;

    return 0;
}

/** 
 * @brief   打开摄像头
 * 
 * @retval  0	成功
 * @retval  -1	打开设备失败
 * 
 */
int CamCapture::open_device()
{
    if ((_fd = open(_dev, O_RDWR)) < 0)
    {
        LOG(ERROR) << "Open device failed.";
        return -1;
    }
    LOG(INFO) << "Open device success.";
    return 0;
}

/** 
 * @brief   查询设备信息
 * 
 * @retval	0	成功
 * @retval	-1	查询失败
 * 
 */
int CamCapture::query_capabilities()
{
    if (ioctl(_fd, VIDIOC_QUERYCAP, &_cap) < 0)
    {
        LOG(ERROR) << "Query capabilities failed.";
        return -1;
    }
    LOG(INFO) << "Query capabilities success.\n\t"
              << "Driver:       " << _cap.driver << "\n\t"
              << "Card:         " << _cap.card << "\n\t"
              << "Bus info:     " << _cap.bus_info << "\n\t"
              << "Version:      " << (_cap.version >> 16 & 0xFF)
              << "." << (_cap.version >> 8 & 0xFF)
              << "." << (_cap.version & 0xFF);
    //   << "." << (_cap.version & 0xFF) << "\n\t";
    //   << "Capabilities: " << _cap.capabilities;
    return 0;
}

/** 
 * @brief   设置抓取图片格式
 * 
 * @retval	0	成功
 * @retval	-1	设置格式失败
 * 
 */
int CamCapture::set_picture_format()
{
    _fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    _fmt.fmt.pix.field = V4L2_FIELD_NONE;
    _fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;

    set_pic_width(600);
    set_pic_height(480);

    if (ioctl(_fd, VIDIOC_S_FMT, &_fmt) < 0)
    {
        LOG(ERROR) << "Set pixel format failed.";
        return -1;
    }
    LOG(INFO) << "Set pixel format success.";
    return 0;
}

/** 
 * @brief   设置图片宽度
 * 
 * @param[in]   width   宽度
 * @retval  0   成功
 */
int CamCapture::set_pic_width(const int width)
{
    _fmt.fmt.pix.width = width;
    return 0;
}

/** 
 * @brief   设置图片高度
 * 
 * @param[in]   height  高度
 * @retval  0   成功
 * 
 */
int CamCapture::set_pic_height(const int height)
{
    _fmt.fmt.pix.height = height;
    return 0;
}

/** 
 * @brief   申请缓存空间
 * 
 * @retval	0	成功
 * @retval	-1	请求失败
 * @note	内存映射模式
 * 
 */
int CamCapture::request_buffers()
{
    _req.count = _nbuffers;
    _req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    _req.memory = V4L2_MEMORY_MMAP;

    if (ioctl(_fd, VIDIOC_REQBUFS, &_req) < 0)
    {
        LOG(ERROR) << "Request buffer failed.";
        return -1;
    }
    LOG(INFO) << "Request buffer success.";
    return 0;
}

/** 
 * @brief   查询缓存
 * 
 */
int CamCapture::query_buffer()
{
    _buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    _buf.memory = V4L2_MEMORY_MMAP;
    for (unsigned int i = 0; i < _req.count; i++)
    {
        _buf.index = i;
        if (ioctl(_fd, VIDIOC_QUERYBUF, &_buf) < 0)
        {
            LOG(ERROR) << "Query buffer failed.";
            return -1;
        }
    }
    LOG(INFO) << "Query buffer success.";
    return 0;
}

int CamCapture::memory_map()
{
    for (unsigned int i = 0; i < _req.count; i++)
    {
        _buf.index = i;
        buffers[i].length = _buf.length;
        buffers[i].start = mmap(NULL,                   // 映射区开始地址
                                _buf.length,            // 映射区长度
                                PROT_READ | PROT_WRITE, // 期望的内存保护模式
                                                        // PROT_EXEC、PROT_READ、PROT_WRITE、PROT_NONE
                                MAP_SHARED,             // 映射对象类型
                                _fd,                    // 有效的文件描述符
                                _buf.m.offset);
        if (buffers[i].start == MAP_FAILED)
        {
            LOG(ERROR) << "Memory map failed.";
            return -1;
        }
    }
    LOG(INFO) << "Memory map success.";
    return 0;
}

int CamCapture::memory_unmap()
{
    for (int i = 0; i < _nbuffers; i++)
    {
        if (munmap(buffers[i].start, _buf.length) < 0)
        {
            LOG(ERROR) << "Memory unmap failed.";
            return -1;
        }
    }
    LOG(INFO) << "Memory unmap success.";
    return 0;
}

/** 
 * @brief   缓存队列
 * 
 */
int CamCapture::queue_buffer()
{
    if (ioctl(_fd, VIDIOC_QBUF, &_buf) < 0)
    {
        LOG(ERROR) << "Queue buffer failed.";
        return -1;
    }
    LOG(INFO) << "Queue buffer success.";
    return 0;
}

/**	
 * @brief   打开串流
 * 
 */
int CamCapture::stream_on()
{
    if (ioctl(_fd, VIDIOC_STREAMON, &_buf.type) < 0)
    {
        LOG(ERROR) << "Start capture failed.";
        return -1;
    }
    LOG(INFO) << "Start capture...";
    return 0;
}

/**	
 * @brief   关闭串流
 * 
 */
int CamCapture::stream_off()
{
    if (ioctl(_fd, VIDIOC_STREAMOFF, &_buf.type) < 0)
    {
        LOG(ERROR) << "Stop capture failed.";
        return -1;
    }
    LOG(INFO) << "Stop capture...";
    return 0;
}

int CamCapture::set_time_out()
{
    return set_time_out(2);
}

/** 
 * @brief   设置访问设备超时
 * 
 */
int CamCapture::set_time_out(const int t)
{
    _tv.tv_sec = t;
    _tv.tv_usec = 0;
    if (select(_fd + 1, &_fds, NULL, NULL, &_tv) < 0)
    {
        LOG(ERROR) << "Camera time out.";
        return -1;
    }
    LOG(INFO) << "Set time out success.";
    return 0;
}

void CamCapture::_data_process()
{
    output_buffer = nullptr;
    output_buffer = malloc(output_buffer_size);
    memcpy(output_buffer, buffers[_buf.index].start, output_buffer_size);
};

/**	
 * @brief   捕获函数
 * 
 */
int CamCapture::capture(std::function<void(void)> data_process)
{
    if (!INITED)
        init();
    if (ioctl(_fd, VIDIOC_DQBUF, &_buf) < 0)
    {
        LOG(ERROR) << "Read frame failed.";
        return -1;
    }
    output_buffer = buffers[_buf.index].start;
    output_buffer_size = buffers[_buf.index].length;
    data_process();
#ifdef ENABLE_DEBUG
    LOG(INFO) << "Read frame success.";
#endif
    queue_buffer();
    return output_buffer_size;
}

int CamCapture::capture()
{
    return capture([&] {
        _data_process();
    });
}
CamCapture::~CamCapture()
{
    stream_off();
    memory_unmap();
    delete[] buffers;
    close(_fd);
}
}
}