#include <iostream>
#include "planner_base.hpp"

enum func_modes
{
    FIRST,
    mode1,
    mode2,
    mode3,
    LAST
};

int main()
{
    auto knobs = Knobs<func_modes>(func_modes());

    // for(int i = 0; i < knobs.knoblist.size(); ++i)
    // {
    //     std::cout << knobs.knoblist.at(i) << std::endl;
    // }

    func_modes mymode = mode1;

    std::cout << knobs.knob_state(mymode);

    return 0;
}