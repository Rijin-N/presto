#include "presto_cpp/main/connectors/arrow_flight/FlightConfig.h"

namespace facebook::presto::connector::afc {

std::string FlightConfig::authenticatorName() {
  return config_->get<std::string>(kAuthenticatorName, "none");
}

std::optional<std::string> FlightConfig::defaultServerHostname() {
  return static_cast<std::optional<std::string>>(
      config_->get<std::string>(kDefaultServerHost));
}

std::optional<uint16_t> FlightConfig::defaultServerPort() {
  return static_cast<std::optional<uint16_t>>(
      config_->get<uint16_t>(kDefaultServerPort));
}

bool FlightConfig::defaultServerSslEnabled() {
  return config_->get<bool>(kDefaultServerSslEnabled, false);
}

bool FlightConfig::serverVerify() {
  return config_->get<bool>(kServerVerify, true);
}

folly::Optional<std::string> FlightConfig::serverSslCertificate() {
  return config_->get<std::string>(kServerSslCertificate);
}

} // namespace facebook::presto::connector::afc
