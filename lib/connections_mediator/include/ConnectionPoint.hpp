#pragma once

template<typename Signal, typename Target, typename... Args>
class ConnectionPoint {
public:
    void set_sender(Signal*);
    void set_receiver(Target*, void(Target::*)(Args...));
    void connect();

private:
    Signal* signal_;
    Target* target_;
    void (Target::*method_)(Args...);

};

