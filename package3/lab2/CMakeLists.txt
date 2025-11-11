project(lab3_2)

add_executable(lab_3_2_run src/main.c src/functions.c)

target_link_options(lab_3_2_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_3_2_run PRIVATE m)

add_executable(lab_3_2_tester tests/tests.c src/functions.c)
target_link_libraries(lab_3_2_tester PRIVATE m)
