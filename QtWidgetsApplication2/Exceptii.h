#pragma once
#include <string>
using std::string;

//clasa pentru exceptiile din repo
class RepoException
{
private:
	string mesaj;

public:
	/*constructor
	* date de intrare:-msg-string
	* date de iesire:-
	*/
	RepoException(string msg) : mesaj(msg) {
	}
	/*returneaza mesajul
	* date de inrtrare:-
	* date de iesire:-mesaj-string
	*/
	string getMesaj() const;
};

//clasa pentru exceptiile din validare
class ValidException
{
private:
	string mesaj;
public:
	/*constructor
	* date de intrare:-msg-string
	* date de iesire:-
	*/
	ValidException(string msg) :mesaj(msg) {

	}
	/*returneaza mesajul
	* date de inrtrare:-
	* date de iesire:-mesaj-string
	*/
	string getMesaj() const;
};

//clasa de exceptii pentru exceptiile din lista de notificari
class listaException
{
private:
	string mesaj;
public:
	/*constructor
	* date de intrare:-msg-string
	* date de iesire:-
	*/
	listaException(string msg) :mesaj{ msg } {};

	/*returneaza mesajul
	* date de inrtrare:-
	* date de iesire:-mesaj-string
	*/
	string getMesaj() const;
};
