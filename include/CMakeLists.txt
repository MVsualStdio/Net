set(DIR_SRC_LIST)
file(GLOB DIR_SRC_LIST ${PROJECT_SOURCE_DIR}/include/*)
add_subdirectory(Heap)
add_subdirectory(Logger)
add_subdirectory(Queue)
add_subdirectory(Task)
add_subdirectory(ThreadPool)
add_subdirectory(Socket)
add_subdirectory(Buffer)
add_subdirectory(Http)