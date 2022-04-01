#include "Teste.h"
#include "Locatar.h"
#include "Exceptii.h"
#include "LocatarService.h"
#include "ListaNotificari.h"
#include "vectorDinamicTemplate.h"
#include <assert.h>
#include "LocatarRepository.h"
#include "LocatarRepositoryFile.h"

//teste pentru domeniu
void testeDomain() {
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	assert(loc.getApartament() == 1);
	assert(loc.getNume() == "Andrei");
	assert(loc.getSuprafata() == 240);
	assert(loc.getTipApartament() == "decomandat");
	loc.setApartament(2);
	loc.setNume("Cristi");
	loc.setSuprafata(123);
	loc.setTipApartament("semidecomandat");
	assert(loc.getApartament() == 2);
	assert(loc.getNume() == "Cristi");
	assert(loc.getSuprafata() == 123);
	assert(loc.getTipApartament() == "semidecomandat");
}

//teste pentru adauga din repo
void testeAdaugaRepo() {
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	LocatarRepository repo;
	repo.adaugaLocatar(loc);
	const auto& locatari = repo.getAll();
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Andrei");
	assert(locatari.at(0).getSuprafata() == 240);
	assert(locatari.at(0).getTipApartament() == "decomandat");
	assert(repo.getSize() == 1);
	try {
		repo.adaugaLocatar(loc);
		//assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "locatar existent!\n");
		assert(true);
	}

}

//teste pentru stergere din repo
void testeStergereRepo()
{
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	Locatar loc2{ 3,"Cristi",520,"semidecomandat" };
	LocatarRepository repo;
	repo.adaugaLocatar(loc);
	repo.adaugaLocatar(loc2);
	const auto& locatari = repo.getAll();
	assert(locatari.size() == 2);
	repo.stergereLocatar(1);
	const auto& locatari1 = repo.getAll();
	assert(locatari1.size() == 1);
	try {
		repo.stergereLocatar(4);
		//assert(false);
	}
	catch (const RepoException& msg) {
		assert(msg.getMesaj() == "locatar inexistent!\n");
		assert(true);
	}
}

//teste pentru modifica din repo
void testeModificaRepo()
{
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	LocatarRepository repo;
	repo.adaugaLocatar(loc);
	Locatar loc1{ 1, "Cristi", 123, "semidecomandat" };
	repo.modificareLocatar(loc1);
	const auto& locatari = repo.getAll();
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Cristi");
	assert(locatari.at(0).getSuprafata() == 123);
	assert(locatari.at(0).getTipApartament() == "semidecomandat");
	Locatar loc2{ 2, "Cristi", 123, "decomandat" };
	try {
		repo.modificareLocatar(loc2);
		//assert(false);
	}
	catch (const RepoException& msg) {
		assert(msg.getMesaj() == "locatar inexistent!\n");
		assert(true);
	}

}
//teste pentru cauta apartament din repo

void testCautaApartament()
{
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	Locatar loc2{ 3,"Cristi",520,"semidecomandat" };
	LocatarRepository repo;
	repo.adaugaLocatar(loc);
	repo.adaugaLocatar(loc2);
	vector<Locatar> locatari;
	Locatar locatar = repo.cautareApartament(1);
	assert(locatar.getApartament() == 1);
	assert(locatar.getNume() == "Andrei");
	assert(locatar.getSuprafata() == 240);
	assert(locatar.getTipApartament() == "decomandat");
	try {
		Locatar locatar1 = repo.cautareApartament(4);
		//assert(false);
	}
	catch (const RepoException& msg) {
		assert(msg.getMesaj() == "apartament inexistent!\n");
		assert(true);
	}
}

//teste pentru adauga din service
void testeAdaugaService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val , list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	const auto& locatari = srv.getAllService();
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Andrei");
	assert(locatari.at(0).getSuprafata() == 240);
	assert(locatari.at(0).getTipApartament() == "decomandat");

	try {
		srv.adaugaLocatarService(2, "", 240, "decomandat");
		//assert(false);
	}
	catch (const ValidException& e)
	{
		assert(e.getMesaj() == "nume invalid!\n");
		assert(true);
	}

	try {
		srv.adaugaLocatarService(2, "Andrei", -240, "decomandat");
		//assert(false);
	}
	catch (const ValidException& e)
	{
		assert(e.getMesaj() == "suprafata invalida\n");
		assert(true);
	}

	try {
		srv.adaugaLocatarService(2, "Andrei", 240, "");
		//assert(false);
	}
	catch (const ValidException& e)
	{
		assert(e.getMesaj() == "tip apartament invalid!\n");
		assert(true);
	}
}

