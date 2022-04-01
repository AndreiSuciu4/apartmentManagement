#pragma once
#include "Locatar.h"
#include "LocatarRepository.h"
#include <vector>
#include <string>
#include <fstream>
#include "Observer.h"
using std::string;
using std::vector;

//clasa lista de notificari
class ListaNotificari
{
private:
	vector<Locatar> lista;

public:
	/*nu permitem copierea listei
	* date de intrare:-ot-referinta la ListaNotificari
	* date de iesire
	*/
	ListaNotificari(const ListaNotificari& ot) = delete;

	/*constructor default
	* date de intrare:-
	* date de iesire:-
	*/
	ListaNotificari() = default;

	/*adauga apartament in lista
	* date de intrare:-loc-referinta la ListaNotificari
	* date de iesire:-
	* programul arunca eroare daca locatarul a mai fost introdus
	*/
	void adaugaApartament(const Locatar&);

	/*goleste lista de notificari
	* date de intrare:-
	* date de iesire:-
	*/
	void golesteLista()noexcept;

	/*returneaza toate apartamentele din lista
	* date de intrare:-
	* date de iesire:-referinta la vectorul de apartamente
	*/
	const vector<Locatar>& getAll()noexcept;

	/*returneaza numarul de apartamente din lista
	* date de intrare:-
	* date de iesire:-numarul de apartamente:-int
	*/
	int nrApartamente()noexcept;

	/*transcrie lista de apartamente in fisier
	* date de intrare::-filename-referinta la string
	* date de iesire:-
	* programul arunca exceptie daca nu a putut deschide fisierul
	*/
	void writeToFile(const string& fileName);

	/*stergere locatar
	* date de intrare:-pozitie-int
	* date de iesire:-
	*/
	void stergereApartament(const int& nr);

	/*modifica locatar in repo
	* date de intrare:-loc-referinta la Locatar
	* date de iesire:-
	*/
	void modificaApartament(const Locatar& loc);

};
