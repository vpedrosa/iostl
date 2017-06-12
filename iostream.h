/**
 * Valentín Pedrosa Campoy
 * Under MIT License: https://github.com/vpedrosa/iostl/blob/master/LICENSE
 * Github: https://github.com/vpedrosa/iostl
 */

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <utility>

#ifndef THRESHOLD
#define THRESHOLD 10
#endif

/**
 * Esta cabecera es una adaptación de iostream para los contenedores principales de la STL.
 * Se han sobrecargado los operadores "<<" y ">>" para:
 * 		stack
 * 		queue
 * 		priority_queue
 * 		list
 * 		vector
 * 		deque
 * 		set
 * 		multiset
 * 		map
 * 		multimap
 * 		
 * La salida normal por pantalla será:
 * (tipo_contenedor:direccion_memoria)[tamaño]{elementos}
 * 
 * O en caso de que haya más elementos que el límite definido
 * (tipo_contenedor:direccion_memoria)[tamaño]{elemento_1,elemento_2,...,elemento_THERSHOLD, ... , elemento_n-THERSHOLD,...,elemento_n-1,elemento_n}
 * 
 * Un ejemplo:
 * (set:0x3bbca30f28d0)[100]{0,1,2,3,4,5,6,7,8,9,...,90,91,92,93,94,95,96,97,98,99}
 * 
 * El valor por defecto del límite es 10
 * Para modificarlo hay que definirlo antes de incluir este archivo:
 * 
 * 		#define THRESHOLD 20
 * 		#include "iostream.h"
 * 		
 * Y con eso modificaremos el límite de elementos a mostrar a 20.
 */

template<class T>
inline void sendHeader(std::ostream & os, const T &container,
		std::string type) {
	os << "(" << type << ":" << &container << ")[" << container.size() << "]";
}

template<class T, class const_iterator>
inline void sendList(std::ostream & os, const T &container,
		const_iterator &it) {
	os << "{";
	it = container.cbegin();
	bool may_truncate = (container.size() > THRESHOLD * 2);
	int current = 0;
	while (it != container.cend()) {
		if (may_truncate && current >= THRESHOLD) {
			it = container.cend();
			for (int i = 0; i < THRESHOLD; ++i)
				it--;

			may_truncate = false;
			os << "..." << ",";
		}
		os << *it;

		it++;
		if (it != container.cend())
			os << ",";
		it--;

		current++;
		it++;
	}

	os << "}";
}

template<class T, class const_iterator>
inline void sendMap(std::ostream & os, const T &container, const_iterator &it) {
	os << "{";
	it = container.cbegin();
	bool may_truncate = (container.size() > THRESHOLD * 2);
	int current = 0;
	while (it != container.cend()) {
		if (may_truncate && current >= THRESHOLD) {
			it = container.cend();
			for (int i = 0; i < THRESHOLD; ++i)
				it--;
			
			may_truncate = false;
			os << "..." << ",";
		}
		os << it->first << ":" << it->second;

		it++;
		if (it != container.cend())
			os << ",";
		it--;

		current++;
		it++;
	}

	os << "}";
}

/**
 * Output
 */

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::stack<T>& s) {
	sendHeader(os, s, "stack");
	os << "{top:" << s.top() << "}";
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::queue<T>& q) {
	sendHeader(os, q, "queue");
	os << "{front:" << q.front() << ",back:" << q.back() << "}";
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os,
		const std::priority_queue<T>& pq) {
	sendHeader(os, pq, "priority_queue");
	os << "{front:" << pq.front() << ",back:" << pq.back() << "}";
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::list<T>& l) {
	typedef typename std::list<T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, l, "list");
	sendList(os, l, it);
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::deque<T>& dq) {
	typedef typename std::deque<T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, dq, "deque");
	sendList(os, dq, it);
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::vector<T>& v) {
	typedef typename std::vector<T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, v, "vector");
	sendList(os, v, it);
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::set<T>& set) {
	typedef typename std::set<T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, set, "set");
	sendList(os, set, it);
	return os;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os, const std::multiset<T>& ms) {
	typedef typename std::multiset<T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, ms, "multiset");
	sendList(os, ms, it);
	return os;
}

template<class T, class K>
inline std::ostream& operator <<(std::ostream& os, const std::map<K,T>& map) {
	typedef typename std::map<K,T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, map, "map");
	sendMap(os, map, it);
	return os;
}

template<class T, class K>
inline std::ostream& operator <<(std::ostream& os, const std::multimap<K,T>& mm) {
	typedef typename std::multimap<K,T>::const_iterator const_iterator;
	const_iterator it;
	sendHeader(os, mm, "multimap");
	sendMap(os, mm, it);
	return os;
}

template<class T, class K>
inline std::ostream& operator<< (std::ostream&os, const std::pair<T,K> & pair) {
	os << "(" << pair.first << "," << pair.second << ")";
	return os;
}

/**
 * Input
 */

template<class T>
inline std::istream& operator >>(std::istream& is, std::stack<T>& s) {
	T new_item = T();
	is >> new_item;
	s.push(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::queue<T>& q) {
	T new_item = T();
	is >> new_item;
	q.push(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::priority_queue<T>& pq) {
	T new_item = T();
	is >> new_item;
	pq.push(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::deque<T>& dq) {
	T new_item = T();
	is >> new_item;
	dq.push_back(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::vector<T>& v) {
	T new_item = T();
	is >> new_item;
	v.push_back(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::list<T>& l) {
	T new_item = T();
	is >> new_item;
	l.push_back(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::set<T>& set) {
	T new_item = T();
	is >> new_item;
	set.insert(new_item);
	return is;
}

template<class T>
inline std::istream& operator >>(std::istream& is, std::multiset<T>& ms) {
	T new_item = T();
	is >> new_item;
	ms.insert(new_item);
	return is;
}

template<class T, class K>
inline std::istream& operator >>(std::istream& is, std::map<K,T>& m) {
	T new_item = T();
	K new_key = K();
	is >> new_key;
	is >> new_item;
	m.insert(make_pair(new_key,new_item));
	return is;
}

template<class T, class K>
inline std::istream& operator >>(std::istream& is, std::multimap<K,T>& mm) {
	T new_item = T();
	K new_key = K();
	is >> new_key;
	is >> new_item;
	mm.insert(make_pair(new_key,new_item));
	return is;
}


