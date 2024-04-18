PROGRAM()

SRCS(
    generator.cpp
    main.cpp
    matcher.cpp
    util.cpp
)

PEERDIR(
    contrib/libs/clang16/include
    contrib/libs/clang16/lib/AST
    contrib/libs/clang16/lib/ASTMatchers
    contrib/libs/clang16/lib/Tooling
)

END()
