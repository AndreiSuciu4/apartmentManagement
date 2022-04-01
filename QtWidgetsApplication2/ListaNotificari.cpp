#include "ListaNotificari.h"
#include "Exceptii.h"

/*adauga apartament in lista
* date de intrare:-loc-referinta la ListaNotificari
* date de iesire:-
* programul arunca eroare daca locatarul a mai fost introdus
*/
void ListaNotificari::adaugaApartament(const Locatar& loc)
{
	
	auto it = std::find_if(lista.begin(), lista.end(), [&](const Locatar& l) {return l.getApartament() == loc.getApartament(); });
	if (it != lista.end())
		throw listaException("locatar existent!\n");
	lista.push_back(loc);
	//notify();

}

/*goleste lista de notificari
* date de intrare:-
* date de iesire:-
*/
void ListaNotificari::golesteLista()noexcept
{
	lista.clear();
	//notify();
}

/*returneaza toate apartamentele din lista
* date de intrare:-
* date de iesire:-referinta la vectorul de apartamente
*/
const vector<Locatar>& ListaNotificari::getAll()noexcept
{
	return lista;
}

/*returneaza numarul de apartamente din lista
* date de intrare:-
* date de iesire:-numarul de apartamente:-int
*/
int ListaNotificari::nrApartamente() noexcept
{
	return lista.size();
}

/*transcrie lista de apartamente in fisier
* date de intrare::-filename-referinta la string
* date de iesire:-
* programul arunca exceptie daca nu a putut deschide fisierul
*/
void ListaNotificari::writeToFile(const string& fileName)
{
	string file = fileName + ".csv";
	std::ofstream out(file);
	if (!out.is_open()) {
		throw listaException("Error open file");
	}
	out << "Numar apartament, Nume, Suprafata, Tip Apartament" << std::endl;
	for (const auto& l : lista)
	{
		out << l.getApartament() << ", " << l.getNume() << ", " << l.getSuprafata() << ", " << l.getTipApartament();
		out << std::endl;
	}
	out.close();
}

/*stergere locatar
* date de intrare:-pozitie-int
* date de iesire:-
*/
void ListaNotificari::stergereApartament(const int& nr)
{
	auto it = std::find_if(lista.begin(), lista.end(), [&](const Locatar& l) {return l.getApartament() == nr; });
	if (it != lista.end())
		lista.erase(it);
	//notify();
}

/*modifica locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
*/
void ListaNotificari::modificaApartament(const Locatar& loc)
{
	for (Locatar& l : lista)
		if (l.getApartament() == loc.getApartament()) {
			l = loc;
			//notify();
			return;
		}
}
