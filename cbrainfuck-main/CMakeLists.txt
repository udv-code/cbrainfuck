add_library(cbrainfuck
	INTERFACE)

target_include_directories(
	cbrainfuck

	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include/bf>
)

target_link_libraries(
	cbrainfuck
	INTERFACE
	bench
)

target_compile_options(
	cbrainfuck
	INTERFACE
	"-O3"
)