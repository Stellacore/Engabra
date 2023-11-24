##
## -- CMake public header sources
##


# list of headers that form package public interface
set(engabraPublicHeaders

	Engabra
	engabra.hpp

	g3_private.hpp

	g3type.hpp

	g3compare.hpp
	g3const.hpp
	g3func.hpp
	g3io.hpp
	g3opsAdd_BiVector.hpp
	g3opsAdd_ComPlex.hpp
	g3opsAdd_DirPlex.hpp
	g3opsAdd.hpp
	g3opsAdd_ImSpin.hpp
	g3opsAdd_MultiVector.hpp
	g3opsAdd_same.hpp
	g3opsAdd_Scalar.hpp
	g3opsAdd_Spinor.hpp
	g3opsAdd_TriVector.hpp
	g3opsAdd_Vector.hpp
	g3ops.hpp
	g3opsMul_BiVector.hpp
	g3opsMul_ComPlex.hpp
	g3opsMul_DirPlex.hpp
	g3opsMul_double.hpp
	g3opsMul.hpp
	g3opsMul_ImSpin.hpp
	g3opsMul_MultiVector.hpp
	g3opsMul_Scalar.hpp
	g3opsMul_Spinor.hpp
	g3opsMul_TriVector.hpp
	g3opsMul_Vector.hpp
	g3opsSub_BiVector.hpp
	g3opsSub_ComPlex.hpp
	g3opsSub_DirPlex.hpp
	g3opsSub.hpp
	g3opsSub_ImSpin.hpp
	g3opsSub_MultiVector.hpp
	g3opsSub_same.hpp
	g3opsSub_Scalar.hpp
	g3opsSub_Spinor.hpp
	g3opsSub_TriVector.hpp
	g3opsSub_Vector.hpp
	g3opsUni.hpp
	g3publish.hpp
	g3traits.hpp
	g3validity.hpp

	)

# install (public) header files
install(
	FILES ${engabraPublicHeaders}
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}/${engabraProjName}
	)

