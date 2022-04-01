#include "GUI.h"
#include <string>

/*initilizare
date de intrare:-
date de iesire:-
*/
void GUI::init()
{
	this->setWindowTitle("Administrare bloc");

	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;
	box2 = new QHBoxLayout;
	box3 = new QHBoxLayout;
	box4 = new QHBoxLayout; 
	box5 = new QHBoxLayout;
	mesaj = new QLabel("@ Instrumente lista notificari @");
	buttAndLines = new QVBoxLayout;
	buttons = new QHBoxLayout;

	//butoane
	adauga = new QPushButton("&adauga");
	afisare = new QPushButton("&lista");
	sterge = new QPushButton("&sterge");
	cauta = new QPushButton("&cauta");
	modifica = new QPushButton("&modifica");
	filtrare = new QPushButton("&filtrare");
	filtrareTip = new QPushButton("&filtrare Tip");
	filtrareSuprafata = new QPushButton("&filtrare Suprafata");
	sortare = new QPushButton("&sortare");
	sortareSuprafata = new QPushButton("&sortare suprafata");
	sortareNume = new QPushButton("&sortare nume");
	sortareTipSuprafata = new QPushButton("&sortare tip si suprafata");
	undo = new QPushButton("&undo");
	listaNotificari = new QPushButton("&lista notificari");
	CosCRUD = new QPushButton("&CosCRUDGUI");
	CosV2CRUD = new QPushButton("&CosV2CRUDGUI");
	CosReadOnly = new QPushButton("&CosReadOnlyGUI");
	adaugaCos = new QPushButton("&adauga cos");
	Export = new QPushButton("&export");
	genereaza = new QPushButton("&genereaza");
	exit = new QPushButton("&exit");

	//QLineEdit
	apartament = new QLineEdit;
	nume = new QLineEdit;
	suprafata = new QLineEdit;
	tipApartament = new QLineEdit;
	fisier = new QLineEdit;
	nrApart = new QLineEdit;
	//lista
	list = new QListWidget;
	table = new QTableWidget{ 1, 4 };

	principalBox->addLayout(box);
	box->addWidget(list);
	box->addLayout(box1);
	box1->addWidget(filtrare);
	box1->addStretch();
	box1->addWidget(sortare);
	box1->addStretch();
	box1->addWidget(afisare);


	box2->addWidget(adauga);
	box2->addStretch();
	box2->addWidget(sterge);
	box2->addStretch();
	box2->addWidget(cauta);
	box2->addStretch();


	box3->addWidget(modifica);
	box3->addWidget(undo);

	box4->addWidget(adaugaCos);
	box4->addWidget(Export);
	box4->addWidget(genereaza);


	box5->addWidget(CosCRUD);
	box5->addWidget(CosV2CRUD);
	box5->addWidget(CosReadOnly);

	QFormLayout* form = new QFormLayout;
	form->addRow("Apartament",apartament);
	form->addRow("Nume", nume);
	form->addRow("Suprafata", suprafata);
	form->addRow("Tip Apartament", tipApartament);
	form->addRow("Fisier", fisier);
	form->addRow("Numar Apartamente", nrApart);

	buttAndLines->addLayout(form);
	buttAndLines->addLayout(box2);
	buttAndLines->addLayout(box3);
	buttAndLines->addWidget(mesaj);
	buttAndLines->addLayout(box4);
	buttAndLines->addLayout(box5);
	buttAndLines->addWidget(exit);
	buttAndLines->addStretch();
	principalBox->addLayout(buttAndLines);

	auto tab = new tabel{ srv.getAllService() };
	tab->setModal(false);
	principalBox->addWidget(table);
	//butoaneFiltrare->addWidget(filtrareTip);
	setLayout(principalBox);
}

/*afisare lista utilizand QListWidget
* date de intrare:-vector de Locatar
* date de iesire:
*/
void GUI::loadList(vector<Locatar> locatari)
{
	list->clear();
	for (const auto& loc : locatari) {
		QListWidgetItem* item = new QListWidgetItem ( QString::fromStdString(loc.getNume()) );
		list->addItem(item);
		item->setData(Qt::UserRole,QString::fromStdString(std::to_string(loc.getApartament())));
	}
}

