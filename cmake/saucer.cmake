# --------------------------------------------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------------------------------------------

FetchContent_Declare(
    saucer 
    GIT_REPOSITORY "https://github.com/saucer/saucer" 
    GIT_TAG v3.0.0-beta
)

FetchContent_MakeAvailable(saucer)