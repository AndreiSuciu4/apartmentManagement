#include "UI.h"
#include <iostream>
#include <string>
#include <map>
using std::cin;
using std::cout;
using std::string;
using std::map;

//UI pentru adauga locatar
void UI::UIadaugaLocatar()
{
	string nume;
	string tipApartament;
	string apartament;
	string suprafata;
	cout << "apartament=";
	getline(cin, apartament, '\n');
	cout << "nume=";
	getline(cin, nume, '\n');
	cout << "suprafata=";
	getline(cin, suprafata, '\n');
	cout << "tipApartament=";
	getline(cin, tipApartament, '\n');
	int apartament1{ 0 };
	double suprafata1{ 0 };
	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		suprafata1 = stoi(suprafata);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		srv.adaugaLocatarService(apartament1, nume, suprafata1, tipApartament);
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}
	catch (const ValidException& msg) {
		cout << msg.getMesaj();
	}
}

//UI pentru afisare locatari
void UI::UIafisareLocatar()
{
	try {
		const vector < Locatar >& locatari = srv.getAllService();
		if (locatari.size() == 0)
		{
			cout << "lista vida";
			return;
		}
		for (const auto& l : locatari)
			cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}

}

//UI pentru stergere locatari
void UI::UIstergereLocatar()
{
	string apartament;
	int apartament1;
	cout << "apartament=";
	getline(cin, apartament, '\n');

	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		srv.stergereLocatarService(apartament1);
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}

}

//UI pntru modifica locatari
void UI::UImodificaLocatar()
{
	string nume;
	string tipApartament;
	string apartament;
	string suprafata;
	int apartament1{ 0 };
	double suprafata1{ 0 };
	cout << "apartament=";
	getline(cin, apartament, '\n');
	cout << "nume=";
	getline(cin, nume, '\n');
	cout << "suprafata=";
	getline(cin, suprafata, '\n');
	cout << "tipApartament=";
	getline(cin, tipApartament, '\n');
	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		suprafata1 = stoi(suprafata);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		srv.modificaLocatarService(apartament1, nume, suprafata1, tipApartament);
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}
	catch (const ValidException& msg) {
		cout << msg.getMesaj();
	}
}

