// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "instrumentation/MessageSequenceDiagram.hpp"

namespace printer {
class Printer;

Printer &operator<<(Printer &printer, const instrumentation::MessageSequenceDiagram &a) {
  printer.object(a.prefix(), a.value());
  return printer;
}
} // namespace printer

using namespace instrumentation;

MessageSequenceDiagram::MessageSequenceDiagram(
  printer::Printer &printer,
  const var::StringView name) {
  set_prefix(generate_prefix(get_class_type(), name));
  printer.object(prefix(), var::StringView("sequenceDiagram"));
}
