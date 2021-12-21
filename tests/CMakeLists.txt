

# list of all developer unit tests (or could GLOB for filenames)
set(unitTests

	test_engabra
	test_g3compare
	test_g3consts
	test_g3io
	test_g3opsBinAdd
	test_g3opsUni
	test_g3types
	test_g3validity
	test_helloEngabra

	)

# Example of CMake loop flow control - to setup each target in turn
foreach(aUnitTest ${unitTests}) # loop over all tests

#add_executable(${aUnitTest} test_ifc_local.cpp test_common.hpp)
add_executable(${aUnitTest} ${aUnitTest}.cpp test_common.hpp)

target_include_directories(
	${aUnitTest}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include # public interface includes
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src # project source (to be tested)
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

