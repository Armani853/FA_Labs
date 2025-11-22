project(lab3_7)

add_executable(lab_3_7_run src/main.c src/functions.c)

# target_link_options(lab_3_7_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_3_7_run PRIVATE m)

add_executable(lab_3_7_tester tests/tests.c src/functions.c)
target_link_libraries(lab_3_7_tester PRIVATE m)
