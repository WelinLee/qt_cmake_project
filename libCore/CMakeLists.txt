aux_source_directory(.   DIR_SRC)


add_library(libCore ${DIR_SRC})
target_link_libraries(libCore ${QT_LIBRARIES})

