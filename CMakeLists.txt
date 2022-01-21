cmake_minimum_required(VERSION 3.16.3)
project(GUIHomework)
include_directories(.idea)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
find_package(Qt5Widgets REQUIRED)
add_executable(GUIHomework main.cpp
        Business/Service.cpp
        Business/Service.h
        Domain/Entity.cpp
        Domain/Entity.h
        Validation/Validator.cpp
        Validation/Validator.h
        Exceptions/Exceptions.cpp
        Exceptions/Exceptions.h
        Business/UserService.cpp
        Business/UserService.h
        Persistence/STLRepository.h
        Persistence/STLRepository.cpp
        Persistence/FileRepository.cpp
        Persistence/FileRepository.h
        Persistence/CSVRepository.cpp
        Persistence/CSVRepository.h
        Persistence/HTMLRepository.cpp
        Persistence/HTMLRepository.h
        Presentation/GUI.cpp Presentation/GUI.h appCoord.cpp appCoord.h Presentation/UserGUI.cpp Presentation/UserGUI.h Persistence/UndoRedoRepo.cpp Persistence/UndoRedoRepo.h Presentation/TableModel.cpp Presentation/TableModel.h)

target_link_libraries(GUIHomework Qt5::Widgets)
