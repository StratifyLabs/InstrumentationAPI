// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <printer/Printer.hpp>

#include "instrumentation/Plot.hpp"


using namespace instrumentation;

Plot::Plot(const var::StringView line)
    : DirectiveAccess<Plot>(line) {}

void Plot::interface_parse_initialize() {
  switch (output_type()) {
  case OutputType::markdown:
    output_file()
        ->write((title() | "\n\n").string_view())
        .write((description() | "\n\n").string_view())
        .write("```chartjs\n");
    break;
  case OutputType::json:
    output_file()->write("{\n");
    break;
  case OutputType::csv:
    output_file()->write((data_name() | "\n").string_view());
    break;
  }
}

void Plot::interface_parse_finalize() {
  switch (output_type()) {
  case OutputType::markdown:
    output_file()->write("```\n\n");
    break;
  case OutputType::json:
    output_file()->write("\n");
    break;
  case OutputType::csv:
    output_file()->write("\n");
    break;
  }
}

void Plot::interface_parse(const Datum &datum) {
  switch (output_type()) {
  case OutputType::markdown:

    break;
  case OutputType::json:

    break;
  case OutputType::csv:
    output_file()->write((datum.value() | "\n").string_view());
    break;
  }

}
