# Headers for the Nigel::modeling namespace

SET (
	Nigel_MOC_HDRS
	${Nigel_MOC_HDRS}

	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/BoxTrianglesMeshGenerator.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/ConeTrianglesMeshGenerator.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/CylinderTrianglesMeshGenerator.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/PlaneTrianglesMeshGenerator.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/SphereTrianglesMeshGenerator.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/meshGenerator/TorusTrianglesMeshGenerator.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/shape/Box.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Cone.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Cylinder.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Generator.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Plane.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Pyramid.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Shape.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Sphere.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/Torus.hpp
)

SET (
	Nigel_HDRS
	${Nigel_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/shape/GeneratorParameter.hpp
	${CMAKE_CURRENT_LIST_DIR}/shape/ShapeManager.hpp
	${CMAKE_CURRENT_LIST_DIR}/ModelingEngine.hpp
)