/*
* conectam butoanele cu functiile
* date de intrare:
* date de iesire:
*/
void GUI::connect()
{
	
	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		close();
		}); 
	
	QWidget::connect(CosCRUD, &QPushButton::clicked, [&]() {
		auto* cos = new CosCRUDGUI( srv );
		cos->show();
		});

	QWidget::connect(CosV2CRUD, &QPushButton::clicked, [&]() {
		auto* cos = new CosV2CRUDGUI(srv);
		cos->show();
		});

	QWidget::connect(CosReadOnly, &QPushButton::clicked, [&]() {
		auto listNot = new CosReadOnlyGUI(srv);
		listNot->show();
		});

	QWidget::connect(listaNotificari, &QPushButton::clicked, [&]() {
		auto listaNot = new listNotificariGUI(srv);
		listaNot->show();
		});

	QWidget::connect(list, &QListWidget::itemSelectionChanged, [&]() {
		if (selectedItem != nullptr) 
			selectedItem->setBackground(Qt::transparent);
		if (list->selectedItems().isEmpty())
		{
			apartament->setText("");
			nume->setText("");
			suprafata->setText("");
			tipApartament->setText("");
			return;
		}
		auto item = list->selectedItems().at(0);
		apartament->setText(item->data(Qt::UserRole).toString());
		nume->setText(item->text());
		suprafata->setText(QString::number(srv.cautareApartamentService(item->data(Qt::UserRole).toInt()).getSuprafata()));
		tipApartament->setText(QString::fromStdString(srv.cautareApartamentService(item->data(Qt::UserRole).toInt()).getTipApartament()));
		item->setBackground(Qt::darkGreen);
		auto tab = new tabelDetalii{ srv.cautareApartamentService(item->data(Qt::UserRole).toInt()) };
		tab->show();
		selectedItem = item;
		//item->setBackground(Qt::transparent);
		});

	QWidget::connect(adaugaCos, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.adaugaLista(apartament1);
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		}
	);

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(nrApart->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
			//loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	QWidget::connect(Export, &QPushButton::clicked, [&]() {
		try {
			srv.writeToFile(fisier->text().toStdString());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	adaugaLocatar();
	stergeLocatar();
	cautaLocatar();
	modificaLocatar();
	filtrareButton();
	filtrareTipApart();
	filtrareSupra();
	sortareButton();
	sortSuprafata();
	sortNume();
	sortTipSuprafata();
	Undo();
	afisareLocatar();
}

/*conectam butonul adauga cu functia de adaugare din service
* date de intrare:
* date de iesire:
*/
void GUI::adaugaLocatar()
{
	QWidget::connect(adauga, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		double suprafata1{ 0 };
		try {
			try {
				apartament1 = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			try {
				suprafata1 = std::stod(suprafata->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return; 
			}
			srv.adaugaLocatarService(apartament1, nume->text().toStdString(), suprafata1, tipApartament->text().toStdString());
			loadList(srv.getAllService());
			tab(srv.getAllService());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		catch (const ValidException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
}

/*conectam butonul afisare cu functia getALL din service
* date de intrare:
* date de iesire:
*/
void GUI::afisareLocatar()
{
	QWidget::connect(afisare, &QPushButton::clicked, [&]() {
		auto tab = new tabel{srv.getAllService()};
		tab->setModal(false);
		tab->show();

		});
}

/*conectam butonul sterge cu functia de stergere din service
* date de intrare:
* date de iesire:
*/
void GUI::stergeLocatar()
{
	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		int apart = 0;
		try {
			try {
				apart = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.stergereLocatarService(apart);
			loadList(srv.getAllService());
			tab(srv.getAllService());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
}

/*conectam butonul cauta cu functia de cautare din service
* date de intrare:
* date de iesire:
*/
void GUI::cautaLocatar()
{
	QWidget::connect(cauta, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			vector<Locatar>loc;
			loc.push_back(srv.cautareApartamentService(apartament1));
			auto tab = new tabel(loc);
			tab->show();
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
}

/*conectam butonul modifica cu functia de modificare din service
* date de intrare:
* date de iesire:
*/
void GUI::modificaLocatar()
{
	QWidget::connect(modifica, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		double suprafata1{ 0 };
		try {
			try {
				apartament1 = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			try {
				suprafata1 = std::stod(suprafata->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.modificaLocatarService(apartament1, nume->text().toStdString(), suprafata1, tipApartament->text().toStdString());
			loadList(srv.getAllService());
			tab(srv.getAllService());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		catch (const ValidException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
}

/*conectam butonul filtrare la butoanele filtreTip si filtrareSuprafata
* date de intrare:
* date de iesire:
*/
void GUI::filtrareButton()
{
	QWidget::connect(filtrare, &QPushButton::clicked, [&]() {
		box->addWidget(filtrareTip);
		box->addWidget(filtrareSuprafata);
		});
}

/*conectam butonul filtrareTip cu functia de filtrare dupa tipul apartamentului din service
* date de intrare:
* date de iesire:
*/
void GUI::filtrareTipApart()
{
	QWidget::connect(filtrareTip, &QPushButton::clicked, [&]() {
		auto tab = new tabel{ srv.filtrareTipApartament(tipApartament->text().toStdString())};
		tab->show();
		});
}

/*conectam butonul filtrareSuprafata cu functia de filtrare dupa suprafata din service
* date de intrare:
* date de iesire:
*/
void GUI::filtrareSupra()
{
	QWidget::connect(filtrareSuprafata, &QPushButton::clicked, [&]() {
		double suprafata1{ 0 };
		try {
			suprafata1 = std::stod(suprafata->text().toStdString());
			auto tab = new tabel{ srv.filtrareSuprafata(suprafata1) };
			tab->show();
		}
		catch (const std::invalid_argument) {
			QMessageBox::warning(this, "warning", "valoare invalida");
			return;
		}
		});
}

/*conectam butonul sortare la butoanele sortareSuprafata, sortareNume si sortareTipSuprafata
* date de intrare:
* date de iesire:
*/
void GUI::sortareButton()
{
	QWidget::connect(sortare, &QPushButton::clicked, [&]() {
		box->addWidget(sortareSuprafata);
		box->addWidget(sortareNume);
		box->addWidget(sortareTipSuprafata);

		});
}

/*conectam butonul sortareSuprafata cu functia de sortare dupa suprafata din service
* date de intrare:
* date de iesire:
*/
void GUI::sortSuprafata()
{
	QWidget::connect(sortareSuprafata, &QPushButton::clicked, [&]() {
		auto tab = new tabel{ srv.sortareSuprafata() };
		tab->show();
		});
}

/*conectam butonul sortareNume cu functia de sortare dupa nume din service
* date de intrare:
* date de iesire:
*/
void GUI::sortNume()
{
	QWidget::connect(sortareNume, &QPushButton::clicked, [&]() {
		auto tab = new tabel{ srv.sortareNume() };
		tab->show();
		});
}

/*conectam butonul sortareTipSuprafata cu functia de sortare dupa tip sisuprafata din service
* date de intrare:
* date de iesire:
*/
void GUI::sortTipSuprafata()
{
	QWidget::connect(sortareTipSuprafata, &QPushButton::clicked, [&]() {
		auto tab = new tabel{ srv.sortareApartamentSuprafata() };
		tab->show();
		});
}

/*conectam butonul undo cu functia undo din service
* date de intrare:
* date de iesire:
*/
void GUI::Undo()
{
	QWidget::connect(undo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			loadList(srv.getAllService());
			tab(srv.getAllService());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning",QString::fromStdString(msg.getMesaj()));
		}
		});
}

void GUI::tab(vector<Locatar> locatar)
{
	table->clear();
	int l = table->rowCount();
	for (int i = 0; i < l; i++)
		table->removeRow(0);
	table->setItem(0, 0, new QTableWidgetItem("apartament"));
	table->setItem(0, 1, new QTableWidgetItem("nume"));
	table->setItem(0, 2, new QTableWidgetItem("suprafata"));
	table->setItem(0, 3, new QTableWidgetItem("tip apartament"));
	for (const auto& l : locatar) {
		table->insertRow(table->rowCount());
		table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(l.getApartament())));
		table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(l.getNume())));
		table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(QString::number(l.getSuprafata())));
		table->setItem(table->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(l.getTipApartament())));
	}
}

/*initilizare
date de intrare:-
date de iesire:-
*/
void tabel::init()
{
	this->setWindowTitle("Tabel");
	box = new QHBoxLayout;
	setModal(true);//nu putem accesa alte ferestre cat timp tabelul e pornit
	QTableWidget* table = new QTableWidget{ 1, 4 };
	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray); 
	setAutoFillBackground(true);
	setPalette(pal);
	table->setItem(0, 0, new QTableWidgetItem("apartament"));
	table->setItem(0, 1, new QTableWidgetItem("nume"));
	table->setItem(0, 2, new QTableWidgetItem("suprafata"));
	table->setItem(0, 3, new QTableWidgetItem("tip apartament"));
	for (const auto&l : locatari) {
		table->insertRow(table->rowCount());
		table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(QString::number(l.getApartament())));
		table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(l.getNume())));
		table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(QString::number(l.getSuprafata())));
		table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(QString::fromStdString(l.getTipApartament())));
	}
	box->addWidget(table);
	setLayout(box);
}

//afiseaza lista de locatari din lista de notificari
//date de intrare:-locatari:-vector
//                -numar:-int
//date de iesire:-
void listNotificariGUI::loadList(vector<Locatar>,int numar)
{
	list->clear();
	for (const auto& l : srv.getAllLista())
		list->addItem(QString::fromStdString(l.getNume()));
	list->addItem(QString::fromStdString("numar apartamente: " + std::to_string(numar)));
}


/*initilizare
date de intrare:-
date de iesire:-
*/
void listNotificariGUI::init()
{
	this->setWindowTitle("Lista Notificari");
	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;
	box2 = new QHBoxLayout;
	box3 = new QHBoxLayout;
	list = new QListWidget;

	//butoane
	adauga = new QPushButton("&adauga");
	sterge = new QPushButton("&goleste lista");
	genereaza = new QPushButton("&genereaza lista");
	Export = new QPushButton("&export");
	afisare = new QPushButton("&afisare");
	exit = new QPushButton("&exit");

	//QLineEdit
	apartament = new QLineEdit;
	numarApartamente = new QLineEdit;
	numeFisier = new QLineEdit;

	QFormLayout* form = new QFormLayout;
	form->addRow("Apartament", apartament);
	form->addRow("Numar apartamente", numarApartamente);
	form->addRow("Nume fisier", numeFisier);


	principalBox->addWidget(list);
	principalBox->addLayout(form);
	box->addWidget(adauga);
	box->addWidget(sterge);
	box->addWidget(genereaza);
	box->addWidget(Export);
	box->addWidget(afisare);
	box->addWidget(exit);
	principalBox->addLayout(box);
	setLayout(principalBox);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray);
	pal.setColor(QPalette::Shadow, Qt::lightGray);
	setAutoFillBackground(true);
	setPalette(pal);
}

