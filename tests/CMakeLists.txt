add_executable(bf-interpreter-test "main.cpp")

target_link_libraries(bf-interpreter-test PUBLIC cbrainfuck)

target_compile_options(
	bf-interpreter-test
	INTERFACE
	"-O3"
)