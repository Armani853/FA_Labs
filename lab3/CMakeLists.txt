project(lab2)

add_executable(lab_03_run src/main.c src/functions.c)

target_link_options(lab_03_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_03_run PRIVATE m)

add_executable(test3_runner src/tests.c src/functions.c)
target_link_libraries(test_runner PRIVATE m)
