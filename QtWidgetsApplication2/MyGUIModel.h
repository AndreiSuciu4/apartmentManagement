#include <qwidget.h>
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QItemSelectionModel>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qobject.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include "LocatarRepository.h"
#include "ValidareLocatar.h"
#include "ListaNotificari.h"
#include "LocatarService.h"
#include "LocatarRepositoryFile.h"
#include "ExceptionRepo.h"
#include "ListaNotificariGUI.h"
#include <iostream>
#include <string>
#include "Teste.h"
#include "UI.h"
#include "Exceptii.h"
#include <vector>
#include <qpainter.h>
#include "Observer.h"
#include <string>
#include <QPoint>
#include <qobject.h>
#include <QTableView>
#include <qcombobox.h>
#include "Modele.h"
using std::vector;
using std::string;


//clasa pentru a afisa un tabel
class tabel1 :public QDialog {
private:
	vector<Locatar>locatari;
	QHBoxLayout* box;

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();
public:
	/*constructor
	* date de intrare:-locatar-vector
	* date de iesire:-
	*/
	tabel1(const vector<Locatar>& locatar) :locatari{ locatar } {
		init();
	}
};

class tabelDetalii1 :public QDialog {
private:
	Locatar locatar;
	QLineEdit* apartament;
	QLineEdit* nume;
	QLineEdit* suprafata;
	QLineEdit* tipApartament;
	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();
public:
	/*constructor
	* date de intrare:-locatar-vector
	* date de iesire:-
	*/
	tabelDetalii1(Locatar locatar) :locatar{ locatar } {
		init();
	}
};



class MyGUIModel :public QWidget
{
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;
	QHBoxLayout* box2;
	QHBoxLayout* box3;
	QHBoxLayout* box4;
	QHBoxLayout* box5;
	QLabel* mesaj;
	QVBoxLayout* buttAndLines;
	QHBoxLayout* buttons;

	//butoane
	QPushButton* adauga;
	QPushButton* afisare;
	QPushButton* sterge;
	QPushButton* cauta;
	QPushButton* modifica;
	QPushButton* undo;
	QPushButton* listaNotificari;
	QPushButton* CosCRUD;
	QPushButton* CosV2CRUD;
	QPushButton* CosReadOnly;
	QPushButton* adaugaCos;
	QPushButton* Export;
	QPushButton* genereaza;
	QPushButton* exit;

	//QLineEdit
	QLineEdit* apartament;
	QLineEdit* nume;
	QLineEdit* suprafata;
	QLineEdit* tipApartament;
	QLineEdit* fisier;
	QLineEdit* nrApart;

	//lista
	QListWidget* list;
	QTableWidget* table;

	ListModel* modelLista;
	QListView* lista;

	TableModel* model;
	QTableView* tabelNou;
	//functii

	QComboBox* combo;
	QComboBox* comboSortari;

	QListWidgetItem* selectedItem = nullptr;

	/*init
	* date de intrare:-
	* date de iesire:-
	*/
	void init();

	/*afisare lista utilizand QListWidget
	* date de intrare:-vector de Locatar
	* date de iesire:
	*/
	void loadList(vector<Locatar>);

	/*
	* conectam butoanele cu functiile
	* date de intrare:
	* date de iesire:
	*/
	void connect();

	/*conectam butonul adauga cu functia de adaugare din service
	* date de intrare:
	* date de iesire:
	*/
	void adaugaLocatar();

	/*conectam butonul afisare cu functia getALL din service
	* date de intrare:
	* date de iesire:
	*/
	void afisareLocatar();

	/*conectam butonul sterge cu functia de stergere din service
	* date de intrare:
	* date de iesire:
	*/
	void stergeLocatar();

	/*conectam butonul cauta cu functia de cautare din service
	* date de intrare:
	* date de iesire:
	*/
	void cautaLocatar();

	/*conectam butonul modifica cu functia de modificare din service
	* date de intrare:
	* date de iesire:
	*/
	void modificaLocatar();


	/*conectam butonul undo cu functia undo din service
	* date de intrare:
	* date de iesire:
	*/
	void Undo();

	//void update()override;

	void tab(vector<Locatar>);

public:
	MyGUIModel(LocatarService& srv) :srv{ srv } {
		init();
		loadList(srv.getAllService());
		connect();
		tab(srv.getAllService());
	}
};

