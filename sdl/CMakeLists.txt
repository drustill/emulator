add_executable(emulator main.cpp)
target_link_libraries(emulator
    PRIVATE
      libemu
      ${SDL2_LIBRARIES}
)

target_include_directories(emulator
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
  SYSTEM
    ${SDL2_INCLUDE_DIRS}
)
