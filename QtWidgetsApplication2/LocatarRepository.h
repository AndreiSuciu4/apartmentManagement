#pragma once
#include "Locatar.h"
#include "LocatarRepository.h"
#include <vector>
#include "AbstractRepo.h"
using std::vector;
//#include "vectorDinamicTemplate.h"
class AbstractRepo;

//clasa LocatarRepository
class LocatarRepository : public AbstractRepo
{
private:
	vector<Locatar> locatari;

public:

	/*nu permitem copierea repozitoriului in aplicatie
	* date de intrare:ot-referire la LocatarRepository
	* date de iesire:-
	*/
	LocatarRepository(const LocatarRepository& ot) = delete;

	/*constructor default
	* date de intrare:-
	* date de iesire:-
	*/
	LocatarRepository() = default;

	/*adauga locatar in repo
	* date de intrare:-loc-referinta la Locatar
	* date de iesire:-
	* aplicatia arunca eroarea "locatar existent!" daca apartamentul a fost deja adaugat
	*/
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
	const Locatar& cautareApartament(const int& apart)const;

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


