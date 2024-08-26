project(resources_plugin LANGUAGES CXX VERSION 1.0)

set(_bundle_name ${PROJECT_NAME})

GenerateService(${_bundle_name} include/ResourcesPluginActivator.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

file(REMOVE "${CMAKE_BINARY_DIR}/plugins/lib${PROJECT_NAME}.so")

usFunctionEmbedResources(TARGET ${_bundle_name}
  WORKING_DIRECTORY
    resources
  FILES
    manifest.json
  ZIP_ARCHIVES
    site.zip
  )