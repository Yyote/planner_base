#include <iostream>
#include <string>
#include "planner_base.hpp"



int main()
{
    std::vector<std::string> functionals
    {
        "search_for_green_markers",
        "remember_marker_coords",
        "marker_initialisation",
        "search_for_lines",
        "line_identication",
        "remember_line_coords"
    };

    std::vector<std::string> modes
    {
        "standing_by",
        "taking_off",
        "landing",
        "planning",
        "moving_along_line",
        "moving_to_coords",
        "centering_above_marker"
    };
    
    std::vector<std::vector<bool>> profiles;
    profiles.resize(7);
    profiles.at(0) = {0, 1, 1, 0, 1, 1};
    profiles.at(1) = {1, 1, 0, 0, 1, 1};
    profiles.at(2) = {0, 1, 0, 0, 1, 1};
    profiles.at(3) = {0, 1, 1, 1, 1, 1};
    profiles.at(4) = {0, 0, 0, 0, 1, 1};
    profiles.at(5) = {1, 1, 0, 0, 1, 0};
    profiles.at(6) = {0, 0, 0, 0, 0, 0};
    auto controller = ModeController(functionals, modes, profiles);

    controller.set_mode("taking_off");
    std::cout << "taking_off" << std::endl;
    controller.print_functional_states();
    std::cout << std::endl;

    controller.set_mode("centering_above_marker");
    std::cout << "centering_above_marker" << std::endl;
    controller.print_functional_states();
    std::cout << std::endl;

    controller.set_mode("landing");
    std::cout << "landing" << std::endl;
    controller.print_functional_states();
    std::cout << std::endl;

    std::cout << "Pinpoint functional state -->" << " remember_marker_coords " << controller.knob_state("remember_marker_coords") << std::endl; 

    

    return 0;
}