set(PYTHON "C:\\Python27")

set(CMAKE_BUILD_TYPE Release)
project(pythonPluginInterfaceExample)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
include_directories(${PYTHON}\\include)
target_link_libraries (${PROJECT_NAME} ${PYTHON}\\libs\\python27.lib)

add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe ${CMAKE_CURRENT_SOURCE_DIR}\\${PROJECT_NAME}.exe )
