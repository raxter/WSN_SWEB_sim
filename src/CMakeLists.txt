PROJECT(WSN_SIMULATOR)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${WSN_SIMULATOR_SOURCE_DIR} ${WSN_SIMULATOR_BINARY_DIR})

# add Qt modules here, the include will setup QT_LIBRARIES
# SET(QT_USE_QTNETWORK TRUE)
INCLUDE(${QT_USE_FILE})


# .cxx sources
SET(WSN_SIMULATOR_SRCS_CXX

  gui/wsnsim.cpp
  
  simulator/node.cpp
  simulator/sensor_network.cpp
  
  

  main.cpp
)

# files which need to be moc'd by Qt
SET(WSN_SIMULATOR_MOC_SRCS

  gui/wsnsim.h
  
)

SET(WSN_SIMULATOR_UI
  
  gui/wsnsim.ui
)

# build ui_XXX files from the XML-style .ui files
QT4_WRAP_UI(WSN_SIMULATOR_SRCS_CXX ${WSN_SIMULATOR_UI})

# this moc's the above variable and appends to the cxx sources
QT4_WRAP_CPP(WSN_SIMULATOR_SRCS_CXX ${WSN_SIMULATOR_MOC_SRCS})

ADD_EXECUTABLE(
  wsnsim
  ${WSN_SIMULATOR_SRCS_CXX}
)

TARGET_LINK_LIBRARIES(wsnsim ${QT_LIBRARIES})