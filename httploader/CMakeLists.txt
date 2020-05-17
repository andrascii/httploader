set(CMAKE_CXX_STANDARD 17)

include(add_msvc_precompiled_header)
include(configure_msvc_runtime)

project(${PROJECT_NAME})

set(QTTHREADMESSAGEDISPATCHER_LIBRARY_DIR "../${QTTHREADMESSAGEDISPATCHER_LIBRARY}/${QTTHREADMESSAGEDISPATCHER_LIBRARY}")

aux_source_directory("./" HTTPLOADER_SOURCE_LIST)
file(GLOB_RECURSE HTTPLOADER_HEADER_LIST "*.h")

qt5_wrap_cpp(HTTPLOADER_MOC_HEADER_LIST ${HTTPLOADER_HEADER_LIST})
list(APPEND HTTPLOADER_SOURCE_LIST ${HTTPLOADER_MOC_HEADER_LIST})

list(REMOVE_ITEM HTTPLOADER_SOURCE_LIST stdafx.cpp)
add_msvc_precompiled_header("stdafx.h" "stdafx.cpp" HTTPLOADER_SOURCE_LIST)

configure_msvc_runtime()

source_group("Precompiled Headers" FILES stdafx.h stdafx.cpp)
source_group("MOC Files" FILES ${HTTPLOADER_MOC_HEADER_LIST})

add_definitions(${QT_DEFINITIONS})

add_executable(
    ${PROJECT_NAME}
    ${HTTPLOADER_SOURCE_LIST}
    ${HTTPLOADER_HEADER_LIST}
)

include_directories(${QTTHREADMESSAGEDISPATCHER_LIBRARY_DIR})

if(MSVC)
    add_definitions(
        /EHsc
        /MP
        /permissive-
        /std:c++latest
        /Zi
        /W4
        /WX
        -D_WINSOCK_DEPRECATED_NO_WARNINGS
    )

    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES COMPILE_FLAGS "/FI\"stdafx.h\""
        LINK_FLAGS /DEBUG
    )

    set_target_properties(
        ${PROJECT_NAME} 
        PROPERTIES WIN32_EXECUTABLE YES
        LINK_FLAGS "/DEBUG /ENTRY:mainCRTStartup /MAP"
    )
endif()

message("
    ${PROJECT_NAME}: 
    Sources: ${HTTPLOADER_SOURCE_LIST}
    Headers: ${HTTPLOADER_HEADER_LIST}
")

target_link_libraries(
    ${PROJECT_NAME}
    ${QTTHREADMESSAGEDISPATCHER_LIBRARY}
    Qt5::Core
)

if(NOT WIN32)
    include(cotire)
    set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
    cotire(${PROJECT_NAME})
endif()
