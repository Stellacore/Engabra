
# The well documented CMake command
cmake_minimum_required(VERSION 3.13)

# This project
# Note that the version and description are propagated to the DEB package
project(
	EnGAbra
	VERSION 0.1.0
	DESCRIPTION "Practical Geometric Algebra Computation for Engineering"
	LANGUAGES CXX
	)

# General package compile configuration
# Note: can use target_compile_features() to customize for individual target
add_compile_options(-std=c++11 -pedantic)

# unit test capabilities
# Include and enable here for enable to be inherited by subdir tree
include(CTest)
enable_testing()

# Inform CMake about project tree
# (each subdir needs its own CMakeLists.txt file)
add_subdirectory(include) # project library public interface (e.g. c++ headers)
add_subdirectory(doc) # project reference documentation
#add_subdirectory(src) # project source code
add_subdirectory(tests) # developer unit tests (check source code operation)
#add_subdirectory(demos) # demonstration/example code
#add_subdirectory(vnv) # user validation tests

#[[

# src/library from: set(modLibName engabra)

# Export cmake configuration files

set_property(
	TARGET engabra
	PROPERTY VERSION ${ExampleOfCMake_VERSION}
	)
set_property(
	TARGET engabra
	PROPERTY VERSION INTERFACE_ExampleOfCMake_MAJOR_VERSION 1
	)
set_property(
	TARGET engabra
	APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ExampleOfCMake_MAJOR_VERSION
	)


include(CMakePackageConfigHelpers)

set(EXPO engabra)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${EXPO}/${EXPO}ConfigVersion.cmake"
	VERSION ${ExampleOfCMake_VERSION}
	COMPATIBILITY AnyNewerVersion
	)
export(
	EXPORT ${EXPO}Targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/${EXPO}/${EXPO}Targets.cmake"
	NAMESPACE ExampleOfCMake::
	)
configure_file(
	cmake/ExampleOfCMakeConfig.cmake
	"${CMAKE_CURRENT_BINARY_DIR}/${EXPO}/ExampleOfCMakeConfig.cmake"
	COPYONLY
	)

set(ConfigPackageLocation lib/cmake/ExampleOfCMake)
install(
	EXPORT ${EXPO}Targets
	FILE ${EXPO}Targets.cmake
	NAMESPACE ExampleOfCMake::
	DESTINATION ${ConfigPackageLocation}
	#	COMPONENT Devel
	)
install(
	FILES
		cmake/ExampleOfCMakeConfig.cmake
		"${CMAKE_CURRENT_BINARY_DIR}/${EXPO}/${EXPO}ConfigVersion.cmake"
	DESTINATION ${ConfigPackageLocation}
	#	COMPONENT Devel
	)

#]]

#[[

# Override default install location for testing this package
# In general default (no command here) will install to /usr/{lib,bin,...}
# - but here, set package to isolated location for easier/safer testing
set(CPACK_PACKAGING_INSTALL_PREFIX "/tmp/local/${PROJECT_NAME}")

# Specify various generic-package distribuation properties
# set(CPACK_PACKAGE_NAME ${PROJECT_NAME}) # same as default
set(CPACK_PACKAGE_VENDOR "PackageVendor") # ? not used by debian generator?
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})

# Set package(Generator) specific characteristics
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
	"libc6 (>= 2.28), libgcc1 (>= 1:8)" # arbitrary - as example
	)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PackageMaintainer")


# Must be included after the package variables are set
include(CPack)

#]]

