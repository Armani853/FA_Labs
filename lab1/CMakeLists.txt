project(lab1)

add_executable(lab_01_run src/main.c src/functions.c)

target_link_options(lab_01_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_01_run PRIVATE m)

add_executable(test_runner src/tests.c src/functions.c)
target_link_libraries(test_runner PRIVATE m)