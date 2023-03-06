#ifndef PLANNERBASE
#define PLANNERBASE

#include <iostream>
#include <map>
#include <vector>
#include <string>

/*
* ################################
* CLASS PROTOTYPES
* ################################
*/

class Knobs
{
    public: 
    /*
    * Конструктор принимает вектор строк функциональных переключателей,
    * а затем из него формирует вектор всех переключателей и словарь состояний.
    */
    Knobs(std::vector<std::string> knobs_list);

    /*
    * Возвращает состояние конкретного переключателя
    */
    bool knob_state(std::string knob);

    /*
    * Выводит состояния переключаетелей
    */
    void print_functional_states();

    protected:
    /*
    * Экземпляр переключателей для установки состояний
    */
    const std::vector<std::string> knobs;
    /*
    * Функция, которая задает состояние переключателя
    */
    void set_state(std::string knob, bool state);

    private:
    /*
    * Словарь состояний хранит состояния всех переключателей.
    * По умолчанию все состояния равны false
    */
    std::map<std::string, bool> knob_state_map;

};


class ModeController 
: public Knobs
{
    public:
    /*
    * Первым аргументом принимает перечисление функциональных переключателей,
    * а затем из него формирует вектор всех переключателей и словарь состояний.
    * 
    * Вторым аргументом принимает перечисление режимов.
    * 
    * Третьим аргументом принимает вектор< вектор<bool> >, где каждый
    * вектор<bool> является вектором состояний функциональных переключателей
    * в режиме, к которому будет привязан.
    * 
    * ПЕРВЫЙ ПРИНИМАЕМЫЙ ENUM ДОЛЖЕН ПЕРВЫМ ИМЕТЬ ЗНАЧЕНИЕ "FIRST", 
    * А ПОСЛЕДНИМ ЗНАЧЕНИЕМ "LAST"
    * 
    * ВТОРОЙ ПРИНИМАЕМЫЙ ENUM ДОЛЖЕН ПЕРВЫМ ИМЕТЬ ЗНАЧЕНИЕ "FIRST_", 
    * А ПОСЛЕДНИМ ЗНАЧЕНИЕМ "LAST_"
    * 
    * Это значит, что первый реальный элемент функционала будет иметь значение 1,
    * а его профиль вектор будет иметь положение 0. И так для каждого элемента.
    */
    ModeController(std::vector<std::string> knobs, std::vector<std::string> modes, std::vector<std::vector<bool>> profiles);

    /*
    * Принимает необходимый режим и устанавливает состояния переключателей для него
    */
    void set_mode(std::string mode);

    private:
    /*
    * Словарь, хранящий профили переключателей функционала для режимов
    */
    std::map<std::string, std::vector<bool>> mode_profiles_map;
};


/*
* ################################
* DEFINITIONS
* ################################
*/


Knobs::Knobs(std::vector<std::string> knobs_list)
: knobs(knobs_list)
{
    for(int i = 0; i < knobs_list.size(); ++i)
    {
        knob_state_map.insert(std::make_pair<std::string, bool>(std::move(knobs_list.at(i)), false));
    }
}

bool Knobs::knob_state(std::string knob)
{
    std::map<std::string, bool>::iterator itknob_state_map;
    // DEBUG: NO NOT FOUND VALUE
    itknob_state_map = knob_state_map.find(knob);
    return itknob_state_map->second;
}

void Knobs::print_functional_states()
{
    for(int i = 0; i < knob_state_map.size(); ++i)
    {
        std::string knob = knobs.at(i);
        std::cout << knob_state_map[knob] << " ";
    }
        std::cout << std::endl;
}

void Knobs::set_state(std::string knob, bool state)
{
    // typename std::map<std::vector<std::string>, bool>::iterator itknob_state_map = knob_state_map.find(knob);
    // itknob_state_map->second = state;
    knob_state_map[knob] = state;
}


ModeController::ModeController(std::vector<std::string> knobs, std::vector<std::string> modes, std::vector<std::vector<bool>> profiles)
: Knobs(knobs)
{
    for(int i = 0; i < modes.size(); ++i)
    {
        mode_profiles_map.insert(std::make_pair<std::string, std::vector<bool>>(std::move(modes.at(i)), std::move(profiles.at(i))));
    }
}

void ModeController::set_mode(std::string mode)
{
    std::vector<std::string> knobs_copy = Knobs::knobs;

    for(int i = 0; i < knobs.size(); ++i)
    {
        knobs_copy = static_cast<std::vector<std::string>>(i);
        Knobs::set_state(knobs.at(i), mode_profiles_map[mode].at(i));
    }
}

#endif