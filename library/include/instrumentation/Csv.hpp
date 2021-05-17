// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef REPORTAPI_REPORT_CSV_HPP
#define REPORTAPI_REPORT_CSV_HPP

#include "Section.hpp"

namespace instrumentation {

class Csv : public Section {
public:
  Csv() {} // used as a placeholder

  Csv(
    printer::Printer &printer,
    const var::StringView name,
    const var::StringViewList &header_list);

  static var::StringView get_class_type() { return "csv"; }

  Csv &set_row(var::StringViewList &&value) {
    m_row = std::move(value);
    return *this;
  }

private:
  API_AC(Csv, var::StringViewList, row);
};

} // namespace report

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const instrumentation::Csv &a);
} // namespace printer

#endif // REPORTAPI_REPORT_CSV_HPP
