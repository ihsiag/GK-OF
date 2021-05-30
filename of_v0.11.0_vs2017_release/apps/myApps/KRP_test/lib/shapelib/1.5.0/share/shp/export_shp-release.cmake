#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "shp" for configuration "Release"
set_property(TARGET shp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(shp PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "-lm"
  IMPORTED_LOCATION_RELEASE "/usr/local/Cellar/shapelib/1.5.0/lib/libshp.1.5.0.dylib"
  IMPORTED_SONAME_RELEASE "/usr/local/Cellar/shapelib/1.5.0/lib/libshp.1.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS shp )
list(APPEND _IMPORT_CHECK_FILES_FOR_shp "/usr/local/Cellar/shapelib/1.5.0/lib/libshp.1.5.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
