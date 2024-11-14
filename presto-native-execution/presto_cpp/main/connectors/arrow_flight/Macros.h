#pragma once

#include "velox/common/base/Exceptions.h"

// macros for dealing with arrow::Status and arrow::Result objects
// and converting them to velox exceptions

/// Raise a Velox exception if status is not OK.
/// Counterpart of ARROW_RETURN_NOT_OK
#define AFC_RAISE_NOT_OK(status)                                      \
  do {                                                                \
    ::arrow::Status __s = ::arrow::internal::GenericToStatus(status); \
    VELOX_CHECK(__s.ok(), __s.message());                             \
  } while (false)

#define AFC_ASSIGN_OR_RAISE_IMPL(result_name, lhs, rexpr)            \
  auto&& result_name = (rexpr);                                      \
  VELOX_CHECK((result_name).ok(), (result_name).status().message()); \
  lhs = std::move(result_name).ValueUnsafe();

/// Raise a Velox exception if expr doesn't return an OK result,
/// else unwrap the value and assign it to `lhs`.
/// `std::move`s its right hand operand.
/// Counterpart of ARROW_ASSIGN_OR_RAISE
#define AFC_ASSIGN_OR_RAISE(lhs, rexpr) \
  AFC_ASSIGN_OR_RAISE_IMPL(             \
      ARROW_ASSIGN_OR_RAISE_NAME(_error_or_value, __COUNTER__), lhs, rexpr);

/// Raise a Velox exception if epr doesn't return an OK result,
/// else unwrap the value and return it.
/// `std::move`s its right hand operand.
#define AFC_RETURN_OR_RAISE(rexpr)                 \
  do {                                             \
    auto&& __r = (rexpr);                          \
    VELOX_CHECK(__r.ok(), __r.status().message()); \
    return std::move(__r).ValueUnsafe();           \
  } while (false)
