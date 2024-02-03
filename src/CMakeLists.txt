##
## -- CMake source code tree
##


# list of sources on which library depends
set(${aProjName}LibSources

	engabra.cpp
	foo.cpp
	
	)

# create CMake library target
add_library(
	${${aProjName}LibName}
	STATIC
		${${aProjName}LibSources}
	)

target_compile_options(
	${${aProjName}LibName}
	PRIVATE
		$<$<CXX_COMPILER_ID:Clang>:${BUILD_FLAGS_FOR_CLANG}>
		$<$<CXX_COMPILER_ID:GNU>:${BUILD_FLAGS_FOR_GCC}>
		$<$<CXX_COMPILER_ID:MSVC>:${BUILD_FLAGS_FOR_VISUAL}>
	)

target_include_directories(
	${${aProjName}LibName}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
		$<INSTALL_INTERFACE:include/${aProjName}>
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	)

# install the library
install(
	TARGETS ${${aProjName}LibName}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)

# Alias for use in downstream CMakeLists
add_library(${aProjName}::${aProjName} ALIAS ${${aProjName}LibName})

# Export info
add_library(
	${EXPORT_ALIAS_NAME}
	ALIAS
	${${aProjName}LibName}
	)

# export linkable library target
install(
	TARGETS ${${aProjName}LibName}
	EXPORT ${EXPORT_TARGETS_NAME}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	#[[
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${${aProjName}_LibDIR}>
		$<INSTALL_INTERFACE:${${aProjName}_LibDIR}>
	NAMESPACE ${aProjName}:: # e.g. ${aProjName}::${aProjName}
	#]]
	)

