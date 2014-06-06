set(Filter_HEADERS  ${CMAKE_SOURCE_DIR}/lib/Polynomial.h)
set(Filter_SOURCES ${CMAKE_SOURCE_DIR})

add_executable(filter main.cpp  ${Filter_HEADERS} ${Filter_SOURCES})

#TARGET_LINK_LIBRARIES( scalerPlus#	  ${OPENSIM_LIBRARIES}
#)
