project(resources_plugin LANGUAGES CXX VERSION 1.0)

find_package(CppMicroServices REQUIRED)

include(GenerateExportHeader)

set(_bundle_name ${PROJECT_NAME})

set(_srcs
  include/ResourcesPluginActivator.h
)

usFunctionGetResourceSource(TARGET ${PROJECT_NAME} OUT _srcs)
usFunctionGenerateBundleInit(TARGET ${PROJECT_NAME} OUT _srcs)

add_library(${PROJECT_NAME}
    ${_srcs}
  )

message("RESOURCES ${_srcs}")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND cmake -E remove "${CMAKE_BINARY_DIR}/plugins/libresources_plugind.so")

target_link_libraries(${PROJECT_NAME} CppMicroServices)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

generate_export_header(${PROJECT_NAME})

#[[
if(BUILD_SHARED_LIBS)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
endif()
]]

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY US_BUNDLE_NAME ${_bundle_name})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS US_BUNDLE_NAME=${_bundle_name})

usFunctionEmbedResources(TARGET ${_bundle_name}
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR} 
  FILES
    manifest.json
  ZIP_ARCHIVES
    site.zip
  )


set_target_properties(${PROJECT_NAME} PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
set_target_properties(${PROJECT_NAME} PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
#[[
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND usResourceCompiler3 -V -n ${_bundle_name} --out-file ${CMAKE_CURRENT_SOURCE_DIR}/manifest.zip -m ${CMAKE_CURRENT_SOURCE_DIR}/manifest.json -z ${CMAKE_SOURCE_DIR}/index.zip)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND usResourceCompiler3 -V -b ${CMAKE_BINARY_DIR}/plugins/libresources-plugind.so -z ${CMAKE_CURRENT_SOURCE_DIR}/manifest.zip)
]]

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND usResourceCompiler3 -V -b ${CMAKE_BINARY_DIR}/plugins/libresources-plugind.so -z ${CMAKE_CURRENT_SOURCE_DIR}/manifest.zip)