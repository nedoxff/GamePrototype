//
// Created by nedo on 24.03.2022.
//

#include "WindowsHelper.hpp"
#include "../Core/Logger.hpp"

#include <Windows.h>
#include <VersionHelpers.h>

std::pair<sf::Vector2i, sf::Vector2i> WindowsHelper::GetPrimaryMonitorSize() {
	SPDLOG_DEBUG("Getting monitor information");

	auto monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFOEX info;
	info.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(monitor, &info);

	sf::Vector2i monitorSize = {info.rcMonitor.right - info.rcMonitor.left, info.rcMonitor.bottom - info.rcMonitor.top};
	sf::Vector2i workSize = {info.rcWork.right - info.rcMonitor.left, info.rcWork.bottom - info.rcWork.top};
	SPDLOG_DEBUG("Monitor name: {} | Monitor size: {}x{} | Work area size: {}x{}", info.szDevice, monitorSize.x, monitorSize.y, workSize.x, workSize.y);

	return {monitorSize, workSize};
}

void WindowsHelper::ShowTaskBar(bool show) {
	auto hShellWnd = FindWindow("Shell_TrayWnd", nullptr);
	ShowWindow(hShellWnd, show ? SW_SHOW: SW_HIDE);
}

void WindowsHelper::OnStartup() {
	if(!IsWindows7OrGreater()) {
		MessageBox(nullptr,
		           "Sorry, this game is only supported on Windows 7 and newer. Please upgrade.\nIf this is a false positive, feel free to contact me at nedoprogrammer0xff@gmail.com",
		           "Uh oh!", MB_ICONERROR);
		std::exit(0);
	}

	auto size = GetPrimaryMonitorSize();
	if(size.first.x < 1366 || size.first.y < 768)
	{
		MessageBox(nullptr, "Sorry, this game requires at least a 1366x768 monitor.\nIf this is a false positive, feel free to contact me at nedoprogrammer0xff@gmail.com",
				   "Uh oh!", MB_ICONERROR);
		std::exit(0);
	}
}

void WindowsHelper::OnShutdown() {
	//TODO
}