# Sources for namespace Nigel::COLLADA

SET (
	Nigel_SRCS
	${Nigel_SRCS}
	
	${CMAKE_CURRENT_LIST_DIR}/asset/Asset.cpp
	${CMAKE_CURRENT_LIST_DIR}/asset/Contributor.cpp
	${CMAKE_CURRENT_LIST_DIR}/asset/IAssetOwner.cpp

	${CMAKE_CURRENT_LIST_DIR}/data/FloatArray.cpp
	${CMAKE_CURRENT_LIST_DIR}/data/IArray.cpp
	${CMAKE_CURRENT_LIST_DIR}/data/IntArray.cpp
	${CMAKE_CURRENT_LIST_DIR}/data/ISourcesCollection.cpp
	${CMAKE_CURRENT_LIST_DIR}/data/Source.cpp

	${CMAKE_CURRENT_LIST_DIR}/extra/Extra.cpp
	${CMAKE_CURRENT_LIST_DIR}/extra/IExtrasCollection.cpp

	${CMAKE_CURRENT_LIST_DIR}/instantiation/ElementInstance.cpp

	${CMAKE_CURRENT_LIST_DIR}/DocumentInstance.cpp
	${CMAKE_CURRENT_LIST_DIR}/DocumentInstanceReference.cpp
	${CMAKE_CURRENT_LIST_DIR}/Element.cpp
	${CMAKE_CURRENT_LIST_DIR}/IElement.cpp
	${CMAKE_CURRENT_LIST_DIR}/InstancesManager.cpp
	${CMAKE_CURRENT_LIST_DIR}/IScopedElement.cpp
	${CMAKE_CURRENT_LIST_DIR}/IUniqueElement.cpp
	${CMAKE_CURRENT_LIST_DIR}/ScopedElement.cpp
	${CMAKE_CURRENT_LIST_DIR}/UniqueElement.cpp
	${CMAKE_CURRENT_LIST_DIR}/UniqueScopedElement.cpp
)
