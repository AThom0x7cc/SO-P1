#ifndef recipe_h
#define recipe_h
#include "ingredient.h"
#include <vector>
class Recipe
{
public:
    std::string name;
    unsigned int price;
    std::vector < std::pair < Ingredient, unsigned int > > ingredients;
    Recipe ( const std::string & name, const unsigned int price, std::initializer_list < std::pair < Ingredient, unsigned int > > init )
    : name { name },
    price { price }
    {
         for ( auto i = init.begin() ; i != init.end() ; ++ i )
             ingredients.push_back(*i);
    }
    Recipe& operator = ( const Recipe& r )
    {
        if (&r == this)
            return *this;
        name = r.name;
        price = r.price;
        for( auto i : r.ingredients )
            ingredients.push_back(i);
        return *this;
    }
    
};

#endif /* recipe_h */
