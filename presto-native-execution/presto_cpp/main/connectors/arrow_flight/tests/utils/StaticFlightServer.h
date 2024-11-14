#pragma once

#include "arrow/api.h"
#include "arrow/flight/api.h"

namespace facebook::presto::connector::afc::test {

/// Test Flight server which supports DoGet operations.
/// Maintains a list of named arrow tables,
///
/// Normally, the tickets would be obtained by calling GetFlightInfo,
/// but since this is done by the coordinator this part is omitted.
/// Instead, the ticket is simply the name of the table to fetch.
class StaticFlightServer : public arrow::flight::FlightServerBase {
 public:
  explicit StaticFlightServer() {};

  void updateTable(std::string name, std::shared_ptr<arrow::Table> table) {
    tables_.emplace(std::move(name), std::move(table));
  }

  void removeTable(const std::string& name) {
    tables_.erase(name);
  }

  arrow::Status DoGet(
      const arrow::flight::ServerCallContext& context,
      const arrow::flight::Ticket& request,
      std::unique_ptr<arrow::flight::FlightDataStream>* stream) override;

 private:
  std::unordered_map<std::string, std::shared_ptr<arrow::Table>> tables_;
};

} // namespace facebook::presto::connector::afc::test
