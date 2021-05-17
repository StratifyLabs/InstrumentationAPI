#ifndef INSTRUMENTATIONAPI_INSTRUMENTATION_DATUM_HPP
#define INSTRUMENTATIONAPI_INSTRUMENTATION_DATUM_HPP


#include <api/api.hpp>
#include <var/StackString.hpp>
#include <var/Array.hpp>

namespace instrumentation {


class Datum : public api::ExecutionContext {
public:
  Datum() = default;
  Datum(const var::StringView line);

  bool is_valid() const {
    return name().is_empty() == false;
  }

  var::GeneralString to_string() const {
    return "D:" | name() | ":" | value();
  }

private:

  enum class Position {
    data,
    name,
    value
  };

  static constexpr size_t to_offset(Position position){
    return static_cast<size_t>(position);
  }

  API_AC(Datum, var::IdString, name);
  API_AC(Datum, var::GeneralString, value);
  API_AF(Datum, u64, timestamp, 0);
};

}

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const instrumentation::Datum &a);
} // namespace printer

#endif // INSTRUMENTATIONAPI_INSTRUMENTATION_DATUM_HPP
