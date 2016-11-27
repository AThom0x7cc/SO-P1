#include <iostream>
#include "buffer.h"
#include "recipe.h"
#include "meal.h"
#include "cook.h"
#include "deliverer.h"
#include "waiter.h"

int main() {
    int a = 2;
    ++ a %= 3;
    printf("%d\n", a);

    Ingredient pomidor( "pomidor", 2 );
    Ingredient ananas("ananas", 3);
    Ingredient pomarancza("pomarancza", 5);
    Ingredient salata("salata", 2);
    Ingredient ogorek("ogorek", 4);
    Ingredient ser("ser", 6);
    Ingredient mieso("mieso", 10);
    Ingredient makaron("makaron", 7);
    
    std::pair<Ingredient, unsigned int> para = std::make_pair(salata, 3);
    
    Recipe r1 ("salatka", 50, { std::make_pair(salata, 3), std::make_pair(pomidor, 2), std::make_pair(pomarancza, 2), std::make_pair(ogorek, 2)});
    Recipe r2 ("pizza", 50, { std::make_pair(mieso, 1), std::make_pair(ser, 2), std::make_pair(ananas, 1)});
    Recipe r3 ("danie", 100, { std::make_pair(makaron, 1), std::make_pair(mieso, 1) } );
    
    Meal m1 (r1);
    Meal m2 (r2);
    Meal m3 (r3);
    
    Buffer <Ingredient> buff_pomidor (100);
    Buffer <Ingredient> buff_ananas (100);
    Buffer <Ingredient> buff_pomarancza (100);
    Buffer <Ingredient> buff_salata (100);
    Buffer <Ingredient> buff_ogorek (100);
    Buffer <Ingredient> buff_ser (100);
    Buffer <Ingredient> buff_mieso (100);
    Buffer <Ingredient> buff_makaron (100);
    
    Buffer <Recipe> buff_recipe (100);
    Buffer <Meal> buff_meal (100);
    Cook cook ({std::make_pair(std::ref(pomidor), std::ref(buff_pomidor)),
                std::make_pair(std::ref(ananas), std::ref(buff_ananas)),
                std::make_pair(std::ref(pomarancza), std::ref(buff_pomarancza)),
                std::make_pair(std::ref(salata), std::ref(buff_salata)),
                std::make_pair(std::ref(ogorek), std::ref(buff_ogorek)),
                std::make_pair(std::ref(ser), std::ref(buff_ser)),
                std::make_pair(std::ref(mieso), std::ref(buff_mieso)),
                std::make_pair(std::ref(makaron), std::ref(buff_makaron))}, buff_recipe, buff_meal);
    
    Deliverer deliverer ({std::make_pair(std::ref(pomidor), std::ref(buff_pomidor)),
                          std::make_pair(std::ref(ananas), std::ref(buff_ananas)),
                          std::make_pair(std::ref(pomarancza), std::ref(buff_pomarancza)),
                          std::make_pair(std::ref(salata), std::ref(buff_salata)),
                          std::make_pair(std::ref(ogorek), std::ref(buff_ogorek)),
                          std::make_pair(std::ref(ser), std::ref(buff_ser)),
                          std::make_pair(std::ref(mieso), std::ref(buff_mieso)),
                          std::make_pair(std::ref(makaron), std::ref(buff_makaron))});
    
    Waiter waiter1 ({ r1, r2, r3 }, buff_recipe);
    
    buff_recipe.produce(r1);
    buff_recipe.produce(r3);
    buff_recipe.produce(r2);
    
    std::thread t1 (&Deliverer::run, deliverer);
    std::thread t2 (&Cook::run, cook);
    std::thread t3 (&Waiter::run, waiter1);
    
    while (true)
    {
        std::cout << buff_pomidor.amount << " " << buff_ananas.amount << " " << buff_pomarancza.amount << " " << buff_salata.amount << " " << buff_ogorek.amount << " " << buff_ser.amount << " " << buff_mieso.amount << " " << buff_makaron.amount << " // " << buff_recipe.amount << " // " << buff_meal.amount << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}
