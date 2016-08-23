find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file(longbow.doxygen.in longbow.doxygen @ONLY)
  install(DIRECTORY images/            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)
  install(DIRECTORY doxygen-extras/    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doxygen-extras)
  install(DIRECTORY examples/          DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/examples)
  install(FILES DoxygenLayout.xml      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

  add_custom_target(documentation
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/longbow.doxygen
        COMMAND tar cf longbow-documentation.tar -C longbow-documentation/html .
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "The file longbow-documentation.tar contains the HTML website suitable to update/replace the gh-pages branch of this repository." VERBATIM )

  add_custom_target(documentation-install
	git init .
	DEPENDS documentation
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/longbow-documentation/html
	COMMAND git checkout -b gh-pages
	COMMAND git add .
	COMMAND git commit -am 'Override all previous versions'
	COMMAND git remote add origin http://githubenterprise.parc.com/CCNX/LongBow
	)

#	COMMAND "/bin/echo git commit -am 'Override all previous versions'"
#	COMMAND "/bin/echo git remote add origin http://githubenterprise.parc.com/CCNX/LongBow "
#	COMMAND "/bin/echo git push origin gh-pages -f"

endif(DOXYGEN_FOUND)
