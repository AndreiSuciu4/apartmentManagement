#include "Locatar.h"


/*returneaza apartamentul locatarului
* date de intrare:-
* dae de iesire-apartament-int
*/
int Locatar::getApartament() const noexcept {
	return apartament;
}

/*returneaza numele locatarului
* date de intrare:-
* date de iesire:-nume-string
*/
string Locatar::getNume() const {
	return nume;
}

/*returneaza suprafata
* date de intrare:-
* date de iesire:-suprafata-double
*/
double Locatar::getSuprafata() const noexcept {
	return suprafata;
}

/*returneaza tipul apartamentului
* date de intrare:-
* date de iesire-tipApartament-string
*/
string	Locatar::getTipApartament() const {
	return tipApartament;
}

/*seteaza pozitia cu o valoare
* date de intrare:-poz-int
* date de iesire:-
*/

/*seteaza apartamentul cu o valoare
* date de intrare-apart-int
* date de iesire:-
*/
void Locatar::setApartament(int apart) noexcept
{
	apartament = apart;
}

/*seteaza numele cu o valoare
* date de intrare:-num-string
* date de iesire:-
*/
void Locatar::setNume(string num)
{
	nume = num;
}

/*seteaza suprafata apartamentului cu o valoare
* date de intrare:-supra-double
* date de iesire:-
*/
void Locatar::setSuprafata(double supra) noexcept
{
	suprafata = supra;
}

/*seteaza tipul apartamentului cu o valoare
* date de intrare-tip-string
* date de iesire:-
*/
void Locatar::setTipApartament(string tip)
{
	tipApartament = tip;
}
