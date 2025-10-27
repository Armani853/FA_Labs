project(lab2_6)

add_executable(lab_2_6_run src/main.c src/functions.c)

target_link_options(lab_2_6_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_2_6_run PRIVATE m)

add_executable(lab_2_6_tester tests/tests.c src/functions.c)
target_link_libraries(lab_2_6_tester PRIVATE m)
