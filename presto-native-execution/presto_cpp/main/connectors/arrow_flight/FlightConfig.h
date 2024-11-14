#pragma once

#include "velox/common/config/Config.h"

namespace facebook::presto::connector::afc {

class FlightConfig {
 public:
  explicit FlightConfig(std::shared_ptr<const velox::config::ConfigBase> config)
      : config_{config} {}

  static constexpr const char* kAuthenticatorName =
      "arrow-flight.authenticator.name";

  static constexpr const char* kDefaultServerHost = "arrow-flight.server";

  static constexpr const char* kDefaultServerPort = "arrow-flight.server.port";

  static constexpr const char* kDefaultServerSslEnabled =
      "arrow-flight.server-ssl-enabled";

  static constexpr const char* kServerVerify = "arrow-flight.server.verify";

  static constexpr const char* kServerSslCertificate =
      "arrow-flight.server-ssl-certificate";

  std::string authenticatorName();

  std::optional<std::string> defaultServerHostname();

  std::optional<uint16_t> defaultServerPort();

  bool defaultServerSslEnabled();

  bool serverVerify();

  folly::Optional<std::string> serverSslCertificate();

 private:
  std::shared_ptr<const velox::config::ConfigBase> config_;
};

} // namespace facebook::presto::connector::afc
