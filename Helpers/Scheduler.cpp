//
// Created by nedo on 16.03.2022.
//

#include "Scheduler.hpp"
#include "../Core/Logger.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <ranges>

void Scheduler::Schedule(sf::Time after, const std::function<void()> &callback) {
	SchedulerTask task;
	int id = tasks.size() + 1;
	task.Callback = callback;
	sf::Time currentTime = current > 1e7 ? sf::seconds(current / 1000.f): sf::milliseconds(current);
	task.After = after + currentTime;
	tasks[id] = task;
	SPDLOG_DEBUG("Scheduling function No.{} after {}ms (+{}ms from start)", id, task.After.asMilliseconds(), currentTime.asMilliseconds());
}

void Scheduler::Update(sf::Time delta) {
	std::unordered_map<int, SchedulerTask> completed;
	std::ranges::copy_if(tasks.begin(), tasks.end(), std::inserter(completed, completed.begin()), [=](const std::pair<int, SchedulerTask>& p){
		return p.second.After.asMilliseconds() <= current;
	});
	for(auto& p: completed)
	{
		SPDLOG_DEBUG("Function No.{} was invoked", p.first);
		p.second.Callback();
		tasks.erase(p.first);
	}

	current += delta.asMilliseconds();
}

void Scheduler::Schedule(const std::function<void()> &callback) {
	sf::Time after = tasks.empty() ? sf::milliseconds(0): std::find_if(tasks.begin(), tasks.end(), [this](const std::pair<int, SchedulerTask>& t){
		return t.first == tasks.size() + 1;
	})->second.After;

	SchedulerTask task;
	int id = tasks.size() + 1;
	task.Callback = callback;
	sf::Time currentTime = current > 1e7 ? sf::seconds(current / 1000.f): sf::milliseconds(current);
	task.After = after + currentTime;
	tasks[id] = task;
	SPDLOG_DEBUG("Scheduling function No.{} after {}ms (+{}ms from start)", id, task.After.asMilliseconds(), currentTime.asMilliseconds());
}
