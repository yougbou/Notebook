cmake_minimum_required(VERSION 3.28)
project(Notebook)

set(CMAKE_CXX_STANDARD 17)

add_library(notebook_lib
        Note.h
        Observer.h
        CollectionObserver.h
        Collection.cpp
        Collection.h
        MainFrame.cpp
        MainFrame.h
        StorageManager.cpp
        StorageManager.h
)

target_include_directories(notebook_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Notebook main.cpp)

target_link_libraries(Notebook notebook_lib)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

add_subdirectory(test)

# Include wxWidgets configuration
include(${wxWidgets_USE_FILE})

# Link wxWidgets libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})