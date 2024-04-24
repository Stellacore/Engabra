##
## -- CMake configuration for downstream use
##


##
## -- create Config.cmake and ConfigVersion.cmake files (for export)
##

# use CMake tools to create package
include(CMakePackageConfigHelpers)

message("### CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

configure_package_config_file(
	${CMAKE_SOURCE_DIR}/cmake/xConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/${aProjName}Config.cmake
	INSTALL_DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${aProjName}
	)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/${aProjName}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

# install the generated configuration files
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/${aProjName}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/${aProjName}ConfigVersion.cmake
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${aProjName}
)

##
## -- "publish" export targets for downstream use
##

# create export set for all targets (e.g. public headers and library)
install(
	EXPORT ${EXPORT_TARGETS_NAME}  # e.g. ${aProjName}Targets
	FILE ${EXPORT_FILENAME}        # e.g. ${aProjName}Targets.cmake
	NAMESPACE ${aProjName}:: # e.g. ${aProjName}::${aProjName}
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${aProjName}
	)

