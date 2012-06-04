# Headers for the Nigel::animation namespace

SET (
	Nigel_MOC_HDRS
	${Nigel_MOC_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/Animation.hpp
	${CMAKE_CURRENT_LIST_DIR}/AnimationClip.hpp
	${CMAKE_CURRENT_LIST_DIR}/AnimationClipsLibrary.hpp
	${CMAKE_CURRENT_LIST_DIR}/AnimationInstance.hpp
	${CMAKE_CURRENT_LIST_DIR}/AnimationsLibrary.hpp
)

SET (
	Nigel_HDRS
	${Nigel_HDRS}
	
	${CMAKE_CURRENT_LIST_DIR}/IAnimationsCollection.hpp
)
