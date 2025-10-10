project(lab8)

add_executable(lab_08_run src/main.c src/converter.c)

target_link_options(lab_08_run PRIVATE -Wl,--subsystem,console)

target_link_libraries(lab_08_run PRIVATE m)

add_executable(test8_runner src/tests.c src/converter.c)
target_link_libraries(test_runner PRIVATE m)
