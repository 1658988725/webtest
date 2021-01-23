PROJECT(main)
cmake_minimum_required(VERSION 3.10)
SET(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} ${O_FLAG} -std=c++11 -Wno-deprecated-declarations -ffunction-sections -fdata-sections -Werror"
)
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/json
)

SET(SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/json/jsoncpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mongoose.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mongoose.c
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


add_executable(${PROJECT_NAME} ${SRC_LIST})