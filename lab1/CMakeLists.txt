project(lab1)

add_executable(lab_01_run src/main.c src/functions.c)

target_include_directories(lab_01_run PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_options(lab_01_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_01_run PRIVATE m)

