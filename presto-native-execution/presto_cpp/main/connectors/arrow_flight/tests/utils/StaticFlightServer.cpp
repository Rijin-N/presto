#include "presto_cpp/main/connectors/arrow_flight/tests/utils/StaticFlightServer.h"

namespace facebook::presto::connector::afc::test {

using namespace arrow::flight;

arrow::Status StaticFlightServer::DoGet(
    const ServerCallContext& context,
    const Ticket& request,
    std::unique_ptr<FlightDataStream>* stream) {
  auto it = tables_.find(request.ticket);
  if (it == tables_.end()) {
    return arrow::Status::KeyError("requested table does not exist");
  }
  auto& table = it->second;
  auto reader = std::make_shared<arrow::TableBatchReader>(table);
  *stream = std::make_unique<RecordBatchStream>(std::move(reader));
  return arrow::Status::OK();
}

} // namespace facebook::presto::connector::afc::test