//UI pentru cauta apartament
void UI::UIcautaApartament()
{
	string apartament;
	int apartament1;
	cout << "apartament=";
	getline(cin, apartament, '\n');
	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	try {
		const Locatar& l = srv.cautareApartamentService(apartament1);
		cout << "Apartament:" << l.getApartament() << " locatari:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " tip apartament:" << l.getTipApartament() << "\n";
	}
	catch (const RepoException& e)
	{
		cout << e.getMesaj();
	}

}
//UI pentru filtrare dupa tip apartament
void UI::UIfiltrareTipApartament()
{
	string  apartament;
	cout << "tip apartament=";
	getline(cin, apartament, '\n');
	vector<Locatar>locatari = srv.filtrareTipApartament(apartament);
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";
}
//UI pentru filtrare dupa suprafata
void UI::UIfiltrareSuprafata()
{
	string suprafata;
	int suprafata1;
	cout << "suprafata=";
	getline(cin, suprafata, '\n');
	try {
		suprafata1 = stoi(suprafata);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	vector<Locatar>locatari = srv.filtrareSuprafata(suprafata1);
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}
//UI pentru sortare dupa nume
void UI::UIsortareNume()
{
	vector<Locatar> locatari = srv.sortareNume();
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

//UI pentru sortare dupa suprafata
void UI::UIsortareSuprafata()
{
	vector<Locatar> locatari = srv.sortareSuprafata();
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

//UI pentru sortare  dupa tip si suprafata
void UI::UIsortareTipSuprafata()
{
	vector<Locatar> locatari = srv.sortareApartamentSuprafata();
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

void UI::UIadaugaListaNotificari()
{
	string apartament;
	int apartament1;
	cout << "apartament=";
	getline(cin, apartament, '\n');

	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	try {
		srv.adaugaLista(apartament1);
	}
	catch (const listaException& msg) {
		cout << msg.getMesaj();
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}
	const int total = srv.nrApartamenteLista();
	cout << "nr aparteamente din lista de notificari:" << total;

}

void UI::UIgolesteLista() {
	srv.golesteLista();
	const int total = srv.nrApartamenteLista();
	cout << "nr aparteamente din lista de notificari:" << total;
}

void UI::UIgenereazaLista()
{
	string numar;
	int numar1;
	cout << "apartamente=";
	getline(cin, numar, '\n');

	try {
		numar1 = stoi(numar);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	try {
		srv.genereazaLista(numar1);
	}
	catch (const listaException& msg) {
		cout << msg.getMesaj();
	}
	const int total = srv.nrApartamenteLista();
	cout << "nr aparteamente din lista de notificari:" << total;
}

void UI::UIafisareLista()
{
	const vector < Locatar >& locatari = srv.getAllLista();
	if (locatari.size() == 0)
	{
		cout << "lista vida";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

void UI::UIexport()
{
	string fileName;
	cout << "numele fisierului=";
	getline(cin, fileName, '\n');
	if (fileName == "")
	{
		cout << "nume fisier invalid";
		return;
	}
	srv.writeToFile(fileName);
}

void UI::UIundo()
{
	try {
		srv.undo();
	}
	catch (const RepoException& msg)
	{
		cout << msg.getMesaj();
	}
}

void UI::UIgetMap()
{
	map<string, std::pair<string, int>>locatari = srv.getMap();
	if (locatari.size() == 0)
	{
		cout << "nu exista locatari in map";
		return;
	}
	for (const auto& l : locatari)
		cout << l.first << "->" << l.second.second << "\n";
}

void UI::UIadauga()
{
	srv.adaugaLocatarService(1, "Andrei", 123, "decomandat");
	srv.adaugaLocatarService(2, "Ana", 1234, "decomandat");
	srv.adaugaLocatarService(3, "Maria", 985, "comandat");
	srv.adaugaLocatarService(4, "Radu", 234, "comandat");
	srv.adaugaLocatarService(5, "Sorin", 324, "comandat");
	srv.adaugaLocatarService(6, "Diana", 1000, "simplu");
	srv.adaugaLocatarService(7, "Dana", 678, "simplu");
	srv.adaugaLocatarService(8, "Cristi", 317, "simplu");
	srv.adaugaLocatarService(9, "Marius", 751, "complex");
	srv.adaugaLocatarService(10, "Alex", 978, "complex");
}

//meniu
void UI::meniu()
{
	cout << "\n1-Adauga locatar\n2-Afisare\n3-Stergere locatar\n4-Modifica locatar\n5-Cauta apartament\n6-Filtrare dupa tipul apartamentului\n7-Filtrare dupa suprafata\n";
	cout << "8-Sortarea apartamentelor dupa numele locatarilor\n9-Sortarea apartamentelor dupa suprafata\n10-Sortarea apartamentelor dupa tip si suprafata\n";
	cout << "11-Adauga apartament in lista de notificari\n12-Goleste lista de notificari\n13-Genereaza lista\n14-Afisare lista notificari\n15-Export\n";
	cout << "16-Adauga\n17-Get Map\n18-Undo\n0-Exit\n";
}
//run
void UI::run()
{
	while (true)
	{
		string cmd1;
		int cmd = -1;
		meniu();
		cout << ">>>";
		getline(cin, cmd1, '\n');
		try {
			cmd = stoi(cmd1);
		}
		catch (const std::invalid_argument) {
		}
		switch (cmd)
		{
		case(1): {
			UIadaugaLocatar();
			break;
		}
		case(2): {
			UIafisareLocatar();
			break;
		}
		case(3): {
			UIstergereLocatar();
			break;
		}
		case(4): {
			UImodificaLocatar();
			break;
		}
		case(5): {
			UIcautaApartament();
			break;
		}
		case(6): {
			UIfiltrareTipApartament();
			break;
		}
		case(7): {
			UIfiltrareSuprafata();
			break;
		}
		case(8): {
			UIsortareNume();
			break;
		}
		case(9): {
			UIsortareSuprafata();
			break;
		}
		case(10): {
			UIsortareTipSuprafata();
			break;
		}
		case(11): {
			UIadaugaListaNotificari();
			break;
		}
		case(12): {
			UIgolesteLista();
			break;
		}
		case(13): {
			UIgenereazaLista();
			break;
		}
		case(14): {
			UIafisareLista();
			break;
		}
		case(15): {
			UIexport();
			break;
		}
		case(16): {
			UIadauga();
			break;
		}
		case(17): {
			UIgetMap();
			break;
		}
		case(18): {
			UIundo();
			break;
		}
		case(0): {
			cout << "bye";
			return;
		}
		default: {
			cout << "comanda invalida!\n";
			break;
		}
		}

	}
}
