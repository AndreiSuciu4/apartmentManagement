#include "ExceptionRepo.h"
#include "Exceptii.h"
#include <algorithm>


/*adauga locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
* aplicatia arunca eroarea "locatar existent!" daca apartamentul a fost deja adaugat
*/
void ExceptionRepo::adaugaLocatar(const Locatar& loc) {
	auto it = locatari.find(loc.getApartament());
	if (it != locatari.end())
		throw RepoException("locatar existent!\n");
	locatari[loc.getApartament()] = loc;
	double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (p >= probabilitate)
		throw RepoException("exceptie!\n");
}

/*stergere locatar
* date de intrare:-pozitie-int
* date de iesire:-
* programul arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
*/
void ExceptionRepo::stergereLocatar(const int& apartament)
{
	auto it = locatari.find(apartament);
	if (it == locatari.end())
		throw RepoException("locatar inexistent!\n");
	locatari.erase(it);
	double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (p >= probabilitate)
		throw RepoException("exceptie!\n");
}

/*modifica locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
* aplicatia arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
*/
void ExceptionRepo::modificareLocatar(const Locatar& loc)
{
	for (auto& l : locatari)
	{
		if (l.first == loc.getApartament()) {
			locatari[l.first] = loc;
			double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			if (p >= probabilitate)
				throw RepoException("exceptie!\n");
		}
	}
	throw RepoException("locatar inexistent!\n");

}

/*cautare apartament
* date de intrare:-apartament-int
* date de iesire:-locatarul dorit-referinta la Locatar
* programul arunca eroarea "apartament inexistent" daca nu exista locatari pe pozitie dorita
*/
const Locatar& ExceptionRepo::cautareApartament(const int& apart) const
{
	for (const auto& l : locatari)
		if (l.first == apart) {
			double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			if (p >= probabilitate)
				throw RepoException("exceptie!\n");
			return l.second;
		}
	throw RepoException("apartament inexistent!\n");

}

/*returneaza locatarii
* date de intrare:-
* date de iesire:-locatari-referinta la vector
*/
const vector<Locatar>& ExceptionRepo::getAll() {
	locat.clear();
	for (const auto& l : locatari)
		locat.push_back(l.second);
	double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (p >= probabilitate)
		throw RepoException("exceptie!\n");
	return locat;
}

/*returneaza numarul de apartamente din repo
	* date de intrare:-
	* date de iesire:numarul de apartamente-int
	*/
int ExceptionRepo::getSize() const
{
	double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (p >= probabilitate)
		throw RepoException("exceptie!\n");
	return locatari.size();
}