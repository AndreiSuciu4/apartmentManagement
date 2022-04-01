#include "Observer.h"

//functie de modifica
//date de intrare:-
//date de isire:-
void Observable::notify()
{
	for (auto obs : observers)
		obs->update();
}

//adauga observer
//date de intrare:-
//date de iesire:-
void Observable::addObserver(Observer* obs)
{
	observers.push_back(obs);
}

//sterge observer
//date de intrare:-
//date de iesire:-
void Observable::removeObserver(Observer* obs)
{
	observers.erase(std::remove(begin(observers), end(observers), obs),
		observers.end());

}

