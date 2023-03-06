# PlannerBase documentation

## What is PlannerBase?

PlannerBase is a small library that is meant to simplify the implementation of operational modes. It is packaged as a shared library for C++ usage.

## Installation

For now, to install PlannerBase you have to clone the repo, put the `planner_base.hpp` into `include` folder  and `planner_base.cpp` into `src` folder of your workspace. Then configure your `CMakeLists.txt` file and add these lines:

```CMake
add_library(planner_base_lib SHARED src/planner_base.cpp include/planner_base.hpp)
  
target_include_directories(planner_base_lib
PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)
```

After that you can link the library to your executable using `target_link_libraries()`.

## Usage
0. `#include "planner_base.hpp"`
1. Create `std::vector<std::string>` type that specifies the functionalities that you want to controll with your modes. For example:
	```cpp
    std::vector<std::string> functionals
    {
        "search_for_green_markers",
        "remember_marker_coords",
        "marker_initialisation",
        "search_for_lines",
        "line_identification",
        "remember_line_coords"
    };
	```
2. Create `std::vector<string>` type that specifies the modes that you want to use. For example:
	```cpp
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
	```
3. After that you have to specify functionality profiles. They are defined as an `std::vector<bool>` that contains a value for each functionality.  For example:
	```cpp
    std::vector<std::vector<bool>> profiles;
    profiles.resize(7);
    profiles.at(0) = {0, 1, 1, 0, 1, 1};
    profiles.at(1) = {1, 1, 0, 0, 1, 1};
    profiles.at(2) = {0, 1, 0, 0, 1, 1};
    profiles.at(3) = {0, 1, 1, 1, 1, 1};
    profiles.at(4) = {0, 0, 0, 0, 1, 1};
    profiles.at(5) = {1, 1, 0, 0, 1, 0};
    profiles.at(6) = {0, 0, 0, 0, 0, 0};
	```
4. To controll the mode change or get the state of a functional knob the `ModeController` is used. You have to initialise it with your functionals, modes and profiles as follows:
	```cpp
    auto controller = ModeController(functionals, modes, profiles);
	```
1. Now your `ModeController` is initialized and you can use it for controlling your modes!

### Is there a full example of the code I can start from?

Yes, there is a `src/test_main.cpp` file which you can use as an example.

### ***ModeController***

#### bool knob_state(std::string knob)

Takes your functional string with a functional knob value that you want to check. Returns function state value bool.

#### **void print_functional_states()**

Prints current functional states.

### void set_mode(std::string mode)

Takes your mode string with a mode value that you want set. Sets the specified mode and applies the corresponding profile.
