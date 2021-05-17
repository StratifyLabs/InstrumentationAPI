#include <var.hpp>
#include <printer/Printer.hpp>

#include "instrumentation/Directive.hpp"

namespace printer {
Printer &operator<<(Printer &printer, const instrumentation::Directive &a) {
  return printer.key("", ("DIR:" | a.type() | ":" | a.data_name() | ":" | a.legend() |
                             ":" | a.title() | ":" | a.description()).string_view());
}
} // namespace printer

using namespace instrumentation;

Directive::Directive(const var::StringView line) {
  const auto token_list = Tokenizer(
      line,
      Tokenizer::Construct().set_delimeters(":").set_maximum_delimeter_count(
          m_position_count));
  const auto list = token_list.list();

  if (list.count() == m_position_count && (list.at(0) == "DIR" || list.at(0) == "DIRECTIVE")) {
    set_type(list.at(to_offset(Position::type)));
    set_data_name(list.at(to_offset(Position::data_name)));
    set_legend(list.at(to_offset(Position::legend)));
    set_title(list.at(to_offset(Position::title)));
    set_description(list.at(to_offset(Position::description)));
  }
}

void Directive::process_trace_output(const fs::FileObject &input_file) {
  GeneralString line;
  interface_parse_initialize();
  do {
    line = input_file.gets();
    const auto datum = Datum(line);
    if (datum.is_valid() && (datum.name() == data_name().string_view())) {
      interface_parse(datum);
    }
  } while (line.is_empty() == false);
  interface_parse_finalize();
}
