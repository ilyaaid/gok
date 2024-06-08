find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

FLEX_TARGET(lexer
            lexer.flex
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)

BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser_generated.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser_generated.hpp)

add_executable(lab 
    main.cpp
    ast_tree.cpp
    driver.cpp
    lexer.yy.cc
    parser_generated.cpp
    builder.cpp

    basic_block.cpp
    function.cpp
    
)


target_compile_options(lab PRIVATE -fsanitize=address)
target_link_options(lab PRIVATE -fsanitize=address)

target_include_directories(lab
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
        ${CMAKE_CURRENT_BINARY_DIR}
)
