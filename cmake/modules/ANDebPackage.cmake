#说明要生成的是deb包

set(CPACK_GENERATOR "DEB")

############下面是设置debian/control文件中的内容

#设置版本信息
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_DEBUG}")

#设置安装包的包名，打好的包将会是packagename-version-linux.deb，如果不设置，默认是工程名
set(CPACK_PACKAGE_NAME "aero-node")

#设置程序名，就是程序安装后的名字
set(CPACK_DEBIAN_PACKAGE_NAME "aero-node")

#设置架构
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

#设置依赖
set(CPACK_DEBIAN_PACKAGE_DEPENDS "liblog4cpp5 libasound2")

#设置section
set(CPACK_DEBIAN_PACKAGE_SECTION "net")

#设置priority
set(CPACK_DEBIAN_PACKAGE_PRIORITY "Optional")

#设置description
set(CPACK_PACKAGE_DESCRIPTION "Aero Node")

#设置联系方式
set(CPACK_PACKAGE_CONTACT "j824544269@gmail.com")

#设置维护人
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "AeroLab411")

include(CPack)