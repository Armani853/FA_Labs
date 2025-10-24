project(lab2_5)

add_executable(lab_2_5_run src/main.c src/functions.c)

target_link_options(lab_2_5_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_2_5_run PRIVATE m)

add_executable(lab_2_5_tester tests/tests.c src/functions.c)
target_link_libraries(lab_2_5_tester PRIVATE m)
