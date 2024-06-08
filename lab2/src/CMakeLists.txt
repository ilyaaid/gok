find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(LLVM REQUIRED CONFIG)

FLEX_TARGET(lexer
            lexer.flex
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)

BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser_generated.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser_generated.hpp)

add_definitions(${LLVM_DEFINITIONS})

add_executable(lab 
    main.cpp
    ast_tree.cpp
    driver.cpp
    lexer.yy.cc
    parser_generated.cpp
)

message("=====", ${LLVM_INCLUDE_DIRS})


target_link_libraries(lab
    PUBLIC
        LLVM
)

target_compile_options(lab PRIVATE -fsanitize=address)
target_link_options(lab PRIVATE -fsanitize=address)

target_include_directories(lab
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
        ${CMAKE_CURRENT_BINARY_DIR}
        ${LLVM_INCLUDE_DIRS}
)
