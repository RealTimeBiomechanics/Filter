#Author: Elena Ceseracciu

set(Filter_HEADERS include/vosl/Filter/Filter.h
                   include/vosl/Filter/TransferFunction.h
                   include/vosl/Filter/Polynomial.h
                   include/vosl/Filter/Designer.h)

set(Filter_TEMPLATE_IMPLEMENTATIONS include/vosl/Filter/Filter.cpp
                                    include/vosl/Filter/Polynomial.cpp
                                    include/vosl/Filter/TransferFunction.cpp
)
set_source_files_properties(${Filter_TEMPLATE_IMPLEMENTATIONS} PROPERTIES HEADER_FILE_ONLY TRUE)

source_group("Header files" FILES ${Filter_HEADERS})
source_group("Source files" FILES ${Filter_TEMPLATE_IMPLEMENTATIONS} ${Filter_SOURCES})

set(Filter_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE PATH "Include directory for Concurrency library" FORCE)
mark_as_advanced(Filter_INCLUDE_DIR)

install(FILES ${Filter_HEADERS} ${Filter_TEMPLATE_IMPLEMENTATIONS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vosl/Filter)

