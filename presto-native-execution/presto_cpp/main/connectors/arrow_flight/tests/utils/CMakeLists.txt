add_library(
  presto_flight_connector_test_lib
  StaticFlightServer.cpp FlightConnectorTestBase.cpp Utils.cpp
  FlightPlanBuilder.cpp)

target_link_libraries(
  presto_flight_connector_test_lib arrow ${ArrowFlight_LIBRARIES}
  velox_exception presto_flight_connector_utils velox_exec_test_lib)
