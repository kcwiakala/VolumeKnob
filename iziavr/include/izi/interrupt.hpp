#pragma once

#include <avr/io.h>

namespace izi {
namespace isr {

struct pcint0 {};

} // namespace isr


template<typename Isr>
class InterruptHandler
{
public:
    InterruptHandler() { _instance = this; }

    static void execute() {
        if(_instance) {
            _instance->isr();
        }
    }

private:
    virtual void isr() = 0;
    static InterruptHandler* _instance;
};


} // namespace izi