# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    CppMicroServices 
    GIT_REPOSITORY "https://github.com/al-sabr/CppMicroServices" 
    GIT_TAG bundle-resource-bug-fixes
)

FetchContent_MakeAvailable(CppMicroServices)