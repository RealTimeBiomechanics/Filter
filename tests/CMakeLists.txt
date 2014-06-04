set(Filter_HEADERS ${CMAKE_SOURCE_DIR}/lib/Filter.h)
set(Filter_SOURCES ${CMAKE_SOURCE_DIR}/lib/Filter.cpp)

add_executable(filter main.cpp  ${Filter_HEADERS} ${Filter_SOURCES})

#TARGET_LINK_LIBRARIES( scalerPlus#	  ${OPENSIM_LIBRARIES}
#)
