# Headers for the Nigel::math namespace

SET (
	Nigel_MOC_HDRS
	${Nigel_MOC_HDRS}

	# Nothing
)

SET (
	Nigel_HDRS
	${Nigel_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/Math.hpp
	${CMAKE_CURRENT_LIST_DIR}/MathEngine.hpp
	${CMAKE_CURRENT_LIST_DIR}/MathTypes.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4f.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines_CPP.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines_SSE.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4x4fRoutines.hpp
	${CMAKE_CURRENT_LIST_DIR}/Quaternionf.hpp
	${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines_CPP.hpp
	${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines_SSE.hpp
	${CMAKE_CURRENT_LIST_DIR}/QuaternionfRoutines.hpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4f.hpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4fRoutines_CPP.hpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4fRoutines.hpp
)
