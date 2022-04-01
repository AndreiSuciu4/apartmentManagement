#include "MyGUIModel.h"
#include <string>

/*initilizare
date de intrare:-
date de iesire:-
*/
void MyGUIModel::init()
{
	this->setWindowTitle("Administrare bloc");
	this->setWindowIcon(QIcon("apart.jpg"));

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
	afisare = new QPushButton("&afisare");
	sterge = new QPushButton("&sterge");
	cauta = new QPushButton("&cauta");
	modifica = new QPushButton("&modifica");
	undo = new QPushButton("&undo");
	listaNotificari = new QPushButton("&lista notificari");
	CosCRUD = new QPushButton("&CosCRUDGUI");
	CosV2CRUD = new QPushButton("&CosV2CRUDGUI");
	CosReadOnly = new QPushButton("&CosReadOnlyGUI");
	adaugaCos = new QPushButton("&adauga cos");
	Export = new QPushButton("&export");
	genereaza = new QPushButton("&genereaza");
	exit = new QPushButton("&exit");

	combo = new QComboBox;
	combo->addItem("Filtrare");
	combo->addItem("Filtrare tip");
	combo->addItem("Filtrare suprafata");

	comboSortari = new QComboBox;
	comboSortari->addItem("Sortare");
	comboSortari->addItem("sortare suprafata");
	comboSortari->addItem("sortare nume");
	comboSortari->addItem("sortare tip si suprafata");

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

	lista = new QListView();
	modelLista = new ListModel(lista, srv);
	lista->setModel(modelLista);
	lista->setUniformItemSizes(true);


	box->addWidget(lista);
	box->addWidget(combo);
	box->addWidget(comboSortari);
	
	box1->addStretch();
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
	form->addRow("Apartament", apartament);
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

	//auto tab = new tabel1{ srv.getAllService() };
	//tab->setModal(false);
	//principalBox->addWidget(table);
	//butoaneFiltrare->addWidget(filtrareTip);
	setLayout(principalBox);

	tabelNou =  new QTableView();
	model = new TableModel(tabelNou, srv);
	tabelNou->setModel(model);
	principalBox->addWidget(tabelNou);

}

/*afisare lista utilizand QListWidget
* date de intrare:-vector de Locatar
* date de iesire:
*/
void MyGUIModel::loadList(vector<Locatar> locatari)
{
}

/*
* conectam butoanele cu functiile
* date de intrare:
* date de iesire:
*/
void MyGUIModel::connect()
{

	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		close();
		});

	QObject::connect(lista->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lista->selectionModel()->selectedIndexes().isEmpty()) {
			modelLista->setSelectedItem(-1);
			return;
		}
		auto selIndex = lista->selectionModel()->selectedIndexes().at(0);
		apartament->setText(QString::number(selIndex.data(Qt::UserRole).toInt()));
		nume->setText(selIndex.data(Qt::DisplayRole).toString());
		suprafata->setText(QString::number(srv.cautareApartamentService(selIndex.data(Qt::UserRole).toInt()).getSuprafata()));
		tipApartament->setText(QString::fromStdString(srv.cautareApartamentService(selIndex.data(Qt::UserRole).toInt()).getTipApartament()));
		modelLista->setSelectedItem(selIndex.row());
		auto tab = new tabelDetalii1{ srv.cautareApartamentService(selIndex.data(Qt::UserRole).toInt()) };
		tab->show();
		});

	QWidget::connect(combo, &QComboBox::currentIndexChanged, [&]() {
		if (combo->currentIndex() == 1)
		{
			auto tab = new tabel1{ srv.filtrareTipApartament(tipApartament->text().toStdString()) };
			tab->show();
		}
		if (combo->currentIndex() == 2)
		{
			double suprafata1{ 0 };
			try {
				suprafata1 = std::stod(suprafata->text().toStdString());
				auto tab = new tabel1{ srv.filtrareSuprafata(suprafata1) };
				tab->show();
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
		}
		});

	QWidget::connect(comboSortari, &QComboBox::currentIndexChanged, [&]() {
		if (comboSortari->currentIndex() == 1)
		{
			auto tab = new tabel1{ srv.sortareSuprafata() };
			tab->show();
		}
		if (comboSortari->currentIndex() == 2)
		{
			auto tab = new tabel1{ srv.sortareNume() };
			tab->show();
		}
		if (comboSortari->currentIndex() == 3)
		{
			auto tab = new tabel1{ srv.sortareApartamentSuprafata() };
			tab->show();
		}
		});

	QWidget::connect(CosCRUD, &QPushButton::clicked, [&]() {
		auto* cos = new CosCRUDGUI1(srv);
		cos->show();
		});

	QWidget::connect(CosV2CRUD, &QPushButton::clicked, [&]() {
		auto* cos = new CosV2CRUDGUI1(srv);
		cos->show();
		});

	QWidget::connect(CosReadOnly, &QPushButton::clicked, [&]() {
		auto listNot = new CosReadOnlyGUI1(srv);
		listNot->show();
		});

	QWidget::connect(listaNotificari, &QPushButton::clicked, [&]() {
		auto listaNot = new listNotificariGUI1(srv);
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
		auto tab = new tabelDetalii1{ srv.cautareApartamentService(item->data(Qt::UserRole).toInt()) };
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
	Undo();
	afisareLocatar();
}

/*conectam butonul adauga cu functia de adaugare din service
* date de intrare:
* date de iesire:
*/
void MyGUIModel::adaugaLocatar()
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
void MyGUIModel::afisareLocatar()
{
	QWidget::connect(afisare, &QPushButton::clicked, [&]() {
		auto tabel = new tabel1{ srv.getAllService() };
		tabel->show();
		});
}

/*conectam butonul sterge cu functia de stergere din service
* date de intrare:
* date de iesire:
*/
void MyGUIModel::stergeLocatar()
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
void MyGUIModel::cautaLocatar()
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
			auto tab = new tabel1(loc);
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
void MyGUIModel::modificaLocatar()
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


/*conectam butonul undo cu functia undo din service
* date de intrare:
* date de iesire:
*/
void MyGUIModel::Undo()
{
	QWidget::connect(undo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			loadList(srv.getAllService());
			tab(srv.getAllService());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
}

void MyGUIModel::tab(vector<Locatar> locatar)
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
void tabel1::init()
{
	this->setWindowTitle("Tabel");
	this->setWindowIcon(QIcon("lista.jpg"));
	box = new QHBoxLayout;
	setModal(true);//nu putem accesa alte ferestre cat timp tabelul e pornit
	QTableView* tabelNou = new QTableView();
	TableModel1* model = new TableModel1(tabelNou, locatari);
	tabelNou->setModel(model);
	
	box->addWidget(tabelNou);
	setLayout(box);
}

void tabelDetalii1::init() {
	this->setWindowTitle("Detalii locatar");
	this->setWindowIcon(QIcon("detalii.jpg"));
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


