#pragma once
#include "LocatarRepository.h"
#include <string>
#include <fstream>
using std::string;
class LocatarRepositoryFile : public LocatarRepository
{
private:
	string fileName;
	/*citeste din fisier
	* date de intrare:-
	* date de iesire:-
	* programul arunca eroare daca nu s-a putut deschide fisierul
	*/
	void loadFromFile();

	/*scrie in fisier
	* date de intrare:-
	* date de iesire:-
	* programul arunca eroare daca nu s-a putut deschide fisierul
	*/
	void writeToFile();
public:
	LocatarRepositoryFile(string file) :LocatarRepository(), fileName{ file }{
		fileName.append(".txt");
		std::ifstream f(fileName);
		if (f.good())
			loadFromFile();
	}
	/*adauga locatar in repo
	* date de intrare:-loc-referinta la Locatar
	* date de iesire:-
	* aplicatia arunca eroarea "locatar existent!" daca apartamentul a fost deja adaugat
	*/
	void adaugaLocatar(const Locatar& loc)override;

	/*stergere locatar
	* date de intrare:-apartament-int
	* date de iesire:-
	* programul arunca eroarea "locatar inexistent!" daca nu exista apartamentul dorit
	*/
	void stergereLocatar(const int& apartament)override;

	/*modifica locatar in repo
	* date de intrare:-loc-referinta la Locatar
	* date de iesire:-
	* aplicatia arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
	*/
	void modificareLocatar(const Locatar& loc)override;

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
	const vector<Locatar>& getAll() noexcept override;

	/*returneaza numarul de apartamente din repo
	* date de intrare:-
	* date de iesire:numarul de apartamente-int
	*/
	int getSize()const noexcept override;
};   

