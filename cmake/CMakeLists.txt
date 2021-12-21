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
	${CMAKE_CURRENT_BINARY_DIR}/${engabraProjName}Config.cmake
	INSTALL_DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${engabraProjName}
	)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/${engabraProjName}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

# install the generated configuration files
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/${engabraProjName}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/${engabraProjName}ConfigVersion.cmake
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${engabraProjName}
)

##
## -- "publish" export targets for downstream use
##

# create export set for all targets (e.g. public headers and library)
install(
	EXPORT ${EXPORT_TARGETS_NAME}  # e.g. engabraTargets
	FILE ${EXPORT_FILENAME}        # e.g. engabraTargets.cmake
	NAMESPACE ${engabraProjName}:: # e.g. engabra::engabra
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${engabraProjName}
	)

