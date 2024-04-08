cmake_minimum_required(VERSION 3.27)
project(opengl_demo)

set(CMAKE_CXX_STANDARD 17)

link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/tools
)

file(GLOB_RECURSE SOURCE_LIST
        "src/*.cpp"
        "src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} glfw3)
