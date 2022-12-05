#include "led_controller.h"
#include "time_service.h"
#include "rainbow_animation.h"

PeriodicRoutine main_routine(1);
LedStrip<25> led_strip;
RainbowAnimation animation;

inline void mainPeriodicRoutine()
{
    animation.update(led_strip.abstractPtr());
    LedController::update(led_strip.abstractPtr());
}

int main(void)
{
    TimeService::initialize();
    LedController::initialize();

    while(1)
    {
        if (main_routine.shouldRun())
        {
            mainPeriodicRoutine();
            if (main_routine.hasElapsed())
            {
                // Spent too much time
                //while (true)
                //{ }
            }
        }
    }
}
