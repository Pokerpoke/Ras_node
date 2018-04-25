# Aero-Node贡献指南

前人种树，后人乘凉。

**注** ：生成目录插件问题，使用英文作为导航

- [Aero-Node贡献指南](#aero-node)
    - [C/C++](#c-c)
        - [Header](#header)
        - [File](#file)
        - [Namespace](#namespace)
        - [Class](#class)
            - [Name of Class](#name-of-class)
            - [Class Member Function](#class-member-function)
            - [Class Member Variable](#class-member-variable)
            - [Executable File](#executable-file)
            - [Unit Test](#unit-test)
        - [Others](#others)
    - [Git](#git)
        - [Commit](#commit)
        - [Release](#release)
        - [Issue](#issue)
    - [Shell Scripts](#shell-scripts)
        - [File](#file)
        - [Variable](#variable)
        - [Function](#function)
        - [Comment](#comment)
        - [Others](#others)
    - [Doxygen](#doxygen)
    - [CMake](#cmake)
    - [Markdown](#markdown)

## C/C++

### Header

- 头文件需要自洽，保证include了足够保证自身运行的头文件
- 不要在头文件中定义全局变量
- 不要在头文件中定义宏
- 不要在头文件中使用`using namespace std`等语句，以免引起冲突

### File

- 命名格式为小写字母加下划线，例如`qa_example.cc`, `example.h`
- 例程统一以`qa_`(Quality Assurance)开头，并在文件名中表明功能
- 文件头部添加以下申明，如下所示(@开头的为生成doxygen文档所需参数)

```c++
/**
 *
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 *
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief
 * @version  0.0.1
 *
 * Last Modified:  2018-01-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 *
 */
```

### Namespace

- 所有类、函数请放到`an`(aero node)命名空间下，并在`an`命名空间下进行分类

### Class

#### Name of Class

- 类名格式为单词首字母大写且无空格，例如`VoiceCapture`

#### Class Member Function

- 成员函数命名格式为小写字母加下划线，例如`open_device()`
- 如果成员函数不会对传入参数进行修改，推荐添加`const`修饰符，例如`open_device(const std::string &dev)`
- *[待定]* 目前使用`#ifdef ENABLE_DEBUG`来控制debug或者release(使用`#ifdef DEBUG`时会与log4cpp库产生冲突)

#### Class Member Variable

- 尽量少的暴露共有变量以防被无意中修改
- 不希望被更改的成员变量使用`const`或者`mutable`进行修饰
- 私有成员变量以下划线开头或结尾，例如`_some_variable`或者`some_variable_`

#### Executable File

- 未经过测试通过的可执行文件和例程以小写字母加`_`组成，例如`qa_send_file`
- 经过测试通过的可执行文件由小写字母加`-`组成，例如`send-file`，并放入顶层目录`/bin`目录下

#### Unit Test

### Others

- 不要使用记事本对程序文件进行编辑，记事本会引入一些不必要的字符
- 除界面外尽量不要引入Qt相关的函数
- 尝试使用C++的特性，如static_cast代替强制类型转换、functional代替函数指针等
- 尝试使用C++11的新特性(在树莓派上运行尝试使用C++14的新特性)，如lambda函数、右值引用、线程库、简单的范围迭代等
- 代码的列数尽量不要超过80列，这样在编辑器中浏览时不需要左右翻页的动作
- 一个函数尽可能短，长度尽量不要超过一个屏幕，如果函数过长可以考虑分为多个小函数
- 代码缩进尽量以空格缩进，以便在不同编辑器中获得相同的显示
- 每个类需要添加相关`qa_`开头的例程，用以说明每个类的不同功能

## Git

### Commit

- Commits首行以一句话简述(140字符以内)，句首字母大写，不需要句号。另起一行写标识符，写明做出的修改

| 标识     | 作用                       |
| -------- | -------------------------- |
| Feat     | 功能的增减                 |
| Fix      | Bug的修补                  |
| Docs     | 文档                       |
| Style    | 格式，不影响代码运行的变动 |
| Refactor | 重构                       |
| Test     | 测试的增减                 |
| Chore    | 构建过程或者辅助工具的变动 |
| Other    | 其他变动                   |

例如

```markdown
Use callback for server and receiver
Feat:
- add voice-all
- add callback method for server and receiver
- add override method for server and receiver
- add thread in CMake
Style:
- update header of some files
Docs:
- remove *.cc files from doxygen
Refactor:
- rewrite UDP TCP and SystemInfo
Other:
- move voice-receive and voice-send to example
```

### Release

- 关于版本

| 级别     | 说明                         |
| -------- | ---------------------------- |
| 主版本号 | 当你做了不兼容的 API 修改    |
| 次版本号 | 当你做了向下兼容的功能性新增 |
| 修订号   | 当你做了向下兼容的问题修正   |

- 进行了重大功能性的修改并测试通过时可以发布Release版本
- 版本发布后为可读属性，即需要修复bug时请发布新版本
- 发布版本时请确保能够在全新的环境下编译、测试通过

### Issue

## Shell Scripts

### File

- 未经过多次测试的脚本使用`_`作为连字符，例如`some_test.sh`
- 确保没有问题的脚本可以使用`-`作为连字符，并不加`sh`后缀，例如`an-run`
- 在Ubuntu中运行的文件头部使用`#!/bin/bash`指定shell，在Tiny4412上运行的文件头部使用`#!/bin/sh`指定shell

### Variable

- 使用`SHELL_SCRIPT_DIR=$(dirname $(readlink -f $0))`来获取脚本文件所在目录
- 除变量名诸如`$1,$a`等只有一个数字、字母或符号的变量外，请尽量使用`{}`将变量包围，例如`${example_variable}`

### Function

### Comment

- 尽量提供详细的注释

### Others

- 尽量保证从不同目录运行脚本都能获得相同的效果，可以使用[变量](#variable)中提供的命令来获取脚本文件所在目录

## Doxygen

- `@param[in]`和`@param[out]`来指明输入输出参数
- 如果有多个返回值，使用`@retval`来指明返回值的意义

## CMake

- 尽可能使用变量或者宏定义来控制不同的目标平台和编译模式

## Markdown

- 请使用Markdown文件作为项目的说明文件