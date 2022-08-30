# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.1)

project (SimIgDecoder)
aux_source_directory(src SOURCES)


add_executable (SimIgDecoder ${SOURCES})

target_include_directories(SimIgDecoder PUBLIC ${PROJECT_SOURCE_DIR}/thirdpart) 