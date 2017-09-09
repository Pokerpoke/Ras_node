# README
## 1.依赖
- 编译工具：[CMake](https://cmake.org/)
- 日志记录：[log4cpp](http://log4cpp.sourceforge.net/)
- 文档生成：[Doxygen](www.doxygen.org/)  
	Doxygen依赖Graphviz生成调用关系图
	- [Graphviz](http://www.graphviz.org/)

- 其他依赖：
	- ALSA：`sudo apt install libasound2-dev`

## 2.编译方法
- 编译可执行
```shell
mkdir build
cd build
cmake ..
make
```
示例程序位于`build/bin/`目录下
- 生成API文档
```shell
cd build
make doc
```

## 3.TODO:
- [X] ~~*system\_info,cpu\_info*~~
- [X] ~~*tcp,udp client,server*~~
- [ ] thread pool
- [X] ~~*file_transfer*~~
	- [ ] Cannot transfer large file. Maybe fix later.
- [X] ~~*capture_image*~~
- [ ] video\_enc,video\_dec
- [ ] qtgui
- [ ] router
- [ ] cross compile
- [ ] swig
