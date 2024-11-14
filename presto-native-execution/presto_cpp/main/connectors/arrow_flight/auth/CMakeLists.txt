add_library(presto_flight_connector_auth Authenticator.cpp)

target_link_libraries(presto_flight_connector_auth
                      presto_flight_connector_utils velox_exception)

