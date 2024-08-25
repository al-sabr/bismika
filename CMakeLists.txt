cmake_minimum_required(VERSION 3.21)
project(bismika LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(external_deps)

find_package(CppMicroServices REQUIRED)

include(GenerateExportHeader)
# --------------------------------------------------------------------------------------------------------
# Create executable
# --------------------------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME}
    bismika.cpp
    src/framework/PluginsListener.cpp
    src/framework/PathInformer.cpp
    src/framework/ExtendedFramework.cpp
    src/utils/MimeTypes.cpp
    
    include/modules/InMemorySchemaHandler.h
    include/utils/StringUtils.h)

target_include_directories(${PROJECT_NAME} PUBLIC 
    include
    include/framework
    include/utils
    )

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/embedded
    include/modules
    )

target_link_libraries(${PROJECT_NAME} PRIVATE saucer::saucer CppMicroServices efsw)

#set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR OFF)

set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    add_definitions(/W2)
else()
    add_definitions(-Wall -Wno-dev)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND cmake -E remove "${CMAKE_BINARY_DIR}/plugins/libresources_plugin.so")


# Dynamic Shared libraries.
add_subdirectory(bundles)