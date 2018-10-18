add_executable(
        unit_tests
        test.cpp
        main.cpp)

target_link_libraries(
        unit_tests
        gtest_main
        linkedlist
)

add_test(
        NAME
        unit
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
