#pragma once
#define INITIAL_CAPACITY 5


template<typename Element>
class IteratorVector;

template<typename Element>
class vectorDinamic
{
private:
	int lg;
	int cp;
	Element* vect;
	/*functia de redimensionare
	date de intrare:-
	date de iesire:-
	*/
	void redimensionare();
public:
	/* constructorul clasei
	* date de intrare:-
	* date de iesire:-
	*/
	vectorDinamic();
	//rules of 3
	/*constructorul de copiere
	* date de intrare - ot -referinta la vectorDinamic
	* date de iesire:-
	*/
	vectorDinamic(const vectorDinamic& ot);

	/*operatorul de assignment
	* date de intrare:-ot-referint la vectorDinamic
	* date de iesire:-referinta la vectorDinamic
	*/
	vectorDinamic& operator=(const vectorDinamic& ot);

	/*destructorul clasei
	* date de intrare:-
	* date de iesire:-
	*/
	~vectorDinamic();

	/*adaugare in vector
	* date de intrare:-referinta la element
	* date de iesire:-
	*/
	void push_back(const Element& el);

	/*functia de stergere
	* date de intrare-poz-int
	* date de iesire:-
	*/
	void erase(int poz) noexcept;

	/*functia de returnare a lungimii listei
	* date de intrare:-
	* date de iesire:lg-tip int
	*/
	int size() const noexcept;

	/*functia de returnare a unui element de pe o pozitie data
	* date de intrare:-poz-int
	* date de iesire:-vect[poz]-referinta la element
	*/
	Element& at(int poz) const noexcept;

	/*functia de inlocuire a unui element cu un alt element din vector
	* date de intrare:-el-referinta la element
	*				  -poz-tip int
	* date de iesire:-
	*/
	void set(const Element&, int poz) noexcept;

	friend class IteratorVector<Element>;

	/*functia de iterare a vectorului
	* date de intrare:-
	* date de iesire:-IteratorVector-de tip iteratorVector
	*/
	IteratorVector<Element> begin() noexcept;

	/*functia de iterare a vectorului incepand de pe ultima pozitie
	* date de intrare:-
	* date de iesire:-IteratorVector-de tip iteratorVector
	*/
	IteratorVector<Element> end() noexcept;

};

/*functia de redimensionare
date de intrare:-
date de iesire:-
*/
template<typename Element>
void vectorDinamic<Element>::redimensionare() {
	cp = 2 * cp;
	Element* aux = new Element[2 * cp];
	for (int i = 0; i < lg; i++)
	{
		aux[i] = vect[i];
	}
	delete[] vect;
	vect = aux;
}

/* constructorul clasei
* date de intrare:-
* date de iesire:-
*/
template<typename Element>
vectorDinamic<Element> ::vectorDinamic() :cp{ INITIAL_CAPACITY }, lg{ 0 }, vect{ new Element[INITIAL_CAPACITY] } {}


/*constructorul de copiere
* date de intrare - ot -referinta la vectorDinamic
* date de iesire:-
*/
template<typename Element>
vectorDinamic<Element>::vectorDinamic(const vectorDinamic& ot) {
	vect = new Element[ot.cp];
	for (int i = 0; i < ot.lg; i++)
		vect[i] = ot.vect[i];
	lg = ot.lg;
	cp = ot.cp;
}

/*operatorul de assignment
* date de intrare:-ot-referint la vectorDinamic
* date de iesire:-referinta la vectorDinamic
*/
template<typename Element>
vectorDinamic<Element>& vectorDinamic<Element>:: operator=(const vectorDinamic<Element>& ot) {
	if (this == &ot)
		return *this;
	delete[] vect;
	vect = new Element[ot.cp];
	for (int i = 0; i < ot.lg; i++)
		vect[i] = ot.vect[i];
	cp = ot.cp;
	lg = ot.lg;
	return *this;
}

/*destructorul clasei
* date de intrare:-
* date de iesire:-
*/
template<typename Element>
vectorDinamic<Element>:: ~vectorDinamic() {
	delete[] vect;
}

/*adaugare in vector
* date de intrare:-referinta la element
* date de iesire:-
*/
template<typename Element>
void vectorDinamic<Element>::push_back(const Element& el)
{
	if (lg == cp)
		redimensionare();
	vect[lg++] = el;

}

/*functia de stergere
* date de intrare-poz-int
* date de iesire:-
*/
template<typename Element>
void vectorDinamic<Element>::erase(int poz) noexcept
{
	for (int i = poz; i < lg; i++)
		vect[i] = vect[i + 1];
	lg = lg - 1;

}

/*functia de returnare a lungimii listei
* date de intrare:-
* date de iesire:lg-tip int
*/
template<typename Element>
int vectorDinamic<Element>::size() const noexcept {
	return lg;
}

/*functia de returnare a unui element de pe o pozitie data
* date de intrare:-poz-int
* date de iesire:-vect[poz]-referinta la element
*/
template<typename Element>
Element& vectorDinamic<Element>::at(int poz) const noexcept {
	return vect[poz];
}

