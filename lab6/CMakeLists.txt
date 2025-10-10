project(lab6)

add_executable(lab_06_run src/main.c src/functions.c)

target_link_options(lab_06_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_06_run PRIVATE m)

add_executable(test6_runner src/tests.c src/functions.c)
target_link_libraries(test_runner PRIVATE m)
