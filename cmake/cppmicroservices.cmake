# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    CppMicroServices 
    GIT_REPOSITORY "https://github.com/al-sabr/CppMicroServices" 
    GIT_TAG bundle-resource-prefix-bug+bundleregistry-embedded-manifest-bug # Pull Request #1036 & #1037
)

FetchContent_MakeAvailable(CppMicroServices)

include(GenerateExportHeader)

function(GenerateService _name _args)
    set(_srcs ${ARGN})

    usFunctionGetResourceSource(TARGET ${_name} OUT _srcs)
    usFunctionGenerateBundleInit(TARGET ${_name} OUT _srcs)

    add_library(${_name} SHARED ${_srcs})
    set_property(TARGET ${_name} APPEND PROPERTY COMPILE_DEFINITIONS US_BUNDLE_NAME=${_name})
    set_property(TARGET ${_name} APPEND PROPERTY US_BUNDLE_NAME ${_name})
    set_property(TARGET ${_name} PROPERTY DEBUG_POSTFIX "")

    generate_export_header(${_name})

    if(${_name}_DEPENDS)
        foreach(_dep ${${_name}_DEPENDS})
            include_directories(${PROJECT_SOURCE_DIR}/${_dep})
            target_link_libraries(${_name} ${_dep})
        endforeach()
    endif()
    target_link_libraries(${_name} CppMicroServices)
    set_target_properties(${_name} PROPERTIES OUTPUT_NAME ${_name})

    target_include_directories(${_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

endfunction()