cmake_minimum_required(VERSION 3.0.0)
project(DungeonCrawler VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(DungeonCrawler main.c room.h room.c game.h game.c utility.h utility.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
