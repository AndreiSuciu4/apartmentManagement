 #pragma once
#include "Locatar.h"
#include <vector>
using std::vector;

class AbstractRepo
{
	//AbstractRepo() = default;
public:
	//virtual ~AbstractRepo() = default;
	virtual void adaugaLocatar(const Locatar& loc) = 0;

	/*stergere locatar
	* date de intrare:-apartament-int
	* date de iesire:-
	* programul arunca eroarea "locatar inexistent!" daca nu exista apartamentul dorit
	*/
	virtual void stergereLocatar(const int& apartament) = 0;

	/*modifica locatar in repo
	* date de intrare:-loc-referinta la Locatar
	* date de iesire:-
	* aplicatia arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
	*/
	virtual void modificareLocatar(const Locatar& loc) = 0;

	/*cautare apartament
	* date de intrare:-apartament-int
	* date de iesire:-referinta la Locatar
	* programul arunca eroarea "apartament inexistent" daca nu exista apartamentul in lista
	*/
	virtual const Locatar& cautareApartament(const int& apart)const = 0;

	/*returneaza locatarii
	* date de intrare:-
	* date de iesire:-locatari-referinta la vector
	*/
	virtual const vector<Locatar>& getAll() = 0;

	/*returneaza numarul de apartamente din repo
	* date de intrare:-
	* date de iesire:numarul de apartamente-int
	*/
	virtual int getSize()const = 0;

	//virtual ~AbstractRepo() = default;
};
