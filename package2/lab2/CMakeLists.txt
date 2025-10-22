project(lab2_2)

add_executable(lab_2_2_run src/main.c src/functions.c)

target_link_options(lab_2_2_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_2_2_run PRIVATE m)

add_executable(lab_2_2_tester tests/tests.c src/functions.c)
target_link_libraries(lab_2_2_tester PRIVATE m)
