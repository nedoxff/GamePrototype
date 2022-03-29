//
// Created by nedo on 12.03.2022.
//

#include "Logger.hpp"

void Logger::Initialize() {

	auto file = std::make_shared<spdlog::sinks::basic_file_sink_mt>("latest_log.txt", true);
	auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

	spdlog::sinks_init_list list = {file, console};
	auto logger = std::make_shared<spdlog::logger>("file & console", list);
	spdlog::set_default_logger(logger);
	spdlog::set_pattern("(%D %T) %^[%l / %!():%#]%$ %v");
	spdlog::set_error_handler([](const std::string &msg) {
		std::cerr << "SPDLOG_ERROR was called: " << msg << std::endl;
		throw std::runtime_error(msg);
	});
#ifdef DEBUG
	spdlog::set_level(spdlog::level::debug);
#else
	spdlog::set_level(spdlog::level::info);
#endif

	SPDLOG_INFO("Logger initialized");
}
