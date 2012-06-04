# Headers for the Nigel::COLLADA namespace

SET (
	Nigel_MOC_HDRS
	${Nigel_MOC_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/asset/Asset.hpp
	${CMAKE_CURRENT_LIST_DIR}/asset/Contributor.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/data/FloatArray.hpp
	${CMAKE_CURRENT_LIST_DIR}/data/IntArray.hpp
	${CMAKE_CURRENT_LIST_DIR}/data/Source.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/extra/Extra.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/instantiation/ElementInstance.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/DocumentInstance.hpp
	${CMAKE_CURRENT_LIST_DIR}/DocumentInstanceReference.hpp
	${CMAKE_CURRENT_LIST_DIR}/Element.hpp
	${CMAKE_CURRENT_LIST_DIR}/InstancesManager.hpp
	${CMAKE_CURRENT_LIST_DIR}/ScopedElement.hpp
	${CMAKE_CURRENT_LIST_DIR}/UniqueElement.hpp
	${CMAKE_CURRENT_LIST_DIR}/UniqueScopedElement.hpp	
)

SET (
	Nigel_HDRS
	${Nigel_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/asset/IAssetOwner.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/data/Accessor.hpp
	${CMAKE_CURRENT_LIST_DIR}/data/Array.hpp
	${CMAKE_CURRENT_LIST_DIR}/data/IArray.hpp
	${CMAKE_CURRENT_LIST_DIR}/data/ISourcesCollection.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/extra/IExtrasCollection.hpp
	
	${CMAKE_CURRENT_LIST_DIR}/ElementsLibrary.hpp
	${CMAKE_CURRENT_LIST_DIR}/ICollection.hpp
	${CMAKE_CURRENT_LIST_DIR}/IElement.hpp
	${CMAKE_CURRENT_LIST_DIR}/InstancesManager.hpp
	${CMAKE_CURRENT_LIST_DIR}/IOwner.hpp
	${CMAKE_CURRENT_LIST_DIR}/IScopedElement.hpp
	${CMAKE_CURRENT_LIST_DIR}/IUniqueElement.hpp
)
