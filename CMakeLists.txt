cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME console_logger)

project(${PROJECT_NAME} LANGUAGES CXX)


add_library(${PROJECT_NAME} STATIC src/console_logger.cpp)
add_library(altenter::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) 

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_executable(test_app test.cpp)
target_link_libraries(test_app PRIVATE altenter::${PROJECT_NAME})