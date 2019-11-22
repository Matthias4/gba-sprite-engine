project(MinionsVsZombies)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        include/MainMenu.h
        src/MainMenu.cpp
        include/Level.h
        src/Level.cpp)

target_include_directories(${PROJECT_NAME}.elf PRIVATE include)
target_include_directories(${PROJECT_NAME}.elf PRIVATE img)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba)