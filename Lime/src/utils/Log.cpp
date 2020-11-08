#include "Pch.hpp"
#include "utils/Log.hpp"

// define outside class
std::shared_ptr<spdlog::logger> Log::mCoreLogger;
std::shared_ptr<spdlog::logger> Log::mClientLogger;