project(grayscaler-backend LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)

add_executable(grayscaler-backend main.cpp)
target_link_libraries(grayscaler-backend PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
