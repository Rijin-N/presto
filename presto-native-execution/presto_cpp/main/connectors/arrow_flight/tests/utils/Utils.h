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
#pragma once

#include "arrow/api.h"
#include "presto_cpp/main/connectors/arrow_flight/Macros.h"
#include "velox/common/base/Exceptions.h"

namespace facebook::presto::connector::arrow_flight::test {

template <typename T>
auto makeNumericArray(const std::vector<typename T::c_type>& values) {
  auto builder = arrow::NumericBuilder<T>{};
  AFC_RAISE_NOT_OK(builder.AppendValues(values));
  AFC_RETURN_OR_RAISE(builder.Finish());
}

std::shared_ptr<arrow::Array> makeDecimalArray(
    const std::vector<int64_t>& decimalValues,
    int precision,
    int scale);

std::shared_ptr<arrow::Array> makeTimestampArray(
    const std::vector<int64_t>& values,
    arrow::TimeUnit::type timeUnit,
    arrow::MemoryPool* memory_pool = arrow::default_memory_pool());

std::shared_ptr<arrow::Array> makeStringArray(
    const std::vector<std::string>& values);

std::shared_ptr<arrow::Array> makeBooleanArray(const std::vector<bool>& values);

auto makeRecordBatch(
    const std::vector<std::string>& names,
    const arrow::ArrayVector& arrays);

std::shared_ptr<arrow::Table> makeArrowTable(
    const std::vector<std::string>& names,
    const arrow::ArrayVector& arrays);

std::string readFile(const std::string& path);

} // namespace facebook::presto::connector::arrow_flight::test