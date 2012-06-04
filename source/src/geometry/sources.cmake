# Sources for namespace Nigel::geometry

SET (
	Nigel_SRCS
	${Nigel_SRCS}
	
	${CMAKE_CURRENT_LIST_DIR}/mesh/buffer/Buffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/buffer/VertexBuffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/Mesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/Patch.cpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/Primitive.cpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/QuadsPatch.cpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/TrianglesPatch.cpp

	${CMAKE_CURRENT_LIST_DIR}/GeometricElement.cpp
	${CMAKE_CURRENT_LIST_DIR}/GeometriesLibrary.cpp
	${CMAKE_CURRENT_LIST_DIR}/Geometry.cpp
	${CMAKE_CURRENT_LIST_DIR}/GeometryInstance.cpp
	${CMAKE_CURRENT_LIST_DIR}/IGeometryInstancesCollection.cpp
)
