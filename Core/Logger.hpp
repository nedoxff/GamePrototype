//
// Created by nedo on 12.03.2022.
//

#ifndef GAMEPROTOTYPE_LOGGER_HPP
#define GAMEPROTOTYPE_LOGGER_HPP

#ifdef DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

class Logger {
public:
	static void Initialize();
};


#endif //GAMEPROTOTYPE_LOGGER_HPP
