#include "Exceptii.h"

/*returneaza mesajul
* date de inrtrare:-
* date de iesire:-mesaj-string
*/
string RepoException::getMesaj() const {
	return mesaj;
}

/*returneaza mesajul
* date de inrtrare:-
* date de iesire:-mesaj-string
*/
string ValidException::getMesaj() const {
	return mesaj;
}

/*returneaza mesajul
* date de inrtrare:-
* date de iesire:-mesaj-string
*/
string listaException::getMesaj() const
{
	return mesaj;
}
