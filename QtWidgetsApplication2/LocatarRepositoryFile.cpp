#include "LocatarRepositoryFile.h"
#include "Locatar.h"
#include "Exceptii.h"
#include <fstream>

/*citeste din fisier
* date de intrare:-
* date de iesire:-
* programul arunca eroare daca nu s-a putut deschide fisierul
*/
void LocatarRepositoryFile::loadFromFile()
{
    std::ifstream f(fileName);
    if (!f.is_open()) {
        throw RepoException("nu s-a putut deschide fisierul " + fileName);
    }
    while (!f.eof()) {
        int apart;
        f >> apart;
        if (f.eof())
            break;
        std::string nume;
        f >> nume;
        double suprafata;
        f >> suprafata;
        std::string tip;
        f >> tip;
        Locatar loc{ apart,nume,suprafata,tip };
        LocatarRepository::adaugaLocatar(loc);
    }
    f.close();

}

/*scrie in fisier
* date de intrare:-
* date de iesire:-
* programul arunca eroare daca nu s-a putut deschide fisierul
*/
void LocatarRepositoryFile::writeToFile()
{
    std::ofstream f(fileName);
    //f.open(fileName, std::ios::app);
    if (!f.is_open())
        throw RepoException("nu s-a putut deschide fisierul");
    for (const auto& l : getAll())
    {
        f << l.getApartament();
        f << std::endl;
        f << l.getNume();
        f << std::endl;
        f << l.getSuprafata();
        f << std::endl;
        f << l.getTipApartament();
        f << std::endl;
    }
    f.close();
}

/*adauga locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
* aplicatia arunca eroarea "locatar existent!" daca apartamentul a fost deja adaugat
*/
void LocatarRepositoryFile::adaugaLocatar(const Locatar& loc)
{
    LocatarRepository::adaugaLocatar(loc);
    writeToFile();
}

/*stergere locatar
* date de intrare:-apartament-int
* date de iesire:-
* programul arunca eroarea "locatar inexistent!" daca nu exista apartamentul dorit
*/
void LocatarRepositoryFile::stergereLocatar(const int& apartament)
{
    LocatarRepository::stergereLocatar(apartament);
    writeToFile();
}

/*modifica locatar in repo
* date de intrare:-loc-referinta la Locatar
* date de iesire:-
* aplicatia arunca eroarea "locatar inexistent!" daca nu exista locatari pe pozitie dorita
*/
void LocatarRepositoryFile::modificareLocatar(const Locatar& loc)
{
    LocatarRepository::modificareLocatar(loc);
    writeToFile();
}

/*cautare apartament
* date de intrare:-apartament-int
* date de iesire:-referinta la Locatar
* programul arunca eroarea "apartament inexistent" daca nu exista apartamentul in lista
*/
const Locatar& LocatarRepositoryFile::cautareApartament(const int& apart) const
{
    return LocatarRepository::cautareApartament(apart);
}

/*returneaza locatarii
* date de intrare:-
* date de iesire:-locatari-referinta la vector
*/
const vector<Locatar>& LocatarRepositoryFile::getAll() noexcept
{
    return LocatarRepository::getAll();
}

/*returneaza numarul de apartamente din repo
* date de intrare:-
* date de iesire:numarul de apartamente-int
*/
int LocatarRepositoryFile::getSize() const noexcept
{
    return LocatarRepository::getSize();
}