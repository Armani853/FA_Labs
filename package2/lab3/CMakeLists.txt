project(lab2_3)

add_executable(lab_2_3_run src/main.c src/functions.c)

target_link_options(lab_2_3_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_2_3_run PRIVATE m)

add_executable(lab_2_3_tester tests/tests.c src/functions.c)
target_link_libraries(lab_2_3_tester PRIVATE m)
