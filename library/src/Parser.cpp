// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <chart.hpp>
#include <fs.hpp>
#include <json.hpp>
#include <var.hpp>

#include "instrumentation/Csv.hpp"
#include "instrumentation/Flowchart.hpp"
#include "instrumentation/Histogram.hpp"
#include "instrumentation/Katex.hpp"
#include "instrumentation/Mermaid.hpp"
#include "instrumentation/MessageSequenceDiagram.hpp"
#include "instrumentation/Parser.hpp"
#include "instrumentation/Table.hpp"

using namespace instrumentation;

Parser::Parser(const fs::FileObject* input) : m_input(input), m_location_scope(*input){
  bool is_done = false;
  input->seek(0);
  do {
    const auto line = input->gets();
    const Directive directive(line);
    if (directive.is_valid()) {
      Directive * new_directive = nullptr;
      if( directive.type() == Histogram::class_type() ){
        new_directive = new Histogram(line);
      } else if( directive.type() == Plot::class_type() ){
        new_directive = new Plot(line);
      } else if( directive.type() == MermaidGraph::class_type() ){
        new_directive = new MermaidGraph(line);
      }
      if( new_directive ){
        m_directive_list.push(new_directive);
      }
    }
    is_done = line.is_empty();
  } while (is_done == false);
}

Parser::~Parser(){
  for (auto entry : m_directive_list) {
    delete entry;
  }
}

Parser &Parser::create_report(const fs::FileObject &output) {
  for( const auto entry: m_directive_list ){
    entry->set_output_type(Directive::OutputType::markdown).set_output_file(&output).process_trace_output(m_input->seek(0));
  }
  return *this;
}

