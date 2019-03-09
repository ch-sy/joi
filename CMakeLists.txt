cmake_minimum_required(VERSION 3.0)

project(joi)

set(JOI_VERSION_MAJOR "0")
set(JOI_VERSION_MINOR "1")
set(JOI_VERSION_PATCH "0")
set(JOI_VERSION_EXTRA "")
set(JOI_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")
set(JOI_VERSION_FULL "${GLFW_VERSION}.${GLFW_VERSION_PATCH}${GLFW_VERSION_EXTRA}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

include_directories(include)

set(INC
	src/joi.h
)

set(SRC
	src/joi.cpp
	src/main.cpp
)

add_executable(joi "${SRC}" "${INC}")
target_link_libraries(joi glfw)

install(TARGETS joi RUNTIME DESTINATION bin)