/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
void listNotificariGUI::connect()
{
	//srv.addObserver(this);
	QWidget::connect(adauga, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.adaugaLista(apartament1);
			loadList(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		}
	);

	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		srv.golesteLista();
		loadList(srv.getAllLista(), srv.nrApartamenteLista());
		});

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(numarApartamente->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
			loadList(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	QWidget::connect(afisare, &QPushButton::clicked, [&]() {
		auto tab = new tabel{ srv.getAllLista() };
		tab->setModal(false);
		tab->show();

		});

	QWidget::connect(Export, &QPushButton::clicked, [&]() {
		try {
			srv.writeToFile(numeFisier->text().toStdString());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		close();
		});
}

void tabelDetalii::init() {
	apartament = new QLineEdit;
	nume = new QLineEdit;
	suprafata = new QLineEdit;
	tipApartament = new QLineEdit;
	apartament->setReadOnly(true);
	nume->setReadOnly(true);
	suprafata->setReadOnly(true);
	tipApartament->setReadOnly(true);
	QFormLayout* form = new QFormLayout;
	apartament->setText(QString::number(locatar.getApartament()));
	nume->setText(QString::fromStdString(locatar.getNume()));
	suprafata->setText(QString::number(locatar.getSuprafata()));
	tipApartament->setText(QString::fromStdString(locatar.getTipApartament()));
	form->addRow("Apartament", apartament);
	form->addRow("Nume", nume);
	form->addRow("Suprafata", suprafata);
	form->addRow("Tip Apartament", tipApartament);
	setLayout(form);
}

//functie de update
//date de intrare:-
//date de isire:-
void CosCRUDGUI::update()
{
	loadTable(srv.getAllLista(), srv.nrApartamenteLista());
}

//initializare
//date de intrare:-
//date de isire:-
void CosCRUDGUI::init()
{
	this->setWindowTitle("Fereastra CosCRUDGUI");

	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;
	table = new QTableWidget{ 1, 4 };

	//butoane

	sterge = new QPushButton("&goleste lista");
	genereaza = new QPushButton("&genereaza lista");

	exit = new QPushButton("&exit");

	//QLineEdit
	numarApartamente = new QLineEdit;
	apart = new QLineEdit;
	apart->setReadOnly(true);
	QFormLayout* form = new QFormLayout;
	form->addRow("Numarul de apartamente de generat", numarApartamente);
	form->addRow("Numarul de apartamente din lista", apart);

	principalBox->addWidget(table);
	principalBox->addLayout(form);
	box->addWidget(sterge);
	box->addWidget(genereaza);
	box->addWidget(exit);
	principalBox->addLayout(box);
	setLayout(principalBox);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray);
	pal.setColor(QPalette::Shadow, Qt::lightGray);
	setAutoFillBackground(true);
	setPalette(pal);
}

/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
void CosCRUDGUI::connect()
{
	srv.addObserver(this);
	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		srv.golesteLista();
		//loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		});

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(numarApartamente->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
			//loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		srv.removeObserver(this);
		close();
		});
}

