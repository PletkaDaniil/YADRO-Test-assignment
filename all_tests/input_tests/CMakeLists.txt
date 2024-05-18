file(GLOB txt_files "*.txt")
foreach(file ${txt_files})
    file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
