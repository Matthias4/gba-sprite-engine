project(MinionsVsZombies)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp

        include/MainMenu.h
        src/MainMenu.cpp
        include/About.h
        src/About.cpp

        include/Level.h
        src/Level.cpp

        include/Minions/Minion.h
        src/Minions/Minion.cpp
        include/Minions/FlowerMinion.h
        src/Minions/FlowerMinion.cpp
        include/Minions/Shooter.h
        src/Minions/Shooter.cpp

        include/Enemies/Enemy.h
        src/Enemies/Enemy.cpp
        include/Enemies/Zombie.h
        src/Enemies/Zombie.cpp

        img/minion_image.h
        img/png/shared.h
        img/png/shared.c
        img/png/minion.h
        img/png/minion.c
        img/png/BananaMinion.h
        img/png/BananaMinion.c
        img/png/Grass.h
        img/png/Grass.c
        img/png/Zombie.h
        img/png/Zombie.c
        )

target_include_directories(${PROJECT_NAME}.elf PRIVATE include)
target_include_directories(${PROJECT_NAME}.elf PRIVATE img)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba)

add_subdirectory(test)