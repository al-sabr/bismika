# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    saucer 
    GIT_REPOSITORY "https://github.com/saucer/saucer" 
    GIT_TAG very-experimental
)

FetchContent_MakeAvailable(saucer)