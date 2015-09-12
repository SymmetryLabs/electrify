#pragma once

#include <regex>

std::regex r(R"(\{
    "value0": \{
        "uuid": "[\w-]+",
        "data": \[\]
    \}
\})");
