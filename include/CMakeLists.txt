
# list of headers that form package public interface
set(allPublicHeaders

	engabra.hpp
	g3types.hpp
	
	)

install(
	FILES ${allPublicHeaders}
	DESTINATION include # disto packages uses (e.g. </usr/local>/include
	)

