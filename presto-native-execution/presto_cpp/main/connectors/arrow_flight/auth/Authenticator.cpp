#include "presto_cpp/main/connectors/arrow_flight/auth/Authenticator.h"
#include "velox/common/base/Exceptions.h"

namespace facebook::presto::connector::afc::auth {

static auto& authenticatorFactories() {
  static std::unordered_map<std::string, std::shared_ptr<AuthenticatorFactory>>
      factories;
  return factories;
}

bool registerAuthenticatorFactory(
    std::shared_ptr<AuthenticatorFactory> factory) {
  bool ok = authenticatorFactories().insert({factory->name(), factory}).second;
  VELOX_CHECK(
      ok,
      "Flight AuthenticatorFactory with name {} is already registered",
      factory->name());
  return true;
}

std::shared_ptr<AuthenticatorFactory> getAuthenticatorFactory(
    const std::string& name) {
  auto it = authenticatorFactories().find(name);
  VELOX_CHECK(
      it != authenticatorFactories().end(),
      "Flight AuthenticatorFactory with name {} not registered",
      name);
  return it->second;
}

AFC_REGISTER_AUTH_FACTORY(std::make_shared<NoOpAuthenticatorFactory>())

} // namespace facebook::presto::connector::afc::auth
