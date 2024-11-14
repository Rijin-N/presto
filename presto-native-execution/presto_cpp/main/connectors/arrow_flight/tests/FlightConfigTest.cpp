#include "presto_cpp/main/connectors/arrow_flight/FlightConfig.h"
#include "gtest/gtest.h"

namespace facebook::presto::connector::afc::test {

TEST(FlightConfigTest, DefaultConfig) {
  auto rawConfig = std::make_shared<velox::config::ConfigBase>(
      std::move(std::unordered_map<std::string, std::string>{}));
  auto config = FlightConfig(rawConfig);
  ASSERT_EQ(config.authenticatorName(), "none");
  ASSERT_EQ(config.defaultServerHostname(), std::nullopt);
  ASSERT_EQ(config.defaultServerPort(), std::nullopt);
  ASSERT_EQ(config.defaultServerSslEnabled(), false);
  ASSERT_EQ(config.serverVerify(), true);
  ASSERT_EQ(config.serverSslCertificate(), folly::none);
}

TEST(FlightConfigTest, OverrideConfig) {
  std::unordered_map<std::string, std::string> configMap = {
      {FlightConfig::kAuthenticatorName, "my-authenticator"},
      {FlightConfig::kDefaultServerHost, "my-server-host"},
      {FlightConfig::kDefaultServerPort, "9000"},
      {FlightConfig::kDefaultServerSslEnabled, "true"},
      {FlightConfig::kServerVerify, "false"},
      {FlightConfig::kServerSslCertificate, "my-cert.crt"}};
  auto config = FlightConfig(
      std::make_shared<velox::config::ConfigBase>(std::move(configMap)));
  ASSERT_EQ(config.authenticatorName(), "my-authenticator");
  ASSERT_EQ(config.defaultServerHostname(), "my-server-host");
  ASSERT_EQ(config.defaultServerPort(), 9000);
  ASSERT_EQ(config.defaultServerSslEnabled(), true);
  ASSERT_EQ(config.serverVerify(), false);
  ASSERT_EQ(config.serverSslCertificate(), "my-cert.crt");
}

} // namespace facebook::presto::connector::afc::test
