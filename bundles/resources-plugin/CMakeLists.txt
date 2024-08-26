project(resources_plugin LANGUAGES CXX VERSION 1.0)

set(_bundle_name ${PROJECT_NAME})

GenerateService(${_bundle_name} src/ResourcesPluginActivator.cpp include/ResourcesPluginActivator.h)

#[[
if(BUILD_SHARED_LIBS)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
endif()
]]

#file(REMOVE "${CMAKE_BINARY_DIR}/plugins/lib${PROJECT_NAME}.so")

usFunctionEmbedResources(TARGET ${_bundle_name}
  WORKING_DIRECTORY
    resources
  FILES
    manifest.json
  ZIP_ARCHIVES
    site.zip
  )