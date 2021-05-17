// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef INSTRUMENTATIONAPI_INSTRUMENTATION_HISTOGRAM_HPP
#define INSTRUMENTATIONAPI_INSTRUMENTATION_HISTOGRAM_HPP

#include "Directive.hpp"

namespace instrumentation {

class Histogram : public DirectiveAccess<Histogram> {
public:
  Histogram() : DirectiveAccess<Histogram>(""){}
  Histogram(const var::StringView line);


  static const char * class_type() {
    return "hist";
  }

private:
  void interface_parse_initialize() override final;
  void interface_parse_finalize() override final;
  void interface_parse(const Datum & datum) override final;
};

} // namespace report



#endif // INSTRUMENTATIONAPI_INSTRUMENTATION_HISTOGRAM_HPP
