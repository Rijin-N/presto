#include "Utils.h"
#include <arrow/status.h>
#include <vector>

namespace facebook::presto::connector::afc::test {

std::shared_ptr<arrow::Array> makeDecimalArray(
    const std::vector<int64_t>& decimalValues,
    int precision,
    int scale) {
  auto decimalType = arrow::decimal(precision, scale);
  auto builder =
      arrow::Decimal128Builder(decimalType, arrow::default_memory_pool());

  for (const auto& value : decimalValues) {
    arrow::Decimal128 dec(value);
    AFC_RAISE_NOT_OK(builder.Append(dec));
  }
  AFC_RETURN_OR_RAISE(builder.Finish());
}

std::shared_ptr<arrow::Array> makeTimestampArray(
    const std::vector<int64_t>& values,
    arrow::TimeUnit::type timeUnit,
    arrow::MemoryPool* memory_pool) {
  arrow::TimestampBuilder builder(arrow::timestamp(timeUnit), memory_pool);
  AFC_RAISE_NOT_OK(builder.AppendValues(values));
  AFC_RETURN_OR_RAISE(builder.Finish());
}

std::shared_ptr<arrow::Array> makeStringArray(
    const std::vector<std::string>& values) {
  auto builder = arrow::StringBuilder{};
  AFC_RAISE_NOT_OK(builder.AppendValues(values));
  AFC_RETURN_OR_RAISE(builder.Finish());
}

std::shared_ptr<arrow::Array> makeBooleanArray(
    const std::vector<bool>& values) {
  auto builder = arrow::BooleanBuilder{};
  AFC_RAISE_NOT_OK(builder.AppendValues(values));
  AFC_RETURN_OR_RAISE(builder.Finish());
}

auto makeRecordBatch(
    const std::vector<std::string>& names,
    const arrow::ArrayVector& arrays) {
  VELOX_CHECK(names.size() == arrays.size());

  auto nrows = (arrays.size() > 0) ? (arrays[0]->length()) : 0;
  for (auto& array : arrays) {
    VELOX_CHECK(array->length() == nrows);
  }

  arrow::FieldVector fields{};
  for (int i = 0; i < arrays.size(); i++) {
    VELOX_CHECK(arrays[i]->length() == nrows);
    fields.push_back(
        std::make_shared<arrow::Field>(names[i], arrays[i]->type()));
  }

  auto schema = arrow::schema(fields);
  return arrow::RecordBatch::Make(schema, nrows, arrays);
}

std::shared_ptr<arrow::Table> makeArrowTable(
    const std::vector<std::string>& names,
    const arrow::ArrayVector& arrays) {
  AFC_RETURN_OR_RAISE(
      arrow::Table::FromRecordBatches({makeRecordBatch(names, arrays)}));
}

std::string readFile(const std::string& path) {
  std::ifstream file(path);
  VELOX_CHECK(file.is_open(), "Could not open file");
  return std::string(
      (std::istreambuf_iterator<char>(file)),
      (std::istreambuf_iterator<char>()));
}

} // namespace facebook::presto::connector::afc::test
