add_library(linkedlist "")

target_sources(
    linkedlist
    PRIVATE
        LinkedList.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LinkedList.h
)

target_include_directories(
    linkedlist
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
