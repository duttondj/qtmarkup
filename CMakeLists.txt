cmake_minimum_required(VERSION 3.2)
project(QtMarkup)

include(CTest)

# Enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_BUILD_TYPE Debug)


# Tell cmake to run moc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Tell cmake to look for moc files
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add core Qt4 and Qt4Test
FIND_PACKAGE(Qt4 REQUIRED QtGui QtTest)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOCSrcs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(qtmarkup main.cpp qtmarkup.cpp ${MOCSrcs})
TARGET_LINK_LIBRARIES(qtmarkup Qt4::QtGui)

ADD_EXECUTABLE(testqtmarkup testqtmarkup.cpp qtmarkup.cpp ${MOCSrcs})
TARGET_LINK_LIBRARIES(testqtmarkup Qt4::QtGui Qt4::QtTest)
ADD_TEST(NAME testqtmarkup COMMAND testqtmarkup -o testqtmarkup.log.txt)