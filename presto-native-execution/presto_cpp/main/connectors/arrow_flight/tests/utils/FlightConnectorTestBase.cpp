#include "presto_cpp/main/connectors/arrow_flight/tests/utils/FlightConnectorTestBase.h"
#include "arrow/testing/gtest_util.h"
#include "presto_cpp/main/connectors/arrow_flight/ArrowFlightConnector.h"
#include "presto_cpp/main/connectors/arrow_flight/Macros.h"
#include "presto_cpp/main/connectors/arrow_flight/tests/utils/Utils.h"

namespace facebook::presto::connector::afc::test {

namespace connector = velox::connector;
namespace core = velox::core;

using namespace arrow::flight;
using velox::exec::test::OperatorTestBase;

void FlightConnectorTestBase::SetUp() {
  OperatorTestBase::SetUp();

  connector::registerConnectorFactory(
      std::make_shared<presto::connector::afc::ArrowFlightConnectorFactory>());
  connector::registerConnector(
      connector::getConnectorFactory(
          ArrowFlightConnectorFactory::kArrowFlightConnectorName)
          ->newConnector(kFlightConnectorId, config_));
}

void FlightConnectorTestBase::TearDown() {
  connector::unregisterConnector(kFlightConnectorId);
  OperatorTestBase::TearDown();
}

void FlightWithServerTestBase::SetUp() {
  FlightConnectorTestBase::SetUp();

  // spawn a StaticFlightServer for testing
  // initially there is no data in the Flight server,
  // tests should call FlightWithServerTestBase::updateTables to populate it
  server_ = std::make_unique<StaticFlightServer>();
  ASSERT_OK(server_->Init(*options_));
}

void FlightWithServerTestBase::TearDown() {
  ASSERT_OK(server_->Shutdown());
  FlightConnectorTestBase::TearDown();
}

std::vector<std::shared_ptr<connector::ConnectorSplit>>
FlightWithServerTestBase::makeSplits(
    std::initializer_list<std::string> tickets,
    std::vector<std::string> location) {
  std::vector<std::shared_ptr<connector::ConnectorSplit>> splits;
  splits.reserve(tickets.size());
  for (auto& ticket : tickets) {
    splits.push_back(std::make_shared<FlightSplit>(
        kFlightConnectorId, std::move(ticket), location));
  }
  return splits;
}

std::shared_ptr<FlightServerOptions>
FlightWithServerTestBase::createFlightServerOptions(
    bool isSecure,
    std::string certPath,
    std::string keyPath) {
  AFC_ASSIGN_OR_RAISE(
      auto loc,
      isSecure ? Location::ForGrpcTls("localhost", 5000)
               : Location::ForGrpcTcp("localhost", 5000));
  auto options = std::make_shared<FlightServerOptions>(loc);
  if (!isSecure)
    return options;

  CertKeyPair tlsCertificate{
      .pem_cert = readFile(certPath), .pem_key = readFile(keyPath)};
  options->tls_certificates.push_back(tlsCertificate);
  return options;
}

} // namespace facebook::presto::connector::afc::test
