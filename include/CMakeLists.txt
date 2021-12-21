##
## -- CMake public header sources
##


# list of headers that form package public interface
set(engabraPublicHeaders

	g3compare.hpp
	g3consts.hpp
	g3funcs.hpp
	g3io.hpp
	g3opsBinAdd.hpp
	g3opsBin.hpp
	g3ops.hpp
	g3opsUni.hpp
	g3types.hpp
	g3validity.hpp

	engabra.hpp

	)

# install (public) header files
install(
	FILES ${engabraPublicHeaders}
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}/${engabraProjName}
	)

