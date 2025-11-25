cmake_minimum_required(VERSION 3.28)
project(Notebook)

set(CMAKE_CXX_STANDARD 17)

add_executable(Notebook main.cpp
        Note.h
        Observer.h
        CollectionObserver.h
        Collection.cpp
        Collection.h
        MainFrame.cpp
        MainFrame.h
        StorageManager.cpp
        StorageManager.h)


# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include wxWidgets configuration
include(${wxWidgets_USE_FILE})

# Link wxWidgets libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})