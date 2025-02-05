#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>

#include "CC3D/Core/Log.h"
#include "CC3D/Debug/Instrumentor.h"

#ifdef  CC3D_PLATFORM_WINDOWS
	#include <Windows.h>
#endif //  CC3D_PLATFORM_WINDOWS