add_subdirectory(utils)

add_executable(presto_flight_connector_infra_test StaticFlightServerTest.cpp)

add_test(presto_flight_connector_infra_test presto_flight_connector_infra_test)

target_link_libraries(presto_flight_connector_infra_test
                      presto_flight_connector_test_lib gtest gtest_main glog)

add_executable(
  presto_flight_connector_test
  ArrowFlightConnectorTest.cpp ArrowFlightConnectorTlsTest.cpp
  ArrowFlightConnectorDataTypeTest.cpp FlightConfigTest.cpp)

set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

add_custom_target(
  copy_data ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${DATA_DIR}
                        $<TARGET_FILE_DIR:presto_flight_connector_test>/data)

add_test(presto_flight_connector_test presto_flight_connector_test)

target_link_libraries(
  presto_flight_connector_test velox_exec_test_lib presto_flight_connector
  gtest gtest_main presto_flight_connector_test_lib)
  
