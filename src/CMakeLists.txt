file(GLOB_RECURSE SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(libemu STATIC ${SRCS})
target_include_directories(libemu
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