/*functia de inlocuire a unui element cu un alt element din vector
* date de intrare:-el-referinta la element
*				  -poz-tip int
* date de iesire:-
*/
template<typename Element>
void vectorDinamic<Element>::set(const Element& el, int poz) noexcept {
	vect[poz] = el;
}

/*functia de iterare a vectorului
* date de intrare:-
* date de iesire:-IteratorVector-de tip iteratorVector
*/
template<typename Element>
IteratorVector<Element> vectorDinamic<Element>::begin() noexcept {
	return IteratorVector<Element>(*this);
}

/*functia de iterare a vectorului incepand de pe ultima pozitie
* date de intrare:-
* date de iesire:-IteratorVector-de tip iteratorVector
*/
template<typename Element>
IteratorVector<Element> vectorDinamic<Element>::end() noexcept {
	return IteratorVector<Element>(*this, lg);
}

template<typename Element>
class IteratorVector {
private:
	int curent;
	const vectorDinamic<Element>& v;
public:
	/*constructor
	* date de intrare:v-referinta catre vectorDinamic
	* date de iesire:-
	*/
	IteratorVector(const vectorDinamic<Element>& v) noexcept;

	/*constructor
	* date de intrare:v-referinta catre vectorDinamic
	*                 poz-tip int
	* date de iesire:-
	*/
	IteratorVector(const vectorDinamic<Element>& v, int lg) noexcept;

	/*verificam daca iteratorul este valid
	* date de intrare:-
	* date de iesire:-true-daca e valid
	*				 -false-daca nu e valid
	*/
	bool valid() noexcept;

	/*returneaza elementul curent iterat
	* date de intrare:-
	* date de iesire:-elment-referinta la Element
	*/
	Element& element() const noexcept;

	/*itereaza urmatorul element
	* date de intrare:-
	* date de iesire:-
	*/
	void next() noexcept;

	/*operatorul*-returneaza elementul de pe pozitia curenta
	* date de intrare:-
	* date de iesire:-element-referinta la element
	*/
	Element& operator*() noexcept;

	/*operatorul ++-returneaza iteratorul vectorului de la pozitia curent+1
	* date de intrare:-
	* date de iesire-referinta la IteratorVector
	*/
	IteratorVector<Element>& operator++() noexcept;

	/*iteratorul ==
	* date de intrare:-ot-referinta la iterator
	* date de iesire:-true-daca curent==ot.curent
					 -false-in caz contrar
	*/
	bool operator==(const IteratorVector<Element>& ot)noexcept;

	/*iteratorul !=
	* date de intrare:-ot-referinta la iterator
	* date de iesire:-true-ot este un iterator diferit fata de iteratorul curent ( ambii itereaza vectori dinamici de acelasi tip de elemente)
					 -false-in caz contrar
	*/
	bool operator!=(const IteratorVector<Element>& ot)noexcept;

};

/*constructor
* date de intrare:v-referinta catre vectorDinamic
* date de iesire:-
*/
template<typename Element>
IteratorVector<Element>::IteratorVector(const vectorDinamic<Element>& v) noexcept :v{ v }, curent{ 0 }{}

/*constructor
* date de intrare:v-referinta catre vectorDinamic
*                 poz-tip int
* date de iesire:-
*/
template<typename Element>
IteratorVector<Element>::IteratorVector(const vectorDinamic<Element>& v, int lg) noexcept : v{ v }, curent{ lg } {}

/*verificam daca iteratorul este valid
* date de intrare:-
* date de iesire:-true-daca e valid
*				 -false-daca nu e valid
*/
template<typename Element>
bool IteratorVector<Element>::valid() noexcept {
	return curent < v.lg;
}

/*returneaza elementul curent iterat
* date de intrare:-
* date de iesire:-elment-referinta la Element
*/
template<typename Element>
Element& IteratorVector<Element>::element() const noexcept {
	return v.vect[curent];
}

/*itereaza urmatorul element
* date de intrare:-
* date de iesire:-
*/
template<typename Element>
void IteratorVector<Element>::next() noexcept {
	curent++;
}

/*operatorul*-returneaza elementul de pe pozitia curenta
* date de intrare:-
* date de iesire:-element-referinta la element
*/
template<typename Element>
Element& IteratorVector<Element>:: operator*() noexcept {
	return element();
}

/*operatorul ++-returneaza iteratorul vectorului de la pozitia curent+1
* date de intrare:-
* date de iesire-referinta la IteratorVector
*/
template<typename Element>
IteratorVector<Element>& IteratorVector<Element>:: operator++() noexcept {
	next();
	return *this;
}

/*iteratorul ==
* date de intrare:-ot-referinta la iterator
* date de iesire:-true-daca curent==ot.curent
				 -false-in caz contrar
*/
template<typename Element>
bool IteratorVector<Element>:: operator==(const IteratorVector<Element>& ot)noexcept {
	return curent = ot.curent;
}

/*iteratorul !=
* date de intrare:-ot-referinta la iterator
* date de iesire:-true-ot este un iterator diferit fata de iteratorul curent ( ambii itereaza vectori dinamici de acelasi tip de elemente)
				 -false-in caz contrar
*/
template<typename Element>
bool IteratorVector<Element>:: operator!=(const IteratorVector<Element>& ot)noexcept {
	return !(*this == ot);
} 