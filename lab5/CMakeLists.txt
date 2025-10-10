project(lab5)

add_executable(lab_05_run src/main.c src/functions.c)

target_link_options(lab_05_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_05_run PRIVATE m)

add_executable(test5_runner src/tests.c src/functions.c)
target_link_libraries(test_runner PRIVATE m)
