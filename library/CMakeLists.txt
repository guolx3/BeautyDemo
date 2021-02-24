cmake_minimum_required(VERSION 3.4.1)

project(test)

# import 2DSlender
add_library(
        2DSlender
        SHARED
        IMPORTED )
set_target_properties(
        2DSlender
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/src/main/cpp/preview_vp4.0.08/libs/${ANDROID_ABI}/lib2DSlender.so )
include_directories( src/main/cpp/preview_vp4.0.08 )

# add native-lib
add_library(
        native-lib
        SHARED
        src/main/cpp/hello.cpp)
include_directories(src/main/cpp/include/)


target_link_libraries( native-lib 2DSlender GLESv2)