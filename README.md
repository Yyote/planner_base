# PlannerBase documentation

## What is PlannerBase?

PlannerBase is a small library that is meant to simplify the implementation of operation modes. It is packaged as a shared library for C++ usage.

## Installation

For now, to install PlannerBase you have to clone the repo, put the `planner_base.hpp` into `include` folder  and `planner_base.cpp` into `src` folder of your workspace. Then configure your `CMakeLists.txt` file and add these lines:

```CMake
add_library(planner_base_lib SHARED src/planner_base.cpp include/planner_base.hpp)
target_link_libraries(planner_base_lib protobuf)
  
target_include_directories(planner_base_lib
PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)
```

After that you can link the library to your executable using `target_link_libraries()`.

## Usage

1. Create `enum` type that specifies the functionalities that you want to controll with your modes. The first and the last element of this enum MUST be `FIRST` and `LAST`. Do not redefine element values. For example:
	```cpp
	enum functionals
	{
	FIRST,
	search_for_green_markers,
	remember_marker_coords,
	marker_initialisation,
	search_for_lines,
	line_identication,
	remember_line_coords,
	LAST
	};
	```
2. Create `enum` type that specifies the modes that you want to use. The first and the last element of this enum MUST be `FIRST_` and `LAST_`. Do not redefine element values. For example:
	```cpp
	enum modes
	{
	FIRST_,
	standing_by,
	taking_off,
	landing,
	planning,
	moving_along_line,
	moving_to_coords,
	centering_above_marker,
	LAST_
	};
	```
3. After that you have to specify functionality profiles. They are defined as an `std::vector<bool>` that contains a value for each functionality. BE CAREFUL! The functionality position in vector will be less than its enum value by 1. These profiles go in `std::vector<std::vector<bool>>` in the same order as modes are presentend in your `modes` enum. For example:
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
4. To controll the mode change or get the state of a functional knob the `ModeController` is used. You have to initialise it with your enums and profiles as follows:
	```cpp
	auto controller = ModeController<functionals, modes>(functionals(), modes(), profiles);
	```
5. Now your `ModeController` is initialized and you can use it for controlling your modes!

### ModeController

#### bool knob_state(enumT functional)

Takes your functional enum variable with a functional knob value that you want to check. Returns function state value bool.

### void print_functional_states()

Prints current functional states.

### void set_mode(enumT mode)

Takes your mode enum variable with a mode value that you want set. Sets the specified mode and applies the corresponding profile.