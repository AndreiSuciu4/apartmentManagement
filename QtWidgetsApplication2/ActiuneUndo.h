#pragma once
#include "Locatar.h"
#include "AbstractRepo.h"

class ActiuneUndo
{
public:
	/*functie pur virtuala
	* date de intrare:-
	* date de iesire:-
	*/
	virtual void doUndo() = 0;
	/*destructorul virtual
	* date de intrare:-
	* date de iesire:-
	*/
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Locatar locatarAdaugat;
	AbstractRepo& repo;
public:
	/*constuctor
	* date de intrare:-repo-referinta la LocatarRepository
	*				  -loc-referinta la locatar
	* date de iesire:-
	*/
	UndoAdauga(AbstractRepo& repo, const Locatar& loc) :repo{ repo }, locatarAdaugat{ loc }{};

	/*doUndo
	* date de intrare:-
	* date de iesire:-
	*/
	void doUndo() override {
		repo.stergereLocatar(locatarAdaugat.getApartament());
	}

};

class UndoSterge : public ActiuneUndo {
private:
	Locatar locatarSters;
	AbstractRepo& repo;
public:
	/*constuctor
	* date de intrare:-repo-referinta la LocatarRepository
	*				  -loc-referinta la locatar
	* date de iesire:-
	*/
	UndoSterge(AbstractRepo& repo, const Locatar& loc) :repo{ repo }, locatarSters{ loc }{};
	/*doUndo
	* date de intrare:-
	* date de iesire:-
	*/
	void doUndo() override {
		repo.adaugaLocatar(locatarSters);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	Locatar locatarModificat;
	AbstractRepo& repo;
public:
	/*constuctor
	* date de intrare:-repo-referinta la LocatarRepository
	*				  -loc-referinta la locatar
	* date de iesire:-
	*/
	UndoModifica(AbstractRepo& repo, const Locatar& loc) :repo{ repo }, locatarModificat{ loc }{};
	/*doUndo
	* date de intrare:-
	* date de iesire:-
	*/
	void doUndo() override {
		repo.modificareLocatar(locatarModificat);
	}
};

