#Author: Elena Ceseracciu

set(Filter_HEADERS vosl/Filter/Filter.h
                   vosl/Filter/TransferFunction.h
                   vosl/Filter/Polynomial.h
                   vosl/Filter/Designer.h)

set(Filter_TEMPLATE_IMPLEMENTATIONS vosl/Filter/Filter.cpp
                                    vosl/Filter/Polynomial.cpp
                                    vosl/Filter/TransferFunction.cpp
)
set_source_files_properties(${Filter_TEMPLATE_IMPLEMENTATIONS} PROPERTIES HEADER_FILE_ONLY TRUE)

source_group("Header files" FILES ${Filter_HEADERS})
source_group("Source files" FILES ${Filter_TEMPLATE_IMPLEMENTATIONS} ${Filter_SOURCES})
include_directories(include)
add_library(Filter ${Filter_HEADERS} ${Filter_TEMPLATE_IMPLEMENTATIONS} ${Filter_SOURCES} )
set(Filter_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Include directory for Filter library" FORCE)
mark_as_advanced(Filter_INCLUDE_DIRS)

install(FILES ${Filter_HEADERS} ${Filter_TEMPLATE_IMPLEMENTATIONS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vosl/Filter)

