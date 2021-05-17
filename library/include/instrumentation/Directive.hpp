#ifndef INSTRUMENTATIONAPI_INSTRUMENTATION_DIRECTIVE_HPP
#define INSTRUMENTATIONAPI_INSTRUMENTATION_DIRECTIVE_HPP

#include <api/api.hpp>
#include <fs/File.hpp>
#include <var/StackString.hpp>

#include "Datum.hpp"

namespace instrumentation {

class Directive : public api::ExecutionContext {
public:
  Directive() = default;
  Directive(const var::StringView line);
  virtual ~Directive(){}

  bool is_valid() const { return !type().is_empty(); }

  bool operator==(const Directive &a) const {
    return type() == a.type() && data_name() == a.data_name() &&
           title() == a.title();
  }

  enum class OutputType {
    markdown,
    csv,
    json,
  };

  void process_trace_output(const fs::FileObject &input_file);

  static const char * class_type() {
    return "unassigned";
  }

protected:
  virtual void interface_parse_initialize(){};
  virtual void interface_parse_finalize(){};
  virtual void interface_parse(const Datum &datum) {
    MCU_UNUSED_ARGUMENT(datum);
  }

  API_ACCESS_COMPOUND(Directive, var::NameString, type);
  API_ACCESS_COMPOUND(Directive, var::IdString, data_name);
  API_ACCESS_COMPOUND(Directive, var::GeneralString, title);
  API_ACCESS_COMPOUND(Directive, var::GeneralString, legend);
  API_ACCESS_COMPOUND(Directive, var::GeneralString, description);
  API_ACCESS_FUNDAMENTAL(Directive, OutputType, output_type,
                         OutputType::markdown);
  API_ACCESS_FUNDAMENTAL(Directive, const fs::FileObject *, output_file,
                         nullptr);
  API_ACCESS_FUNDAMENTAL(Directive, u64, timestamp, 0);

private:
  enum class Position {
    directive,
    type,
    data_name,
    legend,
    title,
    description,
    last_position = description
  };

  static constexpr size_t m_position_count = static_cast<size_t>(Position::last_position) + 1;

  static constexpr size_t to_offset(Position position) {
    return static_cast<size_t>(position);
  }
};

template <class Derived> class DirectiveAccess : public Directive {
public:
  DirectiveAccess(const var::StringView line) : Directive(line) {}
  API_ACCESS_DERIVED_COMPOUND(Directive, Derived, var::NameString, type)
  API_ACCESS_DERIVED_COMPOUND(Directive, Derived, var::IdString, data_name)
  API_ACCESS_DERIVED_COMPOUND(Directive, Derived, var::GeneralString, title)
  API_ACCESS_DERIVED_COMPOUND(Directive, Derived, var::GeneralString, legend)
  API_ACCESS_DERIVED_COMPOUND(Directive, Derived, var::GeneralString,
                              description)
};

} // namespace instrumentation

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const instrumentation::Directive &a);
} // namespace printer

#endif // INSTRUMENTATIONAPI_INSTRUMENTATION_DIRECTIVE_HPP
