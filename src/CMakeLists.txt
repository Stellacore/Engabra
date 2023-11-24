##
## -- CMake source code tree
##


set(engabraLibName engabra)

# list of sources on which library depends
set(engabraLibSources

	engabra.cpp
	foo.cpp
	
	)

# create CMake library target
add_library(
	${engabraLibName}
	STATIC
	${engabraLibSources}
	)

target_compile_options(
	${engabraLibName}
	PRIVATE
		$<$<CXX_COMPILER_ID:Clang>:${BUILD_FLAGS_FOR_CLANG}>
		$<$<CXX_COMPILER_ID:GNU>:${BUILD_FLAGS_FOR_GCC}>
		$<$<CXX_COMPILER_ID:MSVC>:${BUILD_FLAGS_FOR_VISUAL}>
	)

target_include_directories(
	${engabraLibName}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
		$<INSTALL_INTERFACE:include/${engabraProjName}>
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	)

# install the library
install(
	TARGETS ${engabraLibName}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)

# Alias for use in downstream CMakeLists
add_library(engabra::${engabraProjName} ALIAS ${engabraLibName})

# Export info
add_library(
	${EXPORT_ALIAS_NAME}
	ALIAS
	${engabraLibName}
	)

# export linkable library target
install(
	TARGETS ${engabraLibName}
	EXPORT ${EXPORT_TARGETS_NAME}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	#[[
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${engabra_LibDIR}>
		$<INSTALL_INTERFACE:${engabra_LibDIR}>
	NAMESPACE ${engabraProjName}:: # e.g. engabra::engabra
	#]]
	)

