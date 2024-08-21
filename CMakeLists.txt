cmake_minimum_required(VERSION 3.21)
project(bismika LANGUAGES CXX VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(external_deps)
# --------------------------------------------------------------------------------------------------------
# Create executable
# --------------------------------------------------------------------------------------------------------

add_subdirectory(bundles)

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

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} PRIVATE saucer::saucer CppMicroServices efsw)

#set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR OFF)

set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    add_definitions(/W2)
else()
    add_definitions(-Wall -Wno-dev)
endif()