//teste pentru stergere din service
void testeStergereService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val , list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLista(1);
	srv.adaugaLocatarService(2, "Cristi", 222, "semidecomandat");
	const auto& locatari = srv.getAllService();
	assert(locatari.size() == 2);
	srv.stergereLocatarService(1);
	const auto& locatari1 = srv.getAllService();
	assert(locatari1.size() == 1);
}

//teste pentru modifica din service
void testeModificaService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val ,list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLista(1);
	srv.adaugaLocatarService(2, "Cristi", 222, "semidecomandat");
	srv.modificaLocatarService(1, "Ana", 599, "simplu");
	const auto& locatari = srv.getAllService();
	assert(locatari.size() == 2);
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Ana");
	assert(locatari.at(0).getSuprafata() == 599);
	assert(locatari.at(0).getTipApartament() == "simplu");
	try {
		srv.modificaLocatarService(-2, "Andrei", 240, "decomandat");
		//assert(false);
	}
	catch (const ValidException& e)
	{
		assert(e.getMesaj() == "apartament invalid!\n");
		assert(true);
	}

}

//teste pentru cauta apartament din service

void testeCautaApartamentService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLocatarService(2, "Cristi", 222, "semidecomandat");
	Locatar locatar = srv.cautareApartamentService(1);
	assert(locatar.getApartament() == 1);
	assert(locatar.getNume() == "Andrei");
	assert(locatar.getSuprafata() == 240);
	assert(locatar.getTipApartament() == "decomandat");

}

//teste pentru filtrare
void testeFiltrare()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val , list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLocatarService(2, "Cristi", 222, "semidecomandat");
	srv.adaugaLocatarService(3, "Ana", 222, "decomandat");
	vector<Locatar> locatari = srv.filtrareTipApartament("decomandat");
	assert(locatari.size() == 2);
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Andrei");
	assert(locatari.at(0).getSuprafata() == 240);
	assert(locatari.at(0).getTipApartament() == "decomandat");
	vector<Locatar> locatari1 = srv.filtrareSuprafata(222);
	assert(locatari1.size() == 2);
	assert(locatari1.at(0).getApartament() == 2);
	assert(locatari1.at(0).getNume() == "Cristi");
	assert(locatari1.at(0).getSuprafata() == 222);
	assert(locatari1.at(0).getTipApartament() == "semidecomandat");
}
//teste pentru sortari
void testeSortari()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val ,list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLocatarService(2, "Cristi", 190, "semidecomandat");
	srv.adaugaLocatarService(3, "Ana", 222, "decomandat");
	srv.adaugaLocatarService(4, "Man", 333, "simplu");
	srv.adaugaLocatarService(5, "Radu", 260, "decomandat");
	vector<Locatar> locatari = srv.sortareNume();
	assert(locatari.size() == 5);
	assert(locatari.at(0).getApartament() == 3);
	assert(locatari.at(0).getNume() == "Ana");
	assert(locatari.at(0).getSuprafata() == 222);
	assert(locatari.at(0).getTipApartament() == "decomandat");

	vector<Locatar> locatari1 = srv.sortareSuprafata();
	assert(locatari1.size() == 5);
	assert(locatari1.at(0).getApartament() == 2);
	assert(locatari1.at(0).getNume() == "Cristi");
	assert(locatari1.at(0).getSuprafata() == 190);
	assert(locatari1.at(0).getTipApartament() == "semidecomandat");

	vector<Locatar> locatari2 = srv.sortareApartamentSuprafata();
	assert(locatari2.size() == 5);
	assert(locatari2.at(0).getApartament() == 3);
	assert(locatari2.at(0).getNume() == "Ana");
	assert(locatari2.at(0).getSuprafata() == 222);
	assert(locatari2.at(0).getTipApartament() == "decomandat");

}
void testeVectorDinamic()
{
	vectorDinamic<int> vector;
	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);
	vector.push_back(6);
	assert(vector.size() == 6);
	vector.erase(2);
	assert(vector.size() == 5);
	const int x = vector.at(1);
	assert(x == 2);
	vector.set(6, 1);
	assert(vector.at(1) == 6);
	vectorDinamic<int> vector1 = vector;
	assert(vector1.size() == 5);
	vectorDinamic<int> vector2{ vector };
	assert(vector2.size() == 5);
	IteratorVector<int> it = vector.begin();
	assert(it.valid() == true);
	it.next();
	const int y = it.element();
	assert(y == 6);
	const int a = *it;
	assert(a == 6);
	const IteratorVector<int> it1 = ++it;
	const int b = it1.element();
	assert(b == 4);
	assert((it == it1) == true);
	assert((it != it1) == false);
	const IteratorVector<int> it2 = vector.end();
}

