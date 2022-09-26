file(GLOB_RECURSE TEST_SRC_LIST ${PROJECT_SOURCE_DIR}/test)

foreach(test ${DIR_SRC_LIST})    
    MESSAGE(STATUS ${test})
endforeach()

set(TSET_LIB testThread testSocket testLogger testHttp)

foreach(test ${TSET_LIB})
    message("Lib build: ${test}")
    add_executable(${test} ./${test}.cc)
    target_link_libraries(${test} ${NET_LIB})
endforeach()







