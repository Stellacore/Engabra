

# list of all developer unit tests (or could GLOB for filenames)
set(unitTests

	test_helloEngabra

	test_engabra

	test_g3traits
	test_g3type
	test_g3io

	test_g3compare
	test_g3const
	test_g3publish
	test_g3validity

	test_g3opsAdd
	test_g3opsMul
	test_g3opsMulAll
	test_g3opsUni

	test_g3func
	test_g3func_exp

	)

# Example of CMake loop flow control - to setup each target in turn
foreach(aUnitTest ${unitTests}) # loop over all tests

	#add_executable(${aUnitTest} test_ifc_local.cpp test_common.hpp)
	add_executable(${aUnitTest} ${aUnitTest}.cpp test_common.hpp)

	target_compile_options(
		${aUnitTest}
		PRIVATE
			$<$<CXX_COMPILER_ID:Clang>:${BUILD_FLAGS_FOR_CLANG}>
			$<$<CXX_COMPILER_ID:GNU>:${BUILD_FLAGS_FOR_GCC}>
			$<$<CXX_COMPILER_ID:MSVC>:${BUILD_FLAGS_FOR_VISUAL}>
		)

	target_include_directories(
		${aUnitTest}
		PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include # public interface
		PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src # project source
		PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}  # local test code includes
		)

	#[[
	target_link_libraries(
		${aUnitTest}
		LINK_PUBLIC engabra
		)
	#]]

	# add test to CTest collection
	add_test(
		${aUnitTest}  # cmake target
		${aUnitTest}  # command to run test (no command line arguments used)
		)

endforeach(aUnitTest)

