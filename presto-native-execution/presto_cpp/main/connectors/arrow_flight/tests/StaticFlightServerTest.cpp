#include "presto_cpp/main/connectors/arrow_flight/tests/utils/StaticFlightServer.h"
#include "arrow/api.h"
#include "arrow/flight/api.h"
#include "arrow/testing/gtest_util.h"
#include "glog/logging.h"
#include "gtest/gtest.h"
#include "presto_cpp/main/connectors/arrow_flight/tests/utils/Utils.h"

namespace {

using namespace facebook::presto::connector::afc::test;
using namespace arrow::flight;

class StaticFlightServerTest : public testing::Test {
 public:
  static void SetUpTestSuite() {
    server = std::make_unique<StaticFlightServer>();
    ASSERT_OK_AND_ASSIGN(auto loc, Location::ForGrpcTcp("127.0.0.1", 5000));
    ASSERT_OK(server->Init(FlightServerOptions(loc)));
  }

  static void TearDownTestSuite() {
    ASSERT_OK(server->Shutdown());
  }

  static void updateTable(
      std::string name,
      std::shared_ptr<arrow::Table> table) {
    server->updateTable(std::move(name), std::move(table));
  }

  void SetUp() {
    ASSERT_OK_AND_ASSIGN(auto loc, Location::ForGrpcTcp("localhost", 5000));
    ASSERT_OK_AND_ASSIGN(client, FlightClient::Connect(loc));
  }

  std::unique_ptr<FlightClient> client;
  static std::unique_ptr<StaticFlightServer> server;
};

std::unique_ptr<StaticFlightServer> StaticFlightServerTest::server;

TEST_F(StaticFlightServerTest, ServerTest) {
  auto sampleTable = makeArrowTable(
      {"id", "value"},
      {makeNumericArray<arrow::UInt32Type>({1, 2}),
       makeNumericArray<arrow::Int64Type>({41, 42})});
  updateTable("sample-data", sampleTable);

  ASSERT_RAISES(KeyError, client->DoGet(Ticket{"empty"}));

  auto emptyTable = makeArrowTable({}, {});
  updateTable("empty", emptyTable);

  ASSERT_RAISES(KeyError, client->DoGet(Ticket{"non-existent-table"}));

  ASSERT_OK_AND_ASSIGN(auto reader, client->DoGet(Ticket{"empty"}));
  ASSERT_OK_AND_ASSIGN(auto got, reader->ToTable());
  EXPECT_TRUE(got->Equals(*emptyTable));

  ASSERT_OK_AND_ASSIGN(reader, client->DoGet(Ticket{"sample-data"}));
  ASSERT_OK_AND_ASSIGN(got, reader->ToTable());
  EXPECT_TRUE(got->Equals(*sampleTable));

  server->removeTable("sample-data");
  ASSERT_RAISES(KeyError, client->DoGet(Ticket{"sample-data"}));
}

} // namespace