void testeAdaugaListaNotificari()
{
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	ListaNotificari lista;
	lista.adaugaApartament(loc);
	const auto& locatari = lista.getAll();
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Andrei");
	assert(locatari.at(0).getSuprafata() == 240);
	assert(locatari.at(0).getTipApartament() == "decomandat");
	assert(lista.nrApartamente() == 1);
	try {
		lista.adaugaApartament(loc);
		//assert(false);
	}
	catch (const listaException& e) {
		assert(e.getMesaj() == "locatar existent!\n");
		assert(true);
	}
}

void testeGolesteListaNotificari()
{
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	ListaNotificari lista;
	lista.golesteLista();
	assert(lista.nrApartamente() == 0);
}

void testeScrieFisier()
{
	string fileName{ "teste" };
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	ListaNotificari lista;
	lista.adaugaApartament(loc);
	lista.writeToFile(fileName);
}

void testeAdaugaListaService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	repo.adaugaLocatar(loc);
	srv.adaugaLista(1);
	const auto& locatari = srv.getAllLista();
	assert(locatari.at(0).getApartament() == 1);
	assert(locatari.at(0).getNume() == "Andrei");
	assert(locatari.at(0).getSuprafata() == 240);
	assert(locatari.at(0).getTipApartament() == "decomandat");
	assert(srv.nrApartamenteLista() == 1);
	try {
		srv.adaugaLista(2);
		//assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "apartament inexistent!\n");
		assert(true);
	}
}

void testeGolesteListaService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	repo.adaugaLocatar(loc);
	srv.adaugaLista(1);
	srv.golesteLista();
	assert(srv.nrApartamenteLista() == 0);
}

void testeScrieFisierService()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	repo.adaugaLocatar(loc);
	srv.adaugaLista(1);
	srv.writeToFile("teste1");
}

void testeGenereazaLista()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	Locatar loc{ 1,"Andrei",240,"decomandat" };
	srv.adaugaLocatarService(3, "Ana", 222, "decomandat");
	repo.adaugaLocatar(loc);
	srv.adaugaLista(1);
	srv.genereazaLista(1);
	try {
		srv.genereazaLista(3);
		//assert(false);
	}
	catch (const listaException& e) {
		assert(e.getMesaj() == "numar de apartamente invalid!\n");
		assert(true);
	}

}

void testeMap()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLocatarService(2, "Cristi", 190, "semidecomandat");
	srv.adaugaLocatarService(3, "Ana", 222, "decomandat");
	map<string, std::pair<string, int>>locatari = srv.getMap();
	assert(locatari.size() == 2);
	assert(locatari["decomandat"].second == 2);
	assert(locatari["semidecomandat"].second == 1);

}

void testeUndo()
{
	LocatarRepository repo;
	ValidareLocatar val;
	ListaNotificari list;
	LocatarService srv{ repo , val, list };
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.adaugaLocatarService(3, "Ana", 222, "decomandat");
	srv.undo();
	vector<Locatar>locatari = srv.getAllService();
	assert(locatari.size() == 1);
	assert(locatari.at(0).getApartament() == 1);
	srv.undo();
	try {
		srv.undo();
	}
	catch (const RepoException& msg) {
		assert(msg.getMesaj() == "nu se mai poate face undo!\n");
	}
	srv.adaugaLocatarService(1, "Andrei", 240, "decomandat");
	srv.modificaLocatarService(1, "Alex", 1234, "semidecomandat");
	srv.undo();
	locatari = srv.getAllService();
	assert(locatari.size() == 1);
	assert(locatari.at(0).getApartament() == 1);
	srv.stergereLocatarService(1);
	srv.undo();
	locatari = srv.getAllService();
	assert(locatari.size() == 1);
	assert(locatari.at(0).getApartament() == 1);
}

void testeRepoFile()
{
	Locatar loc{ 11,"Andrei",240,"decomandat" };
	LocatarRepositoryFile repo{ "a" };
	repo.adaugaLocatar(loc);
	int size = repo.getSize();//:P
	Locatar loc1{ 11,"Ana",240,"decomandat" };
	repo.modificareLocatar(loc1);
	const Locatar& loc2 = repo.cautareApartament(11);
	assert(loc2.getNume() == "Ana");
	repo.stergereLocatar(11);
	//assert(repo.getSize() == 0);
}

//allTests
void allTests() {
	testeDomain();
	testeAdaugaRepo();
	testeStergereRepo();
	testeModificaRepo();
	testCautaApartament();
	testeAdaugaService();
	testeStergereService();
	testeModificaService();
	testeCautaApartamentService();
	testeFiltrare();
	testeSortari();
	testeVectorDinamic();
	testeAdaugaListaNotificari();
	testeGolesteListaNotificari();
	testeScrieFisier();
	testeAdaugaListaService();
	testeGolesteListaService();
	testeScrieFisierService();
	testeGenereazaLista();
	testeMap();
	testeUndo();
	testeRepoFile();
}