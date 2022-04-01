#pragma once
#include <vector>
#include <algorithm>
using std::vector;

class Observer
{
public:
	//functie pur virtuala de update
	//date de intrare:-
	//date de iesire:-
	virtual void update() = 0;
};


class Observable {
private:
	
	vector<Observer*> observers;

protected:
	//functie de modifica
	//date de intrare:-
	//date de isire:-
	void notify();

public:
	//adauga observer
	//date de intrare:-
	//date de iesire:-
	void addObserver(Observer* obs);

	//sterge observer
	//date de intrare:-
	//date de iesire:-
	void removeObserver(Observer* obs);
};
