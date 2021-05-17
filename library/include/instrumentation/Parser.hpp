// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef REPORTAPI_REPORT_PARSER_HPP
#define REPORTAPI_REPORT_PARSER_HPP

#include <fs/File.hpp>
#include <var/Queue.hpp>
#include <var/StackString.hpp>
#include <var/Tokenizer.hpp>

#include "Directive.hpp"
#include "Section.hpp"

#include "Histogram.hpp"
#include "Plot.hpp"
#include "Mermaid.hpp"

namespace instrumentation {

class Parser : public api::ExecutionContext {
public:
  Parser(const fs::FileObject * input);
  Parser &create_report(const fs::FileObject &output);
  ~Parser();

private:
  var::Queue<Directive *> m_directive_list;

  template<class DirectiveType> DirectiveType * is_directive(Directive * directive){
    auto * result = reinterpret_cast<DirectiveType*>(directive);
    if( directive->type() == result->directive_type() ){
      return result;
    }
    return nullptr;
  }

  const fs::FileObject * m_input;
  fs::File::LocationScope m_location_scope;
};

} // namespace instrumentation

#endif // REPORTAPI_REPORT_PARSER_HPP
