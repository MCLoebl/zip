# Utilized by OSSFuzz to build the harness(es) for continuous fuzz-testing
# OSSFuzz defines the following environment variables, that this target relies upon:
# CXX, CFLAGS, LIB_FUZZING_ENGINE, OUT

set(CMAKE_C_STANDARD 23)

add_definitions(-DNDEBUG)  # Do not want assertions

if (DEFINED ENV{CFLAGS})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} $ENV{CFLAGS}")
endif ()

add_executable(read_entry_fuzzer read_entry_fuzzer.c)
target_link_libraries(read_entry_fuzzer PRIVATE ${PROJECT_NAME} $ENV{LIB_FUZZING_ENGINE})

add_executable(extract_zip_fuzzer extract_zip_fuzzer.c)
target_link_libraries(extract_zip_fuzzer PRIVATE ${PROJECT_NAME} $ENV{LIB_FUZZING_ENGINE})

add_executable(stream_extract_zip_fuzzer stream_extract_zip_fuzzer.c)
target_link_libraries(stream_extract_zip_fuzzer PRIVATE ${PROJECT_NAME} $ENV{LIB_FUZZING_ENGINE})

add_executable(create_zip_fuzzer create_zip_fuzzer.c)
target_link_libraries(create_zip_fuzzer PRIVATE ${PROJECT_NAME} $ENV{LIB_FUZZING_ENGINE})

add_executable(zip_entries_delete_fuzzer zip_entries_delete_fuzzer.c)
target_link_libraries(zip_entries_delete_fuzzer PRIVATE ${PROJECT_NAME} $ENV{LIB_FUZZING_ENGINE})

if (DEFINED ENV{OUT})
    install(TARGETS read_entry_fuzzer DESTINATION $ENV{OUT})
    install(TARGETS extract_zip_fuzzer DESTINATION $ENV{OUT})
    install(TARGETS stream_extract_zip_fuzzer DESTINATION $ENV{OUT})
    install(TARGETS create_zip_fuzzer DESTINATION $ENV{OUT})
    install(TARGETS zip_entries_delete_fuzzer DESTINATION $ENV{OUT})
else ()
    message(WARNING "Cannot install if $OUT is not defined!")
endif ()
