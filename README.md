# README

[![pipeline status](http://192.168.0.9:8086/git/Pokerpoke/aero-node/badges/master/pipeline.svg)](http://192.168.0.9:8086/git/Pokerpoke/aero-node/commits/master)

## 依赖

- 编译工具：[CMake](https://cmake.org/)

- 日志记录：[Log4cpp](http://log4cpp.sourceforge.net/)

- 文档生成：[Doxygen](www.doxygen.org/)

- 其他依赖：

  - Doxygen依赖[Graphviz](http://www.graphviz.org/)生成类关系图

  - [ALSA](https://www.alsa-project.org/main/index.php/Main_Page)

  - [bcg729](https://github.com/BelledonneCommunications/bcg729)

  - [JRTPLIB](http://research.edm.uhasselt.be/jori/page/CS/Jrtplib.html)

  - JRTPLIB依赖[JThread](http://research.edm.uhasselt.be/jori/page/CS/Jthread.html)

- 编码

  - [BCG729](https://github.com/BelledonneCommunications/bcg729)

### 安装依赖

```shell
sudo apt-get install -y cmake libasound2-dev doxygen graphviz liblog4cpp5-dev
```

Tiny4412交叉编译环境，请在实验室局域网环境下执行`scripts/set-up-environment.sh`

## 编译

```shell
mkdir build
cd build
cmake ..
make
# collect binaries and libraries
make install
# @TODO uncomment this line when complete
# sudo make install
```

示例程序位于`example`目录下

- 启用Debug

  ```shell
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  ```

- 交叉编译

  - Tiny4412

    *可选* 修改`cmake/toolschain/CMakeLists.txt`中的`TOOL_CHAIN_DIR`为相应地址

    ```shell
    cmake -DCMAKE_BUILD_TARGET=Tiny4412 -DCMAKE_BUILD_TYPE=Debug ..
    ```

  - RPi

    @TODO

- 生成API文档

  ```shell
  make doc
  ```

- API

  [aero-node API](https://pokerpoke.github.io/Ras_node/)

## 树莓派

树莓派镜像初始化工具位于`scripts/RPi`目录下