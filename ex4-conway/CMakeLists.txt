cmake_minimum_required(VERSION 4.0)
project(conway)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(conway src/main.cxx src/Cell.cxx src/Grid.cxx src/Display.cxx)
target_include_directories(conway PUBLIC ${PROJECT_SOURCE_DIR}/include)

install(TARGETS conway RUNTIME DESTINATION bin)
