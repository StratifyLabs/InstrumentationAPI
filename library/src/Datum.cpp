#include <var.hpp>
#include <printer/Printer.hpp>

#include "instrumentation/Datum.hpp"

namespace printer {
Printer &operator<<(Printer &printer, const instrumentation::Datum &a) {
  return printer.key("", "D:" | a.name() | ":" | a.value());
}
} // namespace printer

using namespace instrumentation;

Datum::Datum(const var::StringView line){
  const auto token_list = Tokenizer(line, Tokenizer::Construct().set_delimeters(":").set_maximum_delimeter_count(3));
  const auto list = token_list.list();

  if( list.count() == 3 && (list.at(0) == "D" || list.at(0) == "DATA") ){
    set_name(list.at(to_offset(Position::name)));
    set_value(list.at(to_offset(Position::value)));
  }
}
