# Headers for the Nigel::geometry namespace

SET (
	Nigel_MOC_HDRS
	${Nigel_MOC_HDRS}

	${CMAKE_CURRENT_LIST_DIR}/mesh/buffer/Buffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/buffer/VertexBuffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/Mesh.hpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/Patch.hpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/Primitive.hpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/QuadsPatch.hpp
	${CMAKE_CURRENT_LIST_DIR}/mesh/TrianglesPatch.hpp
	${CMAKE_CURRENT_LIST_DIR}/GeometriesLibrary.hpp
	${CMAKE_CURRENT_LIST_DIR}/Geometry.hpp
	${CMAKE_CURRENT_LIST_DIR}/GeometryInstance.hpp
)

SET (
	Nigel_HDRS
	${Nigel_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/mesh/Structures.hpp
	${CMAKE_CURRENT_LIST_DIR}/GeometricElement.hpp
	${CMAKE_CURRENT_LIST_DIR}/IGeometryInstancesCollection.hpp
)
