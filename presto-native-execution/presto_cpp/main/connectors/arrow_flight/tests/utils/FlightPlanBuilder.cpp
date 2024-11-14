#include "presto_cpp/main/connectors/arrow_flight/tests/utils/FlightPlanBuilder.h"
#include "presto_cpp/main/connectors/arrow_flight/ArrowFlightConnector.h"

namespace facebook::presto::connector::afc::test {

static const std::string kFlightConnectorId = "test-flight";

velox::exec::test::PlanBuilder& FlightPlanBuilder::flightTableScan(
    velox::RowTypePtr outputType,
    std::unordered_map<
        std::string,
        std::shared_ptr<velox::connector::ColumnHandle>> assignments,
    bool createDefaultColumnHandles) {
  if (createDefaultColumnHandles) {
    for (const auto& name : outputType->names()) {
      // provide unaliased defaults for unmapped columns
      // emplace doesn't overwrite existing entries,
      // so existing aliases are kept
      assignments.emplace(name, std::make_shared<FlightColumnHandle>(name));
    }
  }

  return startTableScan()
      .tableHandle(std::make_shared<FlightTableHandle>(kFlightConnectorId))
      .outputType(std::move(outputType))
      .assignments(std::move(assignments))
      .endTableScan();
}

} // namespace facebook::presto::connector::afc::test
