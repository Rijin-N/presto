#pragma once

#include "arrow/api.h"
#include "presto_cpp/main/connectors/arrow_flight/Macros.h"
#include "velox/common/base/Exceptions.h"

namespace facebook::presto::connector::afc::test {

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

} // namespace facebook::presto::connector::afc::test
