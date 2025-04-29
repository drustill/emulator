add_executable(test-emulator main.cpp)
target_link_libraries(test-emulator
    PRIVATE
      libemu
)

target_include_directories(test-emulator
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
)
