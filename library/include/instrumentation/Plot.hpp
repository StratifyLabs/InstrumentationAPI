// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef INSTRUMENTATIONAPI_INSTRUMENTATION_PLOT_HPP
#define INSTRUMENTATIONAPI_INSTRUMENTATION_PLOT_HPP

#include "Directive.hpp"

namespace instrumentation {

class Plot : public DirectiveAccess<Plot> {
public:
  Plot() : DirectiveAccess<Plot>(""){}
  Plot(const var::StringView line);

  static const char * class_type() {
    return "plot";
  }

private:
  void interface_parse_initialize() override final;
  void interface_parse_finalize() override final;
  void interface_parse(const Datum & datum) override final;
};

} // namespace report



#endif // INSTRUMENTATIONAPI_INSTRUMENTATION_PLOT_HPP
