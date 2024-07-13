# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    saucer 
    GIT_REPOSITORY "https://github.com/saucer/saucer" 
    GIT_TAG v2.3.0
)

FetchContent_MakeAvailable(saucer)