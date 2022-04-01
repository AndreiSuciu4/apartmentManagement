#pragma once
#include "Locatar.h"
#include "Exceptii.h"

//clasa validareLocatar
class ValidareLocatar
{
public:
	/*functi de validare locatar
	* date de intrare:loc-referinta catre Locatar
	* date de iesire:-
	* functia arunca exceptia "apartament invalid!" daca apartament<1
	* functia arunca exceptia "nume invalid!" daca nume==""
	* functia arunca exceptia "suprafata invalida!" daca suprafata<0
	* functia arunca exceptia "tip apartament invalid!" daca tipApartament==""
	*/
	void valideazaLocatar(const Locatar& loc) const;
};

