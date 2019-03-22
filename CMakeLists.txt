cmake_minimum_required(VERSION 3.0)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.111.tar.gz"
    SHA1 "4189bbd869abe4eb69b5303d3f916c03d34dc154"
)

project(joi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(JOI_VERSION_MAJOR "0")
set(JOI_VERSION_MINOR "1")
set(JOI_VERSION_PATCH "0")
set(JOI_VERSION_EXTRA "")
set(JOI_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")
set(JOI_VERSION_FULL "${GLFW_VERSION}.${GLFW_VERSION_PATCH}${GLFW_VERSION_EXTRA}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

# glfw
hunter_add_package(glfw)
find_package(glfw3 REQUIRED)

# glm
hunter_add_package(glm)
find_package(glm REQUIRED)

# zlib
hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)

# vorbis
#hunter_add_package(vorbis)
#find_package(vorbis CONFIG REQUIRED)

# fmt
hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)

# glog
hunter_add_package(glog)
find_package(glog CONFIG REQUIRED)

# EntityX
hunter_add_package(entityx)
find_package(entityx CONFIG REQUIRED)

set(INC
	src/glad/glad.h
	src/glad/khrplatform.h
	src/joi.h
	src/resourceManager.h
	src/sprite.h
	src/aseprite.h
	src/shader.h
)

set(SRC
	src/glad/glad.c
	src/joi.cpp
	src/main.cpp
	src/resourceManager.cpp
	src/sprite.cpp
	src/aseprite.cpp
	src/shader.cpp
)

add_executable(joi "${SRC}" "${INC}")
target_link_libraries(joi glfw)
target_link_libraries(joi glm)
target_link_libraries(joi ZLIB::zlib)
#target_link_libraries(joi vorbis::vorbis)
target_link_libraries(joi fmt::fmt)
target_link_libraries(joi entityx::entityx)
target_link_libraries(joi glog::glog)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_link_libraries(joi c++experimental)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(joi stdc++fs)
endif()



install(TARGETS joi RUNTIME DESTINATION bin)
