# README
## 1.依赖
- [CMake](https://cmake.org/)
- [Doxygen](www.doxygen.org/)  
	Doxygen依赖Graphviz生成调用关系图
	- [Graphviz](http://www.graphviz.org/)

## 2.编译方法
[^_^]:
	@brief 编译前先阅读此文件
- 编译可执行
```shell
mkdir build
cd build
cmake ..
make
```
示例程序位于`build/bin/`目录下
- 生成API文档
```
cd build
make doc
```

## 3.TODO:
- [X] system\_info,cpu\_info
- [ ] tcp,udp clien,server
- [ ] file_transfer
- [ ] image\_enc,image\_dec
- [ ] video\_enc,video\_dec
- [ ] qtgui
- [ ] router
- [ ] cross compile
- [ ] swig