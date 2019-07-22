project(LazyTest)

find_package(Threads)

include_directories(
    ".."
)

set(HEADER
    "lest.hpp"
    "../lazy.h"
)

set(SOURCE
    "tests.cpp"
)

add_executable(${PROJECT_NAME}
    ${SOURCE}
    ${HEADER}
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
)
