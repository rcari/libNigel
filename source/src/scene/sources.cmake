# Sources for namespace Nigel::scene

SET (
	Nigel_SRCS
	${Nigel_SRCS}
	
	${CMAKE_CURRENT_LIST_DIR}/transformation/Matrix.cpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Rotation.cpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Scale.cpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Transformation.cpp
	${CMAKE_CURRENT_LIST_DIR}/transformation/Translation.cpp
	${CMAKE_CURRENT_LIST_DIR}/INodesCollection.cpp
	${CMAKE_CURRENT_LIST_DIR}/Node.cpp
	${CMAKE_CURRENT_LIST_DIR}/NodeInstance.cpp
	${CMAKE_CURRENT_LIST_DIR}/NodesLibrary.cpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
	${CMAKE_CURRENT_LIST_DIR}/VisualScene.cpp
	${CMAKE_CURRENT_LIST_DIR}/VisualSceneInstance.cpp
	${CMAKE_CURRENT_LIST_DIR}/VisualScenesLibrary.cpp
)
