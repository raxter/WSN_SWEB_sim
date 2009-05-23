PROJECT(WSN_SIMULATOR)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${WSN_SIMULATOR_SOURCE_DIR} ${WSN_SIMULATOR_BINARY_DIR})

# add Qt modules here, the include will setup QT_LIBRARIES
# SET(QT_USE_QTNETWORK TRUE)
INCLUDE(${QT_USE_FILE})


# .cxx sources
SET(WSN_SIMULATOR_SRCS_CXX

  gui/wsnsim.cpp
  gui/graphics_view.cpp
  gui/graphics_scene.cpp
  
  simulator/sensor_network.cpp
  simulator/discrete_simulator.cpp
  
  simulator/base_packet.cpp
  simulator/packets/init.cpp
  simulator/packets/energy_req.cpp
  simulator/packets/data_req.cpp

  
  simulator/nodes/base_node.cpp
  
  simulator/nodes/sensor.cpp
  simulator/nodes/base_station.cpp
  
  simulator/nodes/discrete_sim.cpp
  simulator/nodes/physical_layer.cpp
  simulator/nodes/sensor_layers/layers.cpp
  simulator/nodes/sensor_layers/link.cpp
  simulator/nodes/sensor_layers/network.cpp
  simulator/nodes/base_station_layers/layers.cpp
  simulator/nodes/base_station_layers/link.cpp
  simulator/nodes/base_station_layers/network.cpp
  
  main.cpp
)

# files which need to be moc'd by Qt
SET(WSN_SIMULATOR_MOC_SRCS

  gui/wsnsim.h
  gui/graphics_view.h
  gui/graphics_scene.h
  simulator/discrete_simulator.h
  
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
