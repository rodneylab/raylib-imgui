macro(enable_clang_tidy)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
    set(CLANG_TIDY_COMMAND
        "${CLANG_TIDY_EXE}"
        "-extra-arg=-Wno-unknown-warning-option;-extra-arg=-Wno-ignored-optimization-argument;-extra-arg=-Wno-unused-command-line-argument;-warnings-as-errors=*"
    )
endmacro()
