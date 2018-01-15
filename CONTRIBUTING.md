# Aero-Node贡献指南

- [Aero-Node贡献指南](#aero-node%E8%B4%A1%E7%8C%AE%E6%8C%87%E5%8D%97)
    - [C/C++](#cc)
        - [文件](#%E6%96%87%E4%BB%B6)
        - [命名空间](#%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4)
        - [类](#%E7%B1%BB)
            - [类名](#%E7%B1%BB%E5%90%8D)
            - [类成员函数](#%E7%B1%BB%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
            - [类成员变量](#%E7%B1%BB%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F)
            - [可执行文件](#%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6)
            - [单元测试](#%E5%8D%95%E5%85%83%E6%B5%8B%E8%AF%95)
            - [其他](#%E5%85%B6%E4%BB%96)
    - [Git](#git)
        - [Commit](#commit)
        - [Release](#release)
        - [Issue](#issue)
    - [Shell Scripts](#shell-scripts)
        - [变量](#%E5%8F%98%E9%87%8F)
        - [函数](#%E5%87%BD%E6%95%B0)
        - [注释](#%E6%B3%A8%E9%87%8A)
    - [Doxygen](#doxygen)
    - [CMake](#cmake)
    - [Markdown](#markdown)

## C/C++

### 文件

- 命名格式为小写字母加下划线，例如`qa_example.cc, example.h`
- 例程统一以`qa_`(Quality Assurance)开头，并在文件名中表明功能
- 文件头部添加以下申明，如下所示(@开头的为生成doxygen文档所需参数)

```c++
/*******************************************************************************
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
 ******************************************************************************/
```

### 命名空间

- 所有类、函数请放到`an`(aero node)命名空间下，并在`an`命名空间下进行分类
- 不要再任何可以被`#include "foo.h"`的头文件下使用`using namespace std`等可能引入命名空间的语句

### 类

#### 类名

- 类名格式为单词首字母大写且无空格，例如`VoiceCapture`
- 尽量少的暴露共有变量以防被无意中修改

#### 类成员函数

- 成员函数命名格式为小写字母加下划线，例如`open_device()`
- 如果成员函数不会对传入参数进行修改，推荐添加`const`修饰符，例如`open_device(const std::string &dev)`

#### 类成员变量

- 私有成员变量以下划线开头，例如`_some_variable`

#### 可执行文件

- 经过测试通过的可执行文件由小写字母加`-`组成，例如`send-file`

#### 单元测试

#### 其他

- 不要使用记事本对程序文件进行编辑，记事本会引入一些不必要的字符
- 除界面外尽量不要引入Qt相关的函数
- 代码的列数尽量不要超过80列，这样在编辑器中浏览时不需要左右翻页的动作
- 一个函数尽可能短，长度尽量不要超过一个屏幕，如果函数过长可以考虑分为多个小函数
- 代码缩进尽量以空格缩进，以便在不同编辑器中获得相同的显示
- 每个类需要添加相关`qa_`开头的例程，用以说明每个类的不同功能

## Git

### Commit

- Commits首行以一句话简述(140字符以内)，句首字母大写，另起一行写标识符，写明做出的修改

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

### Issue

## Shell Scripts

### 变量

- 除变量名诸如`$1,$a`等只有一个数字、字母或符号的变量外，请尽量使用`{}`将变量包围，例如`${example_variable}`

### 函数

### 注释

## Doxygen

## CMake

## Markdown

- 请使用Markdown文件作为项目的说明文件