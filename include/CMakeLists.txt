##
## -- CMake public header sources
##


# list of headers that form package public interface
set(engabraPublicHeaders

	g3func.h
	g3.h
	g3long.h
	g3ops.h

	)

# install (public) header files
install(
	FILES ${engabraPublicHeaders}
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}/${engabraProjName}
	)

