project(lab2_1)

add_executable(lab_2_1_run src/main.c src/functions.c)

target_link_options(lab_2_1_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_2_1_run PRIVATE m)

add_executable(lab_2_1_tester tests/tests.c src/functions.c)
target_link_libraries(lab_2_1_tester PRIVATE m)
