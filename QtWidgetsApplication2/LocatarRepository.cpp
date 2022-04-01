#include "LocatarRepository.h"
#include "Exceptii.h"
#include <algorithm>

/*adauga locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
* aplicatia arunca eroarea "locatar existent!" daca apartamentul a fost deja adaugat
*/
void LocatarRepository::adaugaLocatar(const Locatar& loc) {
	auto it = std::find_if(locatari.begin(), locatari.end(), [&](const Locatar& l) {return l.getApartament() == loc.getApartament(); });
	if (it != locatari.end())
		throw RepoException("locatar existent!\n");
	locatari.push_back(loc);
}

/*stergere locatar
* date de intrare:-pozitie-int
* date de iesire:-
* programul arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
*/
void LocatarRepository::stergereLocatar(const int& apartament)
{
	auto it = std::find_if(locatari.begin(), locatari.end(), [&](const Locatar& l) {return l.getApartament() == apartament; });
	if (it == locatari.end())
		throw RepoException("locatar inexistent!\n");
	locatari.erase(it);
}

/*modifica locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
* aplicatia arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
*/
void LocatarRepository::modificareLocatar(const Locatar& loc)
{
	for (Locatar& l : locatari)
	{
		if (l.getApartament() == loc.getApartament()) {
			l = loc;
			return;
		}
	}
	throw RepoException("locatar inexistent!\n");

}

/*cautare apartament
* date de intrare:-apartament-int
* date de iesire:-locatarul dorit-referinta la Locatar
* programul arunca eroarea "apartament inexistent" daca nu exista locatari pe pozitie dorita
*/
const Locatar& LocatarRepository::cautareApartament(const int& apart) const
{
	for (const Locatar& l : locatari)
		if (l.getApartament() == apart)
			return l;
	throw RepoException("apartament inexistent!\n");

}

/*returneaza locatarii
* date de intrare:-
* date de iesire:-locatari-referinta la vector
*/
const vector<Locatar>& LocatarRepository::getAll() noexcept {
	return locatari;
}

/*returneaza numarul de apartamente din repo
	* date de intrare:-
	* date de iesire:numarul de apartamente-int
	*/
int LocatarRepository::getSize() const noexcept
{
	return locatari.size();
}