// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <printer/Printer.hpp>

#include "instrumentation/Csv.hpp"

namespace printer {
class Printer;

Printer &operator<<(Printer &printer, const instrumentation::Csv &a) {
  printer.array(a.prefix(), a.row());
  return printer;
}

} // namespace printer

using namespace instrumentation;

Csv::Csv(
  printer::Printer &printer,
  const var::StringView name,
  const var::StringViewList &header_list) {
  set_prefix(generate_prefix(get_class_type(), name));
  printer.array(prefix(), header_list);
}
