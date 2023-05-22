#pragma once

#include <machine/endian.h>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Kaleidoscope/Log.h"

#ifdef KLD_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#ifdef KLD_PLATFORM_MACOS
#endif