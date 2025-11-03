//
// Created by Kirill "Raaveinm" on 11/2/25.
//

#ifndef DEQUE_EMULATOR_MODEL_H
#define DEQUE_EMULATOR_MODEL_H

#include <deque>
#include <string>

struct Model {
    using container = std::deque<std::string>;
    container items;
    container::iterator it = items.begin();
};

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

#endif //DEQUE_EMULATOR_MODEL_H