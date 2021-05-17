// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "instrumentation/Mermaid.hpp"

using namespace instrumentation;

u32 Mermaid::Node::m_count = 0;

Mermaid::Mermaid(const var::StringView line) : DirectiveAccess<Mermaid>(line) {}

void Mermaid::interface_parse_initialize() {
  switch (output_type()) {
  case OutputType::markdown:
    output_file()
        ->write(("**" | title() | "**\n\n").string_view())
        .write((description() | "\n\n").string_view())
        .write("```mermaid\n")
        .write((type() | "\n").string_view());
    break;
  case OutputType::json:
    break;
  case OutputType::csv:
    break;
  }
}

void Mermaid::interface_parse_finalize() {
  switch (output_type()) {
  case OutputType::markdown:
    output_file()->write("```\n\n");
    break;
  case OutputType::json:

    break;
  case OutputType::csv:
    break;
  }
}

void Mermaid::interface_parse(const Datum &datum) {
  switch (output_type()) {
  case OutputType::markdown:
    output_file()->write(("  " | datum.value()).string_view());
    break;
  case OutputType::json:

    break;
  case OutputType::csv:
    break;
  }
}

Mermaid::Node::Node(const var::StringView text, Shape shape) {
  switch (shape) {
  case Shape::square:
    m_node =
        var::KeyString().format("n%d[", m_count++).append(text).append("]");
    return;
  case Shape::round:
    m_node =
        var::KeyString().format("n%d(", m_count++).append(text).append(")");
    return;
  case Shape::stadium:
    m_node =
        var::KeyString().format("n%d([", m_count++).append(text).append("])");
    return;
  case Shape::subroutine:
    m_node =
        var::KeyString().format("n%d[[", m_count++).append(text).append("]]");
    return;
  case Shape::cylinder:
    m_node =
        var::KeyString().format("n%d([", m_count++).append(text).append("])");
    return;
  case Shape::circle:
    m_node =
        var::KeyString().format("n%d((", m_count++).append(text).append("))");
    return;
  case Shape::asymmetric:
    m_node =
        var::KeyString().format("n%d>", m_count++).append(text).append("]");
    return;
  case Shape::rhombus:
    m_node =
        var::KeyString().format("n%d{", m_count++).append(text).append("}");
    return;
  case Shape::hexagon:
    m_node =
        var::KeyString().format("n%d{{", m_count++).append(text).append("}}");
    return;
  case Shape::parallelogram:
    m_node =
        var::KeyString().format("n%d[/", m_count++).append(text).append("/]");
    return;
  case Shape::parallelogram_alternate:
    m_node =
        var::KeyString().format("n%d[\\", m_count++).append(text).append("\\]");
    return;
  case Shape::trapezoid:
    m_node =
        var::KeyString().format("n%d[/", m_count++).append(text).append("\\]");
    return;
  case Shape::trapezoid_alternate:
    m_node =
        var::KeyString().format("n%d[\\", m_count++).append(text).append("/]");
    return;
  }
}

var::StringView MermaidGraph::get_link_string(Link link) {
  switch (link) {
  case Link::arrow:
    return "-->";
  case Link::open:
    return " --- ";
  case Link::dotted:
    return "-.->";
  case Link::thick:
    return "==>";
  }
  return "-->";
}

MermaidGraph &MermaidGraph::set_transition(const Node &from, Link link_arrow,
                                           const Node &to,
                                           const var::StringView message) {
  return set_from(from).set_to(to).set_link(link_arrow).set_message(message);
}

Datum MermaidGraph::get_transition() const {
  return Datum().set_name(data_name()).set_value(
      var::GeneralString()
          .append(m_from.node())
          .append(get_link_string(m_link))
          .append(m_message.is_empty()
                      ? var::KeyString()
                      : (var::KeyString("|").append(m_message).append("|")))
          .append(m_to.node()));
}

CallGraph &CallGraph::push(printer::Printer &printer,
                           const var::StringView name) {
  Mermaid::Node node(name, Mermaid::Shape::round);
  if (m_call_stack.count()) {
    printer << set_transition(
        m_call_stack.top(), MermaidGraph::Link::arrow, node,
        var::NumberString(m_transition_counter++)).get_transition();
  }
  m_call_stack.push(node);
  return *this;
}

CallGraph &CallGraph::data(printer::Printer &printer,
                           const var::StringView data) {
  if (m_call_stack.count()) {
    printer << set_transition(
        m_call_stack.top(), instrumentation::MermaidGraph::Link::arrow,
        Mermaid::Node(data, Mermaid::Shape::cylinder),
        var::NumberString(m_transition_counter++)).get_transition();
  }
  return *this;
}
