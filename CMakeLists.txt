cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME console_logger)

project(${PROJECT_NAME} LANGUAGES CXX)


add_library(${PROJECT_NAME} STATIC src/console_logger.cpp)
add_library(altenter::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) 

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
