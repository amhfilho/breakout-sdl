cmake_minimum_required(VERSION 4.3)
project(breakout_sdl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew" "/usr/local")

# Avoid picking up a separately-installed SDL3.framework (e.g. in
# ~/Library/Frameworks) while SDL3_image resolves to the Homebrew dylib.
# Loading both SDL3 binaries into the same process causes duplicate
# Objective-C class registrations and crashes at runtime.
set(CMAKE_FIND_FRAMEWORK NEVER)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

include_directories(include)

add_executable(${PROJECT_NAME}
    src/main.cpp
        src/Game.cpp
        include/Game.h
        include/Constants.h
        include/Colors.h
        src/Colors.cpp
        src/Brick.cpp
        include/Brick.h
        include/Vector2.h
        src/Paddle.cpp
        include/Paddle.h

)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)
# Copy game assets next to the executable so they are found via SDL_GetBasePath()
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/Graphics $<TARGET_FILE_DIR:${PROJECT_NAME}>/Graphics
#)

