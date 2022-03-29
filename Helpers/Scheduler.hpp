//
// Created by nedo on 16.03.2022.
//

#ifndef GAMEPROTOTYPE_SCHEDULER_HPP
#define GAMEPROTOTYPE_SCHEDULER_HPP

#include <functional>
#include <unordered_map>
#include <SFML/System.hpp>

struct SchedulerTask
{
	std::function<void()> Callback;
	sf::Time After;
	int Id;
};

class Scheduler {
public:
	Scheduler() = default;
	void Schedule(sf::Time after, const std::function<void()>& callback);
	void Schedule(const std::function<void()>& callback);
	void Update(sf::Time delta);
private:
	std::unordered_map<int, SchedulerTask> tasks;
	unsigned long long current = 0;
};


#endif //GAMEPROTOTYPE_SCHEDULER_HPP
