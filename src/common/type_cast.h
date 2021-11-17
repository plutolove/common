#pragma once
#include <memory>
#include <type_traits>

#include "shared_ptr_helper.h"
namespace common {

template <typename To, typename From>
std::enable_if_t<std::is_reference_v<To>, To> type_cast(From &from) {
  try {
    if ((typeid(From) == typeid(To)) || (typeid(from) == typeid(To))) {
      return static_cast<To>(from);
    }
  } catch (const std::exception &e) {
    throw e.what();
  }
  throw std::string("bad cast from ") + typeid(From).name() +
      std::string(" to ") + typeid(To).name();
}

template <typename To, typename From>
std::enable_if_t<std::is_pointer_v<To>, To> type_cast(From *from) {
  try {
    if ((typeid(From) == typeid(std::remove_pointer_t<To>)) ||
        (from && (typeid(*from) == typeid(std::remove_pointer_t<To>)))) {
      return static_cast<To>(from);
    } else {
      return nullptr;
    }
  } catch (const std::exception &e) {
    throw e.what();
  }
  throw std::string("bad cast from ") + typeid(From).name() +
      std::string(" to ") + typeid(To).name();
}

}  // namespace common