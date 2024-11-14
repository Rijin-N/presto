#pragma once

#include "velox/exec/tests/utils/PlanBuilder.h"

namespace facebook::presto::connector::afc::test {

class FlightPlanBuilder : public velox::exec::test::PlanBuilder {
 public:
  /// @brief Add a table scan node to the Plan, using the Flight connector
  /// @param outputType The output type of the table scan node
  /// @param assignments mapping from the column aliases to real column handles
  /// @param createDefaultColumnHandles If true, generate column handles for
  /// for the columns which don't have an entry in assignments
  velox::exec::test::PlanBuilder& flightTableScan(
      velox::RowTypePtr outputType,
      std::unordered_map<
          std::string,
          std::shared_ptr<velox::connector::ColumnHandle>> assignments = {},
      bool createDefaultColumnHandles = true);
};

} // namespace facebook::presto::connector::afc::test
