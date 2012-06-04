# Headers for the Nigel::scene namespace

SET (
	Nigel_MOC_HDRS
	${Nigel_MOC_HDRS}

	${CMAKE_CURRENT_LIST_DIR}/transformation/Matrix.hpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Rotation.hpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Scale.hpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Transformation.hpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Translation.hpp
	${CMAKE_CURRENT_LIST_DIR}/INodesCollection.hpp
	${CMAKE_CURRENT_LIST_DIR}/Node.hpp
	${CMAKE_CURRENT_LIST_DIR}/NodeInstance.hpp
	${CMAKE_CURRENT_LIST_DIR}/NodesLibrary.hpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.hpp
	${CMAKE_CURRENT_LIST_DIR}/VisualScene.hpp
	${CMAKE_CURRENT_LIST_DIR}/VisualSceneInstance.hpp
	${CMAKE_CURRENT_LIST_DIR}/VisualScenesLibrary.hpp
)

SET (
	Nigel_HDRS
	${Nigel_HDRS}
	
	# Nothing
)
