#pragma once

#include <vector>
#include <utility>

template<typename Signal, typename Target, typename... Args>
class ConnectionPoint {
public:
    void add_sender(Signal*);
    void add_receiver(Target*, void(Target::*)(Args...));
    void connect();

private:
	std::vector<Signal*> senders_;
	std::vector<std::pair<Target*, void (Target::*)(Args...)>> receivers_;

};

template<typename Signal, typename Target, typename... Args>
void ConnectionPoint<Signal, Target, Args...>::add_receiver(Target* t, void(Target::*m)(Args...)) {
	receivers_.push_back(std::make_pair(t, m));
	for (auto sndr : senders_)
		sndr->connect(receivers_.back().first, receivers_.back().second);
}

template<typename Signal, typename Target, typename... Args>
void ConnectionPoint<Signal, Target, Args...>::add_sender(Signal* s) {
	senders_.push_back(s);
	for (auto rcvr : receivers_)
		senders_.back()->connect(rcvr.first, rcvr.second);
}

template<typename Signal, typename Target, typename... Args>
void ConnectionPoint<Signal, Target, Args...>::connect() {
	for (auto s : senders_)
		for (auto r : receivers_)
			s->connect(r.first, r.second);
}

