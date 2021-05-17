// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef REPORTAPI_REPORT_MERMAID_HPP
#define REPORTAPI_REPORT_MERMAID_HPP

#include <var/Stack.hpp>
#include <var/StringView.hpp>

#include "Directive.hpp"

namespace instrumentation {

class Mermaid : public DirectiveAccess<Mermaid> {
public:
  enum class Link { arrow, open, dotted, thick };

  enum class Shape {
    square,
    round,
    stadium,
    subroutine,
    cylinder,
    circle,
    asymmetric,
    rhombus,
    hexagon,
    parallelogram,
    parallelogram_alternate,
    trapezoid,
    trapezoid_alternate
  };

  class Node {
  public:
    Node() {}
    Node(const var::StringView text, Shape shape = Shape::round);

  private:
    API_RAC(Node, var::KeyString, node);
    static u32 m_count;
  };

  Mermaid() : DirectiveAccess<Mermaid>("") {  }
  Mermaid(const var::StringView line);

protected:
  void interface_parse_initialize() override final;
  void interface_parse_finalize() override final;
  void interface_parse(const Datum &datum) override final;
};

class MermaidGraph : public Mermaid {
public:
  MermaidGraph() { set_type(class_type()); }
  MermaidGraph(const var::StringView line) : Mermaid(line) {}

  class Transition {
    API_AC(Transition, Node, first);
    API_AC(Transition, Node, second);
    API_AC(Transition, var::String, message);
    API_AF(Transition, Link, link, Link::arrow);
  };

  MermaidGraph &
  set_transition(const Node &from, Link link_arrow, const Node &to,
                 const var::StringView message = var::StringView());

  Datum get_transition() const;

  static const char * class_type() {
    return "stateDiagram";
  }

protected:

private:
  u32 m_sequence_count;
  API_AC(MermaidGraph, Node, from);
  API_AC(MermaidGraph, Node, to);
  API_AC(MermaidGraph, var::KeyString, message);
  API_AF(MermaidGraph, Link, link, Link::arrow);

  static var::StringView get_link_string(Link link);
};

class CallGraph : public MermaidGraph {
public:
  CallGraph() {}
  CallGraph(const var::StringView line) : MermaidGraph(line) {}

  CallGraph &push(printer::Printer &printer, const var::StringView name);
  CallGraph &data(printer::Printer &printer, const var::StringView data);

  CallGraph &pop() {
    if (m_call_stack.count()) {
      m_call_stack.pop();
    }
    return *this;
  }

protected:

private:
  var::Stack<Mermaid::Node> m_call_stack;
  u32 m_transition_counter = 0;
};

class CallGraphNode {
public:
  CallGraphNode(printer::Printer &printer, CallGraph &graph,
                const var::StringView name)
      : m_graph(graph) {
    graph.push(printer, name);
  }

  ~CallGraphNode() { m_graph.pop(); }

private:
  CallGraph &m_graph;
};

} // namespace instrumentation

#define CALL_GRAPH_TRACE_FUNCTION(printer, graph)                              \
  report::CallGraphNode call_graph_node =                                      \
      report::CallGraphNode(printer, graph, __FUNCTION__)

#endif // REPORTAPI_REPORT_MERMAID_HPP
