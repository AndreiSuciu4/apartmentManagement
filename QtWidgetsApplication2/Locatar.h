#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;


//clasa locatar
class Locatar
{
private:
	int apartament;
	string nume;
	double suprafata;
	string tipApartament;

public:
	Locatar() noexcept :apartament{ 0 }, suprafata{ 0 } {};
	/*constructor
	* date de intrare:-apart-int
	*				  -nume-string
	*				  -suprafata-double
	*				  -tip-string
	* date de iesire:-
	*/
	Locatar(int apart, string nume, double suprafata, string tip) : apartament{ apart }, nume{ nume }, suprafata{ suprafata }, tipApartament{ tip }{
	}

	/*returneaza pozitia locatarului
	* date de intrare:
	* date de iesire-pozitie-int
	*/
	int getApartament() const noexcept;

	/*returneaza numele locatarului
	* date de intrare:-
	* date de iesire:-nume-string
	*/
	string getNume() const;

	/*returneaza suprafata
	* date de intrare:-
	* date de iesire:-suprafata-double
	*/
	double getSuprafata() const noexcept;

	/*returneaza tipul apartamentului
	* date de intrare:-
	* date de iesire-tipApartament-string
	*/
	string getTipApartament() const;

	/*seteaza pozitia cu o valoare
	* date de intrare:-poz-int
	* date de iesire:-
	*/

	void setApartament(int apart) noexcept;

	/*seteaza numele cu o valoare
	* date de intrare:-num-string
	* date de iesire:-
	*/
	void setNume(string num);

	/*seteaza suprafata apartamentului cu o valoare
	* date de intrare:-supra-double
	* date de iesire:-
	*/
	void setSuprafata(double supra) noexcept;

	/*seteaza tipul apartamentului cu o valoare
	* date de intrare-tip-string
	* date de iesire:-
	*/
	void setTipApartament(string tip);

	/*verificam de cate ori se copie obiectul locatar in aplicatie
	* date de intrare:-ot-referinta la Locatar
	* date de iesire:-
	*/
	Locatar(const Locatar& ot) : apartament{ ot.apartament }, nume{ ot.nume }, suprafata{ ot.suprafata }, tipApartament{ ot.tipApartament }{
		//cout << "se face copie\n";
	}
};

