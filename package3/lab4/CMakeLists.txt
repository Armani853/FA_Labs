project(lab3_4)

add_executable(lab_3_4_run src/main.c src/functions.c)

# target_link_options(lab_3_4_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_3_4_run PRIVATE m)

add_executable(lab_3_4_tester tests/tests.c src/functions.c)
target_link_libraries(lab_3_4_tester PRIVATE m)
