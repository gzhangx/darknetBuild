#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Darknet::dark" for configuration "Debug"
set_property(TARGET Darknet::dark APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Darknet::dark PROPERTIES
  IMPORTED_IMPLIB_DEBUG "D:/work/cur/dark/darknet/darknetd.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "CuDNN::CuDNN"
  IMPORTED_LOCATION_DEBUG "D:/work/cur/dark/darknet/darknetd.dll"
  )

list(APPEND _cmake_import_check_targets Darknet::dark )
list(APPEND _cmake_import_check_files_for_Darknet::dark "D:/work/cur/dark/darknet/darknetd.lib" "D:/work/cur/dark/darknet/darknetd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
