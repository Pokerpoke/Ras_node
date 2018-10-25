/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    摄像头捕获类
 * @version  0.0.1
 * 
 * Last Modified:  2018-01-19
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example  qa_cam_capture.cc
 * 
 */
#ifndef _CAM_CAPTURE_H_
#define _CAM_CAPTURE_H_

#include <string>
#include <functional>
#include <linux/videodev2.h>
#include <sys/time.h>

namespace an
{
namespace media
{
/** 
 * @brief   摄像头捕获类
 * 
 * 传入数据处理函数来使用Memory Map指针，如不传入处理函数会将图像数据复制到
 * output_buffer中 
 * 
 * @warning 可能存在内存泄漏
 * @todo    修复可能的内存泄漏
 */
class CamCapture
{
  public:
    /** 
     * @brief   构造函数
     * 
     * @param[in]   dev 设备名称，例如"/dev/video0"
     * 
     */
    CamCapture(const std::string &dev);
    /** 
     * @brief   析构函数
     * 
     */
    ~CamCapture();
    /** 
     * @brief   捕获函数
     * 
     * output_buffer指向图像数据所在内存地址，output_buffer_size为地址长度
     * 
     * @param[in]   data_process    图像数据处理函数
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int capture(std::function<void(void)> data_process);
    /**
     * @brief   捕获函数
     * 
     * 将图像数据复制到output_buffer中，output_buffer指向图像数据所在内存地址
     * output_buffer_size为地址长度
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int capture();

    /// 输出缓存
    /// @see CamCapture::capture
    mutable void *output_buffer;
    /// 输出缓存大小
    /// @see CamCapture::capture
    mutable int output_buffer_size;

  protected:
  private:
    /**
     * @brief   给v4l2申请buffer用的
     * 
     */
    class buffer
    {
      public:
        /// 内存映射时的开始位置指针
        void *start;
        /// 长度
        size_t length;
    };
    /**
     * @brief   初始化函数
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int init();
    /**
     * @brief   打开设备
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int open_device();
    /**
     * @brief   查询设备信息
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int query_capabilities();
    /**
     * @brief   设置图像宽度
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int set_pic_width(const int width);
    /**
     * @brief   设置图像高度
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int set_pic_height(const int height);
    /**
     * @brief   设置图片格式
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int set_picture_format();
    /**
     * @brief   申请缓存空间
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int request_buffers();
    /**
     * @brief   查询缓存
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int query_buffer();
    /**
     * @brief   内存映射
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int memory_map();
    /**
     * @brief   内存解映射
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int memory_unmap();
    /**
     * @brief   将缓存放入输出队列
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int queue_buffer();
    /**
     * @brief   开始串流
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int stream_on();
    /**
     * @brief   关闭串流
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int stream_off();
    /**
     * @brief   设置超时
     * 
     * @param[in]   t   超时秒数
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int set_time_out(const int t);
    /**
     * @brief   设置超时2s
     * 
     * @retval  0   成功
     * @retval  -1  失败
     * 
     */
    int set_time_out();

    /// 设备名
    const char *_dev;
    /// v4l2缓存数组数组
    buffer *buffers;
    /// 文件指针
    int _fd;
    /// 缓存个数
    int _nbuffers;
    /// 用于select函数
    fd_set _fds;
    /// 超时时间结构体
    struct timeval _tv;
    /// v4l2格式
    struct v4l2_format _fmt;
    /// v4l2缓存
    struct v4l2_buffer _buf;
    /// v4l2支持能力
    struct v4l2_capability _cap;
    /// v4l2申请缓存
    struct v4l2_requestbuffers _req;

    // Flags
    /// 是否初始化
    bool INITED;
    /// 用以判断使用默认capture函数，最后是否释放
    bool MEMORY_COPY;
};
}
}

#endif // !_CAM_CAPTURE_H_