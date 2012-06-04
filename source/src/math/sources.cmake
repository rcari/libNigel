# Sources for the Nigel::math namespace

SET (
	Nigel_SRCS
	${Nigel_SRCS}
	
	${CMAKE_CURRENT_LIST_DIR}/MathEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4f.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines_CPP.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines_SSE.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines.cpp
	${CMAKE_CURRENT_LIST_DIR}/Quaternionf.cpp
	${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines_CPP.cpp
	${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines_SSE.cpp
	${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4f.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4fRoutines_CPP.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4fRoutines_SSE.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4fRoutines.cpp
)

IF ( MSVC )
	SET (
		Nigel_SRCS
		${Nigel_SRCS}

		${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines_SSE_MSVC.cpp
	)
ELSE ( MSVC )
	SET (
		Nigel_SRCS
		${Nigel_SRCS}

		${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines_SSE_GCC.cpp
		${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines_SSE_GCC.cpp
		${CMAKE_CURRENT_LIST_DIR}/Vector4fRoutines_SSE_GCC.cpp
	)
ENDIF ( MSVC )
