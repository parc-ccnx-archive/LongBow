find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file(longbow.doxygen.in longbow.doxygen @ONLY)
  add_custom_target(doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/longbow.doxygen
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Running Doxygen" VERBATIM )
endif(DOXYGEN_FOUND)
