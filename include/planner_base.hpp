#ifndef PLANNERBASE
#define PLANNERBASE

#include <iostream>
#include <map>
#include <vector>

/*
* CLASS PROTOTYPES
*/

template <typename functionsT> class Knobs
{
    public: 
    /*
    * Конструктор принимает перечисление функциональных переключателей,
    * а затем из него формирует вектор всех переключателей и словарь состояний.
    * ПРИНИМАЕМЫЙ ENUM ДОЛЖЕН ПЕРВЫМ ИМЕТЬ ЗНАЧЕНИЕ "FIRST", 
    * А ПОСЛЕДНИМ ЗНАЧЕНИЕМ "LAST"
    */
    Knobs(functionsT knobs_enum);

    /*
    * Возвращает состояние конкретного переключателя
    */
    bool knob_state(functionsT knob);

    protected:
    /*
    * Функция, которая определяет состояние переключателя
    */
    void set_state(functionsT knob, bool state);

    private:
    /*
    * Словарь состояний хранит состояния всех переключателей.
    * По умолчанию все состояния равны false
    */
    std::map<functionsT, bool> knob_state_map;

};


template <typename functionsT, typename modesT> class ModeController : public Knobs<functionsT>
{
    public:
    ModeController(functionsT knobs, modesT modes);
};


/*
* DEFINITIONS
*/


template <typename functionsT>
Knobs<functionsT>::Knobs(functionsT knobs_enum)
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
void Knobs<functionsT>::set_state(functionsT knob, bool state)
{
    typename std::map<functionsT, bool>::iterator itknob_state_map = knob_state_map.find(knob);
    itknob_state_map->second = state;
}

#endif