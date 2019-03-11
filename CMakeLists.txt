cmake_minimum_required(VERSION 3.0)

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

# glfw Library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

# glm Library
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glm)

# zlib Library
set(ZLIB_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/zlib)

include_directories(include)

set(INC
	src/joi.h
	src/resourceManager.h
	src/sprite.h
	src/aseprite.h
)

set(SRC
	src/joi.cpp
	src/main.cpp
	src/resourceManager.cpp
	src/sprite.cpp
	src/aseprite.cpp
)


add_executable(joi "${SRC}" "${INC}")
target_link_libraries(joi glfw)
target_link_libraries(joi glm)
target_link_libraries(joi zlib)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_link_libraries(${PROJECT_NAME} c++experimental)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(joi stdc++fs)
endif()

install(TARGETS joi RUNTIME DESTINATION bin)
