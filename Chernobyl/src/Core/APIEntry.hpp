#pragma once

#include "Application.hpp"

namespace CH { extern Application* CreateApplication(ApplicationStartupArguments args); }

CH::int32 main(CH::int32 argc, char* argv[]);