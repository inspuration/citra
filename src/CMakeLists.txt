add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(video_core)
add_subdirectory(citra)
add_subdirectory(citra_qt)

if(QT4_FOUND AND QT_QTCORE_FOUND AND QT_QTGUI_FOUND AND QT_QTOPENGL_FOUND AND NOT DISABLE_QT4)
    #add_subdirectory(citra_qt)
endif()
