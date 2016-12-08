add_library(spira timer.cpp)

install(
  TARGETS spira
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT library
)
