set(UTILS_LIB_NAME utils)

add_library(${UTILS_LIB_NAME} OBJECT )
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
target_sources(${UTILS_LIB_NAME} PRIVATE ${SRC_LIST})
target_include_directories(${UTILS_LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set_target_properties(${UTILS_LIB_NAME} PROPERTIES
    PUBLIC_HEADER "inc/utils_getopt_long.h"
)

install(TARGETS ${UTILS_LIB_NAME}
        PUBLIC_HEADER DESTINATION include
        COMPONENT head_file)

set(UTILS_STATIC_NAME ${UTILS_LIB_NAME}_static)
set(UTILS_SHARED_NAME ${UTILS_LIB_NAME}_shared)
add_library(${UTILS_SHARED_NAME} SHARED $<TARGET_OBJECTS:${UTILS_LIB_NAME}>)
add_library(${UTILS_STATIC_NAME} STATIC $<TARGET_OBJECTS:${UTILS_LIB_NAME}>)

set(LIB_ARRAY "${UTILS_STATIC_NAME}" "${UTILS_SHARED_NAME}")

foreach(LIB_NAME IN LISTS LIB_ARRAY)
   set_target_properties(${LIB_NAME} PROPERTIES
        COMPILE_PDB_NAME_DEBUG "${LIB_NAME}_debug"
        COMPILE_PDB_NAME_RELEASE "${LIB_NAME}_release"
        OUTPUT_NAME "${UTILS_LIB_NAME}"
    )
    set_target_properties(${LIB_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON  # 自动导出所有符号
    )
    install(
        TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib  # 静态库 (.a)
        LIBRARY DESTINATION lib  # 共享库 (.so/.dylib)
        RUNTIME DESTINATION bin  # Windows DLL
        COMPONENT ${LIB_NAME}
    )
endforeach()




