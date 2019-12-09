


aux_source_directory(. SOURCEFILES)

add_executable(test_main ${SOURCEFILES})

TARGET_LINK_LIBRARIES(test_main algorithm gtest gmock ssl crypto)

