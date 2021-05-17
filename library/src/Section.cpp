// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "instrumentation/Section.hpp"

using namespace instrumentation;

Section::Section() { set_prefix(generate_prefix("raw", "")); }
