# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    CppMicroServices 
    GIT_REPOSITORY "https://github.com/CppMicroServices/CppMicroServices" 
    GIT_TAG v3.8.3
)

FetchContent_MakeAvailable(CppMicroServices)