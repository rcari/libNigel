CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

PROJECT ( Nigel C CXX )

SET ( Nigel_Version "0.0.1" )

# Kore dependency...
IF( KORE_FOUND )
	INCLUDE_DIRECTORIES( ${KORE_INCLUDE_DIRS} )
ELSE()
	MESSAGE( FATAL_ERROR "Unresolved dependency to the Kore module" ) 
ENDIF( KORE_FOUND )

# Headers
INCLUDE_DIRECTORIES ( inc )

# Template files
INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_SOURCE_DIR} )

### ------------- Nigel -------------
SET ( Nigel_SRCS src/NigelApplication.cpp )

INCLUDE ( src/animation/sources.cmake )
INCLUDE ( src/camera/sources.cmake )
INCLUDE ( src/COLLADA/sources.cmake )
INCLUDE ( src/fx/sources.cmake )
INCLUDE ( src/geometry/sources.cmake )
INCLUDE ( src/lighting/sources.cmake )
INCLUDE ( src/math/sources.cmake )
INCLUDE ( src/modeling/sources.cmake )
INCLUDE ( src/project/sources.cmake )
INCLUDE ( src/rendering/sources.cmake )
INCLUDE ( src/scene/sources.cmake )

SET ( 
	Nigel_HDRS
	
	inc/NigelApplication.hpp
	inc/NigelExport.hpp
)
SET ( Nigel_MOC_HDRS )

INCLUDE ( inc/animation/headers.cmake )
INCLUDE ( inc/camera/headers.cmake )
INCLUDE ( inc/COLLADA/headers.cmake )
INCLUDE ( inc/fx/headers.cmake )
INCLUDE ( inc/geometry/headers.cmake )
INCLUDE ( inc/lighting/headers.cmake )
INCLUDE ( inc/math/headers.cmake )
INCLUDE ( inc/modeling/headers.cmake )
INCLUDE ( inc/project/headers.cmake )
INCLUDE ( inc/rendering/headers.cmake )
INCLUDE ( inc/scene/headers.cmake )

### ------------- MOC --------------
IF ( MSVC )
SET( Nigel_MOC_SRCS )
	FOREACH( hdr ${Nigel_MOC_HDRS} )
		SET( _MOC_SRCS )
		QT4_WRAP_CPP ( _MOC_SRCS ${hdr} OPTIONS -f"${CMAKE_CURRENT_SOURCE_DIR}/../inc/NigelMSVC.hpp" -f"${CMAKE_CURRENT_SOURCE_DIR}/${hdr}" )
		SET( Nigel_MOC_SRCS ${Nigel_MOC_SRCS} ${_MOC_SRCS} )
	ENDFOREACH( hdr ${Nigel_MOC_HDRS} )
ELSE ( MSVC )
	QT4_WRAP_CPP ( Nigel_MOC_SRCS ${Nigel_MOC_HDRS} )
ENDIF ( MSVC )

# Target library: Nigel
ADD_LIBRARY ( Nigel SHARED ${Nigel_HDRS} ${Nigel_MOC_HDRS} ${Nigel_SRCS} ${Nigel_MOC_SRCS} )

# Mac OS specifics
IF ( APPLE )
	SET_TARGET_PROPERTIES ( 
		Nigel PROPERTIES
		COMPILE_DEFINITIONS "_K_BUILD_NIGEL;_NIGEL_VERSION=\"${Nigel_Version}\";_K_MACX;${DEBUG_DEFINES}"
		COMPILE_FLAGS -fno-common
		LINK_FLAGS "-undefined dynamic_lookup"
		VERSION ${Nigel_Version}
	)
# Windows specifics
ELSEIF ( WIN32 )
	# Visual Studio compiler specifics
	IF ( MSVC )
		SOURCE_GROUP ( "Header Files" FILES ${Nigel_HDRS} ${Nigel_MOC_HDRS} )
		SOURCE_GROUP ( "Source Files" FILES ${Nigel_SRCS} )
		SOURCE_GROUP ( "Moc Files" FILES ${Nigel_MOC_SRCS} )
		SET_TARGET_PROPERTIES ( 
			Nigel PROPERTIES
			COMPILE_DEFINITIONS "_K_BUILD_NIGEL;_NIGEL_VERSION=\"${Nigel_Version}\";_K_WIN32;${DEBUG_DEFINES};NIGEL_MSVC"
			VERSION ${Nigel_Version}
		)
		IF ( CMAKE_CXX_FLAGS MATCHES "/EHsc " )
			string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
		ENDIF ()
	# Others compilers specifics
	ELSE ( MSVC )
		SET_TARGET_PROPERTIES ( 
				Nigel PROPERTIES
				COMPILE_FLAGS -msse
				COMPILE_DEFINITIONS "_K_BUILD_NIGEL;_NIGEL_VERSION=\"${Nigel_Version}\";_K_WIN32;${DEBUG_DEFINES}"
				VERSION ${Nigel_Version}
			)
	ENDIF ( MSVC )
	TARGET_LINK_LIBRARIES ( Nigel Kore ${QT_QTCORE_LIBRARY} )
# Linux specifics
ELSEIF ( UNIX )
	SET_TARGET_PROPERTIES ( 
		Nigel PROPERTIES
		COMPILE_FLAGS -msse
		COMPILE_DEFINITIONS "_K_BUILD_NIGEL;_NIGEL_VERSION=\"${Nigel_Version}\";_K_UNIX;${DEBUG_DEFINES}"
		VERSION ${Nigel_Version}
	)
	TARGET_LINK_LIBRARIES ( Nigel Kore ${QT_QTCORE_LIBRARY} )
ENDIF ( APPLE )

# Documentation
IF ( DOXYGEN_FOUND )
	SET ( DOXYGEN_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../doc/html )
	ADD_CUSTOM_COMMAND (
		OUTPUT ${DOXYGEN_OUTPUT}
		COMMAND ${CMAKE_COMMAND} -E echo_append "Building Nigel Documentation..."
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../doc/Doxyfile
		COMMAND ${CMAKE_COMMAND} -E echo "Done."
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../doc
	 )
	ADD_CUSTOM_TARGET ( nigel-doc DEPENDS ${DOXYGEN_OUTPUT} )
ENDIF ( DOXYGEN_FOUND )
