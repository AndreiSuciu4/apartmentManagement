#include "ValidareLocatar.h"

void ValidareLocatar::valideazaLocatar(const Locatar& loc) const
/*functi de validare locatar
	* date de intrare:loc-referinta catre Locatar
	* date de iesire:-
	* functia arunca exceptia "apartament invalid!" daca apartament<1
	* functia arunca exceptia "nume invalid!" daca nume==""
	* functia arunca exceptia "suprafata invalida!" daca suprafata<0
	* functia arunca exceptia "tip apartament invalid!" daca tipApartament==""
	*/
{
	if (loc.getApartament() < 1)
		throw ValidException("apartament invalid!\n");

	if (loc.getNume().size() == 0)
		throw ValidException("nume invalid!\n");

	if (loc.getSuprafata() < 0)
		throw ValidException("suprafata invalida\n");

	if (loc.getTipApartament().size() == 0)
		throw ValidException("tip apartament invalid!\n");
}