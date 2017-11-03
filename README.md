# README

[![Build Status](https://travis-ci.org/Pokerpoke/Ras_node.svg?branch=master)](https://travis-ci.org/Pokerpoke/Ras_node)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/633f642c57ff4768bac4a6deed91313d)](https://www.codacy.com/app/Pokerpoke/Ras_node?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Pokerpoke/Ras_node&amp;utm_campaign=Badge_Grade)

## 1.依赖

- 编译工具：[CMake](https://cmake.org/)

- 日志记录：[Log4cpp](http://log4cpp.sourceforge.net/)

- 文档生成：[Doxygen](www.doxygen.org/)  

	- Doxygen依赖[Graphviz](http://www.graphviz.org/)生成调用关系图
	
	```shell
	sudo apt install graphviz
	```

- 其他依赖：

	- [ALSA](https://www.alsa-project.org/main/index.php/Main_Page)
	
	```shell
	sudo apt install libasound2-dev
	```
	
	- [JRTPLIB](http://research.edm.uhasselt.be/jori/page/CS/Jrtplib.html)
	
	```shell
	git clone https://github.com/j0r1/JRTPLIB.git
	cd JRTPLIB
	mkdir build
	cd build
	cmake ..
	make
	sudo make install
	```
	
	- JRTPLIB依赖[JThread](http://research.edm.uhasselt.be/jori/page/CS/Jthread.html)
	
	```shell
	git clone https://github.com/j0r1/JThread.git
	cd JThread
	mkdir build
	cd build
	cmake ..
	make
	sudo make install
	```
	

## 2.编译

- 编译可执行程序

```shell
mkdir build
cd build
cmake ..
make
```

示例程序位于`build/bin/`目录下

- 启用Debug

```shell
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

- 交叉编译

	- Tiny4412  
	
	修改`cmake/toolschain/CMakeLists.txt`中的`TOOL_CHAIN_DIR`为相应地址
	
	```shell
	cmake -DCMAKE_BUILD_TARGET=Tiny4412 ..
	```
	
- 生成API文档

```shell
make doc
```
- 在线API参考

[Ras_node API](https://pokerpoke.github.io/Ras_node/)
