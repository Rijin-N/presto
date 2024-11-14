// DO NOT EDIT : This file is generated by chevron
/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// presto_protocol.prolog.cpp
//

// This file is generated DO NOT EDIT @generated

#include <iostream>

#include "presto_cpp/presto_protocol/connector/arrow_flight/presto_protocol_arrow_flight.h"
using namespace std::string_literals;

// ArrowTransactionHandle is special since
// the corresponding class in Java is an enum.

namespace facebook::presto::protocol::arrow_flight {

void to_json(json& j, const ArrowTransactionHandle& p) {
  j = json::array();
  j.push_back(p._type);
  j.push_back(p.instance);
}

void from_json(const json& j, ArrowTransactionHandle& p) {
  j[0].get_to(p._type);
  j[1].get_to(p.instance);
}
} // namespace facebook::presto::protocol::arrow_flight
/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

namespace facebook::presto::protocol::arrow_flight {
ArrowColumnHandle::ArrowColumnHandle() noexcept {
  _type = "arrow-flight";
}

void to_json(json& j, const ArrowColumnHandle& p) {
  j = json::object();
  j["@type"] = "arrow-flight";
  to_json_key(
      j,
      "columnName",
      p.columnName,
      "ArrowColumnHandle",
      "String",
      "columnName");
  to_json_key(
      j, "columnType", p.columnType, "ArrowColumnHandle", "Type", "columnType");
}

void from_json(const json& j, ArrowColumnHandle& p) {
  p._type = j["@type"];
  from_json_key(
      j,
      "columnName",
      p.columnName,
      "ArrowColumnHandle",
      "String",
      "columnName");
  from_json_key(
      j, "columnType", p.columnType, "ArrowColumnHandle", "Type", "columnType");
}
} // namespace facebook::presto::protocol::arrow_flight
namespace facebook::presto::protocol::arrow_flight {
ArrowSplit::ArrowSplit() noexcept {
  _type = "arrow-flight";
}

void to_json(json& j, const ArrowSplit& p) {
  j = json::object();
  j["@type"] = "arrow-flight";
  to_json_key(
      j, "schemaName", p.schemaName, "ArrowSplit", "String", "schemaName");
  to_json_key(j, "tableName", p.tableName, "ArrowSplit", "String", "tableName");
  to_json_key(j, "ticket", p.ticket, "ArrowSplit", "String", "ticket");
  to_json_key(
      j,
      "locationUrls",
      p.locationUrls,
      "ArrowSplit",
      "List<String>",
      "locationUrls");
}

void from_json(const json& j, ArrowSplit& p) {
  p._type = j["@type"];
  from_json_key(
      j, "schemaName", p.schemaName, "ArrowSplit", "String", "schemaName");
  from_json_key(
      j, "tableName", p.tableName, "ArrowSplit", "String", "tableName");
  from_json_key(j, "ticket", p.ticket, "ArrowSplit", "String", "ticket");
  from_json_key(
      j,
      "locationUrls",
      p.locationUrls,
      "ArrowSplit",
      "List<String>",
      "locationUrls");
}
} // namespace facebook::presto::protocol::arrow_flight
namespace facebook::presto::protocol::arrow_flight {
ArrowTableHandle::ArrowTableHandle() noexcept {
  _type = "arrow-flight";
}

void to_json(json& j, const ArrowTableHandle& p) {
  j = json::object();
  j["@type"] = "arrow-flight";
  to_json_key(j, "schema", p.schema, "ArrowTableHandle", "String", "schema");
  to_json_key(j, "table", p.table, "ArrowTableHandle", "String", "table");
}

void from_json(const json& j, ArrowTableHandle& p) {
  p._type = j["@type"];
  from_json_key(j, "schema", p.schema, "ArrowTableHandle", "String", "schema");
  from_json_key(j, "table", p.table, "ArrowTableHandle", "String", "table");
}
} // namespace facebook::presto::protocol::arrow_flight
namespace facebook::presto::protocol::arrow_flight {
void to_json(json& j, const std::shared_ptr<ColumnHandle>& p) {
  if (p == nullptr) {
    return;
  }
  String type = p->_type;

  if (type == "arrow-flight") {
    j = *std::static_pointer_cast<ArrowColumnHandle>(p);
    return;
  }

  throw TypeError(type + " no abstract type ColumnHandle ");
}

void from_json(const json& j, std::shared_ptr<ColumnHandle>& p) {
  String type;
  try {
    type = p->getSubclassKey(j);
  } catch (json::parse_error& e) {
    throw ParseError(std::string(e.what()) + " ColumnHandle  ColumnHandle");
  }

  if (type == "arrow-flight") {
    std::shared_ptr<ArrowColumnHandle> k =
        std::make_shared<ArrowColumnHandle>();
    j.get_to(*k);
    p = std::static_pointer_cast<ColumnHandle>(k);
    return;
  }

  throw TypeError(type + " no abstract type ColumnHandle ");
}
} // namespace facebook::presto::protocol::arrow_flight
namespace facebook::presto::protocol::arrow_flight {
ArrowTableLayoutHandle::ArrowTableLayoutHandle() noexcept {
  _type = "arrow-flight";
}

void to_json(json& j, const ArrowTableLayoutHandle& p) {
  j = json::object();
  j["@type"] = "arrow-flight";
  to_json_key(
      j,
      "table",
      p.table,
      "ArrowTableLayoutHandle",
      "ArrowTableHandle",
      "table");
  to_json_key(
      j,
      "columnHandles",
      p.columnHandles,
      "ArrowTableLayoutHandle",
      "List<ArrowColumnHandle>",
      "columnHandles");
  to_json_key(
      j,
      "tupleDomain",
      p.tupleDomain,
      "ArrowTableLayoutHandle",
      "TupleDomain<std::shared_ptr<ColumnHandle>>",
      "tupleDomain");
}

void from_json(const json& j, ArrowTableLayoutHandle& p) {
  p._type = j["@type"];
  from_json_key(
      j,
      "table",
      p.table,
      "ArrowTableLayoutHandle",
      "ArrowTableHandle",
      "table");
  from_json_key(
      j,
      "columnHandles",
      p.columnHandles,
      "ArrowTableLayoutHandle",
      "List<ArrowColumnHandle>",
      "columnHandles");
  from_json_key(
      j,
      "tupleDomain",
      p.tupleDomain,
      "ArrowTableLayoutHandle",
      "TupleDomain<std::shared_ptr<ColumnHandle>>",
      "tupleDomain");
}
} // namespace facebook::presto::protocol::arrow_flight
