# README

[![Build Status](https://travis-ci.com/Pokerpoke/Ras_node.svg?token=bwwRBmFu8PYsDXRZk1iU&branch=master)](https://travis-ci.com/Pokerpoke/Ras_node)

## 1.依赖

- 编译工具：[CMake](https://cmake.org/)

- 日志记录：[Log4cpp](http://log4cpp.sourceforge.net/)

- 文档生成：[Doxygen](www.doxygen.org/)

    - Doxygen依赖[Graphviz](http://www.graphviz.org/)生成类关系图

    ```shell
    sudo apt install graphviz
    ```

- 其他依赖：

    - [ALSA](https://www.alsa-project.org/main/index.php/Main_Page)

    ```shell
    sudo apt install libasound2-dev
    ```

    - [JRTPLIB](http://research.edm.uhasselt.be/jori/page/CS/Jrtplib.html)

    - JRTPLIB依赖[JThread](http://research.edm.uhasselt.be/jori/page/CS/Jthread.html)

- 编码

    - [BCG729](https://github.com/BelledonneCommunications/bcg729)

## 2.编译

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

- API

[Ras_node API](https://pokerpoke.github.io/Ras_node/)
