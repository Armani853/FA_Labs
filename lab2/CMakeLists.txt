project(lab2)

add_executable(lab_02_run src/main.c src/functions.c)

target_link_options(lab_02_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_02_run PRIVATE m)

add_executable(test2_runner src/tests.c src/functions.c)
target_link_libraries(test_runner PRIVATE m)
