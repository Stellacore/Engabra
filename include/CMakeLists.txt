##
## -- CMake public header sources
##


# list of headers that form package public interface
set(engabraPublicHeaders

	g3compare.hpp
	g3const.hpp
	g3func.hpp
	g3io.hpp
	g3opsAdd.hpp
	g3ops.hpp
	g3opsMul.hpp
	g3opsUni.hpp
	g3publish.hpp
	g3traits.hpp
	g3type.hpp
	g3validity.hpp

	engabra.hpp

	g3opsMul.inl

	)

# install (public) header files
install(
	FILES ${engabraPublicHeaders}
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}/${engabraProjName}
	)

