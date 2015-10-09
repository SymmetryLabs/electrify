#pragma once

#define ENABLE_TEST_ACCESS()                    \
template <typename>                             \
friend class TestAccess;
