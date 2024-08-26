project(fractal_plugin LANGUAGES CXX VERSION 1.0)

set(_bundle_name ${PROJECT_NAME})

GenerateService(${_bundle_name} src/FractalPluginActivator.cpp include/FractalPluginActivator.h)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

#[[
if(BUILD_SHARED_LIBS)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
endif()
]]

usFunctionEmbedResources(TARGET ${_bundle_name}
  WORKING_DIRECTORY
    resources
  FILES
    manifest.json

  )