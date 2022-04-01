#pragma once
#include "LocatarRepository.h"
#include "ValidareLocatar.h"
#include "ListaNotificari.h"
#include "ActiuneUndo.h"
#include "AbstractRepo.h"
#include "Observer.h"
#include <string>
#include <map>

//#include "vectorDinamicTemplate.h"
#include <functional>
#include <vector>
using std::string;
using std::function;
using std::vector;
using std::map;
using std::unique_ptr;

//clasa LocatarService
class LocatarService: public Observable
{
private:
	AbstractRepo& repo;
	ValidareLocatar& val;
	ListaNotificari& lista;
	vector<unique_ptr<ActiuneUndo>> undoActions;
public:

	/*constructor
	* date de intrare:-repo-referinta la LocatarRepository
	*				  -val-referinta la ValidareLocatar
	*				  -lista-referinta la ListaNotificari
	*/
	LocatarService(AbstractRepo& repo, ValidareLocatar& val, ListaNotificari& lista) noexcept :repo{ repo }, val{ val }, lista{ lista }{};
	/*nu permitem copierea service-ului
	* date de intrare:-ot-referinta la LocatarService
	* date de iesire:-
	*/
	LocatarService(const LocatarService& ot) = delete;

	/*constructor default
	* date de intrare:-
	* date de iesire:-
	*/
	LocatarService() = default;

	/*adauga locatar
	date de intrare: -apart-int
	*				 -nume-string
	*			     -suprafata-double
	*		         -tip-string
	* date de iesire:-
	*/
	void adaugaLocatarService(const int& apartament, const string& nume, const  double& suprafata, const string& tipApartament);

	/*stergere locatar
	* date de intrare:-apartament-int
	* date de iesire:-
	*/
	void stergereLocatarService(const int& apartament);

	/*modifica locatar
	date de intrare: -apart-int
	*				 -nume-string
	*			     -suprafata-double
	*		         -tip-string
	* date de iesire:-
	*/
	void modificaLocatarService(const int& apartament, const string& nume, const double& suprafata, const string& tipApartament);

	/*cautare apartament
	* date de intrare:-apartament-int
	* date de iesire:-locatarul dorit-referinta la Locatar
	*/
	const Locatar& cautareApartamentService(const int& apartament);

	/*returneaza toti locatarii din repo
	* date de intrare:-
	* date de iesire:-referinta la vector
	*/
	const vector<Locatar>& getAllService();

	/*functie de filtrare
	* date de intrare:-functie booleana
	* date de iesire:-rez-referinta la vector
	*/
	//vector<Locatar> filtrare(function<bool(const Locatar& loc)>fct);

	/*filtrare dupa tipul apartamentului
	* date de intrare:-tip-string
	* date de iesire:-rez-referinta la vector
	*/
	vector<Locatar> filtrareTipApartament(const string& tip);

	/*filtrare dupa auprafata apartamentului
	* date de intrare:-suprafata-int
	* date de iesire:-rez-referinta la vector
	*/
	vector<Locatar> filtrareSuprafata(const double& suprafata);

	/*functie de sortare
	* date de intrare:-functie booleana
	* date de iesire:-rez-referinta la vector
	*/
	//vector<Locatar> sortare(function<bool(const Locatar& loc, const Locatar& loc2)>fct);

	/*sortare dupa nume
	* date de intrare:-
	* date de iesire:-rez-referinta la vector
	*/
	vector<Locatar> sortareNume();

	/*sortare dupa suprafata
	* date de intrare:-
	* date de iesire:-rez-referinta la vector
	*/
	vector<Locatar> sortareSuprafata();

	/*sortare dupa tipul apartamentului si suprafata
	* date de intrare:-
	* date de iesire:-rez-referinta la vector
	*/
	vector<Locatar> sortareApartamentSuprafata();

	//lisat de notificari

	/*adauga apartament in lista
	* date de intrare:-nr-referinta la int
	* date de iesire:-
	* */
	void adaugaLista(const int& nr);

	/*goleste lista de notificari
	* date de intrare:-
	* date de iesire:-
	*/
	const void golesteLista();

	/*returneaza numarul de apartamente din lista
	* date de intrare:-
	* date de iesire:-numarul de apartamente:-int
	*/
	const int nrApartamenteLista();

	/*genereaza aleatoriu lista
	* date de intrare:-nr-referinta la intreg
	* date de iesire:-
	* programul arunca eroare daca nr<1 sayu daca nr>nr de apartamente din repo
	*/
	void genereazaLista(const int& nr);

	/*returneaza toate apartamentele din lista
	* date de intrare:-
	* date de iesire:-referinta la vectorul de apartamente
	*/
	const vector<Locatar>& getAllLista();

	/*transcrie lista de apartamente in fisier
	* date de intrare::-filename-referinta la string
	* date de iesire:-
	*/
	void writeToFile(const string& fileName);

	map<string, std::pair<string, int>>getMap();

	/*undo
	* date de intrare:-
	* date de iesire:-
	*/
	void undo();
};

