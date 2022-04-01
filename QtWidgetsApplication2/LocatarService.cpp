#include "LocatarService.h"
#include "Exceptii.h"
#include <iostream>
#include <algorithm>
#include <random> 
#include <chrono> 


/*adauga locatar
date de intrare: -apart-int
*				 -nume-string
*			     -suprafata-double
*		         -tip-string
* date de iesire:-
*/
void LocatarService::adaugaLocatarService(const int& apartament, const string& nume, const double& suprafata, const string& tipApartament) {
	Locatar loc{ apartament,nume,suprafata,tipApartament };
	val.valideazaLocatar(loc);
	repo.adaugaLocatar(loc);
	notify();
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, loc));
}

/*stergere locatar
* date de intrare:-apartament-int
* date de iesire:-
*/
void LocatarService::stergereLocatarService(const int& apartament)
{
	const Locatar& loc = repo.cautareApartament(apartament);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, loc));
	repo.stergereLocatar(apartament);
	lista.stergereApartament(apartament);
	notify();
}

/*modifica locatar
date de intrare: -apart-int
*				 -nume-string
*			     -suprafata-double
*		         -tip-string
* date de iesire:-
*/
void LocatarService::modificaLocatarService(const int& apartament, const string& nume, const double& suprafata, const string& tipApartament)
{
	Locatar loc{ apartament,nume,suprafata,tipApartament };
	val.valideazaLocatar(loc);
	Locatar loc1 = repo.cautareApartament(apartament);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, loc1));
	repo.modificareLocatar(loc);
	lista.modificaApartament(loc);
	notify();
}

/*cautare apartament
* date de intrare:-apartament-int
* date de iesire:-locatarul dorit-referinta la locatar
*/

const Locatar& LocatarService::cautareApartamentService(const int& apartament)
{
	return repo.cautareApartament(apartament);
}

/*returneaza toti locatarii din repo
* date de intrare:-
* date de iesire:-locatarii-referinta la VectorDinamic
*/
const vector<Locatar>& LocatarService::getAllService() {
	return repo.getAll();
}

/*functie de filtrare
* date de intrare:-functie booleana
* date de iesire:-rez-referinta la VectorDinamic

vector<Locatar> LocatarService::filtrare(function<bool(const Locatar& loc)> fct)
{
	vector<Locatar> rez;
	const vector<Locatar>& locatari = repo.getAll();
	for (int i=0; i<locatari.size();i++)
		if (fct(locatari.at(i)))
			rez.push_back(locatari.at(i));
	return rez;
}
*/
/*filtrare dupa tipul apartamentului
* date de intrare:-tip-string
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::filtrareTipApartament(const string& tip)
{
	vector<Locatar> rez;
	const vector<Locatar>& locatari = repo.getAll();
	std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(rez), [&](const Locatar& l) {return l.getTipApartament() == tip; });
	return rez;
}

/*filtrare dupa auprafata apartamentului
* date de intrare:-suprafata-int
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::filtrareSuprafata(const double& suprafata)
{
	vector<Locatar> rez;
	const vector<Locatar>& locatari = repo.getAll();
	std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(rez), [&](const Locatar& l) {return l.getSuprafata() <= suprafata; });
	return rez;
}

/*functie de sortare
* date de intrare:-functie booleana
* date de iesire:-rez-referinta la VectorDinamic

vectorDinamic<Locatar> LocatarService::sortare(function<bool(const Locatar& loc1, const Locatar& loc2)> fct)
{
	vectorDinamic<Locatar> rez{ repo.getAll() };
	for(int i{0};i<rez.size();i++)
		for(int j{0};j<rez.size();j++)
			if (fct(rez.at(i), rez.at(j)))
			{
				Locatar aux = rez.at(i);
				rez.set(rez.at(j), i);
				rez.set(aux, j);
			}
	return rez;
}
*/

/*sortare dupa nume
* date de intrare:-
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::sortareNume()
{
	vector<Locatar> rez{ repo.getAll() };
	std::sort(rez.begin(), rez.end(), [](const Locatar& loc1, const Locatar& loc2) {return loc1.getNume() <= loc2.getNume(); });
	return rez;
}

/*sortare dupa suprafata
* date de intrare:-
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::sortareSuprafata()
{
	vector<Locatar> rez{ repo.getAll() };
	std::sort(rez.begin(), rez.end(), [](const Locatar& loc1, const Locatar& loc2) {return loc1.getSuprafata() <= loc2.getSuprafata(); });
	return rez;
}

/*sortare dupa tipul apartamentului si suprafata
* date de intrare:-
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::sortareApartamentSuprafata()
{
	vector<Locatar> rez{ repo.getAll() };
	std::sort(rez.begin(), rez.end(), [](const Locatar& loc1, const Locatar& loc2) {
		if (loc1.getTipApartament() < loc2.getTipApartament())
			return true;
		if (loc1.getTipApartament() == loc2.getTipApartament() && loc1.getSuprafata() <= loc2.getSuprafata())
			return true;
		else
			return false;	});
	return rez;
}

/*adauga apartament in lista
* date de intrare:-nr-referinta la int
* date de iesire:-
* */
void LocatarService::adaugaLista(const int& nr)
{
	const Locatar& loc = repo.cautareApartament(nr);
	lista.adaugaApartament(loc);
	notify();
}

/*goleste lista de notificari
* date de intrare:-
* date de iesire:-
*/
const void LocatarService::golesteLista()
{
	lista.golesteLista();
	notify();
}

/*returneaza numarul de apartamente din lista
* date de intrare:-
* date de iesire:-numarul de apartamente:-int
*/
const int LocatarService::nrApartamenteLista()
{
	return lista.nrApartamente();
}

/*genereaza aleatoriu lista
* date de intrare:-nr-referinta la intreg
* date de iesire:-
* programul arunca eroare daca nr<1 sayu daca nr>nr de apartamente din repo
*/
void LocatarService::genereazaLista(const int& nr)
{
	if (nr > repo.getSize() || nr < 1)
		throw listaException("numar de apartamente invalid!\n");
	lista.golesteLista();
	vector<Locatar> rez = repo.getAll();
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(rez.begin(), rez.end(), std::default_random_engine(seed));
	int i = 0;
	for (const auto& l : rez)
	{
		if (i == nr)
			break;
		lista.adaugaApartament(l);
		i++;
	}
	notify();

}

/*returneaza toate apartamentele din lista
	* date de intrare:-
	* date de iesire:-referinta la vectorul de apartamente
	*/
const vector<Locatar>& LocatarService::getAllLista()
{
	return lista.getAll();
}

/*transcrie lista de apartamente in fisier
* date de intrare::-filename-referinta la string
* date de iesire:-
*/
void LocatarService::writeToFile(const string& fileName)
{
	lista.writeToFile(fileName);
}

map<string, std::pair<string, int>> LocatarService::getMap()
{
	map<string, std::pair<string, int>> rez;
	const auto& locatari{ repo.getAll() };
	for (const auto& l : locatari)
		if (rez.find(l.getTipApartament()) == rez.end())
		{
			rez[l.getTipApartament()] = std::make_pair(l.getTipApartament(), 1);
		}
		else
			rez[l.getTipApartament()].second++;
	return rez;
}

/*undo
* date de intrare:-
* date de iesire:-
*/
void LocatarService::undo()
{
	if (undoActions.size() == 0)
		throw RepoException("nu se mai poate face undo!\n");
	undoActions.back()->doUndo();
	notify();
	undoActions.pop_back();
}