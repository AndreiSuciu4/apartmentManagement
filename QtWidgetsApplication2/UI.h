#pragma once
#include "Locatar.h"
#include "LocatarRepository.h"
#include "LocatarService.h"
#include "Exceptii.h"

//clasa UI
class UI
{
private:
	LocatarService& srv;
	//UI pentru adauga locatar
	void UIadaugaLocatar();
	//UI pentru afisare locatari
	void UIafisareLocatar();
	//UI pentru stergere locatari
	void UIstergereLocatar();
	//UI pntru modifica locatari
	void UImodificaLocatar();
	//UI pentru cauta apartament
	void UIcautaApartament();
	//UI pentru filtrare dupa tip apartament
	void UIfiltrareTipApartament();
	//UI pentru filtrare dupa suprafata
	void UIfiltrareSuprafata();
	//UI pentru sortare dupa nume
	void UIsortareNume();
	//UI pentru sortare dupa suprafata
	void UIsortareSuprafata();
	//UI pentru sortare  dupa tip si suprafata
	void UIsortareTipSuprafata();
	//UI prentru adauga apartament in lista de notificari
	void UIadaugaListaNotificari();
	//UI pentru goleste lista de notificari
	void UIgolesteLista();
	//UI pentru genereaza lista de notificari
	void UIgenereazaLista();
	//UI pentru afisarea listei de notificari
	void UIafisareLista();
	//UI pentru export
	void UIexport();
	//UI pentru undo
	void UIundo();
	void UIgetMap();
	//meniu
	void meniu();
public:
	/*constructor
	* date de intrare-srv-referinta la LocatarService
	* date de iesire:-
	*/
	UI(LocatarService& srv) noexcept :srv{ srv } {

	}
	//run
	void UIadauga();
	void run();
};

