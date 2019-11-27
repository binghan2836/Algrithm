


aux_source_directory(. SOURCEFILES)

add_executable(test_main ${SOURCEFILES})

TARGET_LINK_LIBRARIES(test_main gtest gmock ssl crypto)

