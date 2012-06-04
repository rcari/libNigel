# Sources for namespace Nigel::modeling

SET (
	Nigel_SRCS
	${Nigel_SRCS}
	
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/BoxTrianglesMeshGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/ConeTrianglesMeshGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/CylinderTrianglesMeshGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/PlaneTrianglesMeshGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/SphereTrianglesMeshGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/TorusTrianglesMeshGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Box.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Cone.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Cylinder.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Generator.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/GeneratorParameter.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Plane.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Pyramid.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Shape.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/ShapeManager.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Sphere.cpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Torus.cpp
)
