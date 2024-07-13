# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    efsw 
    GIT_REPOSITORY "https://github.com/SpartanJ/efsw" 
    GIT_TAG master
)

FetchContent_MakeAvailable(efsw)