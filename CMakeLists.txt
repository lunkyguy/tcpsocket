# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)
# 项目信息
project (Socket)
#添加QT库
find_package(Qt5Core)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(Socket ${DIR_SRCS})
target_link_libraries(Socket Qt5::Core)
