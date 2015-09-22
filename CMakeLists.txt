cmake_minimum_required(VERSION 3.2)
project(QtMarkup)

enable_testing()

# tell cmake to run moc automatically
set(CMAKE_AUTOMOC ON)

# Tell cmake to look for moc files
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add core Qt4 and Qt4Test
FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(Qt4Test REQUIRED)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOCSrcs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(qtmarkup main.cpp qtmarkup.cpp ${MOCSrcs})
ADD_TEST(qtmarkup qtmarkup)

TARGET_LINK_LIBRARIES(qtmarkup Qt4::QtGui Qt4::Test)
