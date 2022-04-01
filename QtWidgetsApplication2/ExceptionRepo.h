#pragma once
#include "Locatar.h"
#include "AbstractRepo.h"
#include "Exceptii.h"
#include <vector>
#include <map>
using std::map;
using std::vector;

class ExceptionRepo : public AbstractRepo
{
private:
	map<int, Locatar> locatari;
	double probabilitate;
	vector<Locatar> locat;
public:
	ExceptionRepo(double prob) :probabilitate{ prob } {}

	void adaugaLocatar(const Locatar& loc) override;

	/*stergere locatar
	* date de intrare:-apartament-int
	* date de iesire:-
	* programul arunca eroarea "locatar inexistent!" daca nu exista apartamentul dorit
	*/
	void stergereLocatar(const int& apartament) override;

	/*modifica locatar in repo
	* date de intrare:-loc-referinta la Locatar
	* date de iesire:-
	* aplicatia arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
	*/
	void modificareLocatar(const Locatar& loc) override;

	/*cautare apartament
	* date de intrare:-apartament-int
	* date de iesire:-referinta la Locatar
	* programul arunca eroarea "apartament inexistent" daca nu exista apartamentul in lista
	*/
	const Locatar& cautareApartament(const int& apart)const override;

	/*returneaza locatarii
	* date de intrare:-
	* date de iesire:-locatari-referinta la vector
	*/
	const vector<Locatar>& getAll()override;

	/*returneaza numarul de apartamente din repo
	* date de intrare:-
	* date de iesire:numarul de apartamente-int
	*/
	int getSize()const override;
};
