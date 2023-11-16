

# list of all developer unit tests (or could GLOB for filenames)
set(unitTests

	test_g3engabra
	test_g3helloEngabra

	test_g3_private  # implementation detail

	test_g3type_ctor
	test_g3type_ComPlex
	test_g3type_DirPlex
	test_g3traits_all

	test_g3compare_all
	test_g3const_all
	test_g3io_all
	test_g3publish_all
	test_g3validity_all

	test_g3opsUni_all

	test_g3func_ga
	test_g3func_G2
	test_g3func_amp
	test_g3func_mag
	test_g3func_inv

#TODO#	test_g3func_exp

	test_g3opsAdd_same
	test_g3opsAdd_other
	test_g3opsSub_same
	test_g3opsSub_other

	test_g3opsMul_double
	test_g3opsMul_Scalar
	test_g3opsMul_Vector
	test_g3opsMul_BiVector
	test_g3opsMul_TriVector
	test_g3opsMul_Spinor
##	test_g3opsMul_same
test_g3opsMul
test_g3opsMulAll

	)

# Example of CMake loop flow control - to setup each target in turn
foreach(aUnitTest ${unitTests}) # loop over all tests

	#add_executable(${aUnitTest} test_ifc_local.cpp checks.hpp)
	add_executable(${aUnitTest} ${aUnitTest}.cpp checks.hpp)

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

