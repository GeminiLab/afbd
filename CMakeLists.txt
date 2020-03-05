cmake_minimum_required(VERSION 3.2)
project(rtlil)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. SOURCE)

add_library(rtlil STATIC ${SOURCE})
target_include_directories(rtlil PUBLIC include)
