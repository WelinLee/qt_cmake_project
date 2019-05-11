aux_source_directory(./SrcUI   DIR_UI_SRC)

qt5_wrap_ui(UIC ./SrcUI/AboutGui.ui
                                  ./SrcUI/DefaultPageWidget.ui
                                  ./SrcUI/MainWindow.ui
                                  ./SrcUI/PluginUpdateUi.ui
                                  ./SrcUI/SystemSetUi.ui
                                  ./SrcUI/TitleWidget.ui
)
qt5_add_resources(RCC qrc.qrc)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../BaseClass/)

add_executable(${PROJECT_NAME} main.cpp QSingleApplication.cpp ${DIR_LIB_SRC} ${DIR_UI_SRC} ${UIC} ${RCC})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} libCore)

