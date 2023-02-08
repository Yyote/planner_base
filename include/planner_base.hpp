#ifndef PLANNERBASE
#define PLANNERBASE

#include <iostream>
#include <map>
#include <vector>

/*
* ################################
* CLASS PROTOTYPES
* ################################
*/

template <typename functionsT> class Knobs
{
    public: 
    /*
    * Конструктор принимает перечисление функциональных переключателей,
    * а затем из него формирует вектор всех переключателей и словарь состояний.
    * ПРИНИМАЕМЫЙ ENUM ДОЛЖЕН ПЕРВЫМ ИМЕТЬ ЗНАЧЕНИЕ "FIRST", 
    * А ПОСЛЕДНИМ ЗНАЧЕНИЕМ "LAST"
    * ЗНАЧЕНИЯ ДОЛЖНЫ БЫТЬ ПОСЛЕДОВАТЕЛЬНЫ
    */
    Knobs(functionsT knobs_enum);

    /*
    * Возвращает состояние конкретного переключателя
    */
    bool knob_state(functionsT knob);

    /*
    * Выводит состояния переключаетелей
    */
    void print_functional_states();

    protected:
    /*
    * Экземпляр переключателей для установки состояний
    */
    const functionsT knobs;
    /*
    * Функция, которая задает состояние переключателя
    */
    void set_state(functionsT knob, bool state);

    private:
    /*
    * Словарь состояний хранит состояния всех переключателей.
    * По умолчанию все состояния равны false
    */
    std::map<functionsT, bool> knob_state_map;

};


template <typename functionsT, typename modesT> class ModeController 
: public Knobs<functionsT>
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
    ModeController(functionsT knobs, modesT modes, std::vector<std::vector<bool>> profiles);

    /*
    * Принимает необходимый режим и устанавливает состояния переключателей для него
    */
    void set_mode(modesT mode);

    private:
    /*
    * Словарь, хранящий профили переключателей функционала для режимов
    */
    std::map<modesT, std::vector<bool>> mode_profiles_map;
};


/*
* ################################
* DEFINITIONS
* ################################
*/


template <typename functionsT>
Knobs<functionsT>::Knobs(functionsT knobs_enum)
: knobs(knobs_enum)
{
    for(int i = functionsT::FIRST; i != functionsT::LAST; ++i)
    {
        if(i == functionsT::FIRST) continue;
        knobs_enum = static_cast<functionsT>(i);
        knob_state_map.insert(std::make_pair<functionsT, bool>(std::move(knobs_enum), false));
    }
}

template <typename functionsT>
bool Knobs<functionsT>::knob_state(functionsT knob)
{
    typename std::map<functionsT, bool>::iterator itknob_state_map;
    itknob_state_map = knob_state_map.find(knob);
    return itknob_state_map->second;
}

template <typename functionsT>
void Knobs<functionsT>::print_functional_states()
{
    for(int i = 0; i <= knob_state_map.size(); ++i)
    {
        functionsT knob = static_cast<functionsT>(i);
        if(knob != functionsT::FIRST && knob != functionsT::LAST)
        {
            std::cout << knob_state_map[knob] << " ";
        }
    }
        std::cout << std::endl;
}

template <typename functionsT>
void Knobs<functionsT>::set_state(functionsT knob, bool state)
{
    // typename std::map<functionsT, bool>::iterator itknob_state_map = knob_state_map.find(knob);
    // itknob_state_map->second = state;
    knob_state_map[knob] = state;
}


template <typename functionsT, typename modesT>
ModeController<functionsT, modesT>::ModeController(functionsT knobs, modesT modes, std::vector<std::vector<bool>> profiles)
: Knobs<functionsT>(knobs)
{
    for(int i = modesT::FIRST_; i != modesT::LAST_; ++i)
    {
        if(i == modesT::FIRST_) continue;
        modes = static_cast<modesT>(i);
        mode_profiles_map.insert(std::make_pair<modesT, std::vector<bool>>(std::move(modes), std::move(profiles.at(i - 1))));
    }
}

template <typename functionsT, typename modesT>
void ModeController<functionsT, modesT>::set_mode(modesT mode)
{
    // typename std::map<modesT, std::vector<bool>::iterator itmode_profiles_map = mode_profiles_map.find(mode);
    
    // std::vector<bool> profile = itmode_profiles_map->second;
    // std::vector<bool> profile = mode_profiles_map[mode];
    functionsT knobs_copy = Knobs<functionsT>::knobs;

    for(int i = functionsT::FIRST; i != functionsT::LAST; ++i)
    {
        if(i == functionsT::FIRST) continue;
        knobs_copy = static_cast<functionsT>(i);
        Knobs<functionsT>::set_state(knobs_copy, mode_profiles_map[mode].at(i - 1));
    }
}

#endif