void CosCRUDGUI::loadTable(vector<Locatar>locatari, int numar) {

	table->clear();
	int l = table->rowCount();
	for (int i = 0; i < l; i++)
		table->removeRow(0);
	table->setItem(0, 0, new QTableWidgetItem("apartament"));
	table->setItem(0, 1, new QTableWidgetItem("nume"));
	table->setItem(0, 2, new QTableWidgetItem("suprafata"));
	table->setItem(0, 3, new QTableWidgetItem("tip apartament"));
	for (const auto& l : locatari) {
		table->insertRow(table->rowCount());
		table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(l.getApartament())));
		table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(l.getNume())));
		table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(QString::number(l.getSuprafata())));
		table->setItem(table->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(l.getTipApartament())));
	}
	apart->setText(QString::number(numar));
}


void CosV2CRUDGUI::update()
{
	loadList(srv.getAllLista(), srv.nrApartamenteLista());
}

//initializare
//date de intrare:-
//date de isire:-
void CosV2CRUDGUI::init()
{
	this->setWindowTitle("Fereastra CosV2CRUDGUI");

	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;
	list = new QListWidget;

	//butoane

	sterge = new QPushButton("&goleste lista");
	genereaza = new QPushButton("&genereaza lista");

	exit = new QPushButton("&exit");

	//QLineEdit
	numarApartamente = new QLineEdit;
	apart = new QLineEdit;
	apart->setReadOnly(true);
	QFormLayout* form = new QFormLayout;
	form->addRow("Numarul de apartamente de generat", numarApartamente);
	form->addRow("Numarul de apartamente din lista", apart);

	principalBox->addWidget(list);
	principalBox->addLayout(form);
	box->addWidget(sterge);
	box->addWidget(genereaza);
	box->addWidget(exit);
	principalBox->addLayout(box);
	setLayout(principalBox);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray);
	pal.setColor(QPalette::Shadow, Qt::lightGray);
	setAutoFillBackground(true);
	setPalette(pal);
}


void CosV2CRUDGUI::connect()
{
	srv.addObserver(this);
	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		srv.golesteLista();
		//loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		});

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(numarApartamente->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
			//loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		srv.removeObserver(this);
		close();
		});
}

void CosV2CRUDGUI::loadList(vector<Locatar>locatari, int numar) {

	list->clear();
	for (const auto& loc : locatari) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(loc.getNume()));
		list->addItem(item);
	}
}