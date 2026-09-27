cmake_minimum_required(VERSION 3.19)
project(NiyaGeraAE LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(NiyaGeraAE
    main.cpp
    aethreadpool.h aethreadpool.cpp
    aetask.h aetask.cpp
    executorpooltasks.h executorpooltasks.cpp
    aetimer.h aetimer.cpp
)

target_link_libraries(NiyaGeraAE
    PRIVATE
        Qt::Core
)

install(TARGETS NiyaGeraAE
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
