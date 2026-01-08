#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
	Node<T>* first;
	int n;
public:
	ListLinked(){
		first = nullptr;
		n = 0;
	}

	~ListLinked() override{
		Node<T>* aux;
		while(first != nullptr){
			aux = first->next;
			delete first;
			first = aux;
		}

				
	}

	void insert(int pos, T e){
		if(pos < 0){
			throw std::out_of_range("Posición inválida.");
		}

		if(pos == 0){
			first = new Node<T>(e, first);
			n++;
			return;
		}

		Node<T>* current = first;
		for(int i = 0; i < pos-1 && current != nullptr; i++){
			current = current->next;
		}

		if(current == nullptr){
			throw std::out_of_range("Posición inválida");
		}

		current->next = new Node<T>(e, current->next);
		n++;
	}

	T remove(int pos){
		if(pos < 0 ){
			throw std::out_of_range("Posición inválida.");
		}

		Node<T>* aux;
		if(pos == 0){
			if(first == nullptr){
				throw std::out_of_range("Posición inválida.");
			}
			aux = first;
			T value = aux->data;
			first = first->next;
			delete aux;
			n--;
			return value;
		}

		Node<T>* current = first;

		for(int i = 0; i < pos-1 && current != nullptr; i++){
			current = current->next;
		}

		if(current == nullptr || current->next == nullptr){
			throw std::out_of_range("Posición inválida.");
		}

		aux = current->next;
		current->next = aux->next;
		
		T value = aux->data;
		delete aux;
		n--;
		return value;
	}

	T get(int pos) const{
		if(pos < 0){
			throw std::out_of_range("Posición inválida.");
		}

		if(pos == 0){
			if(first == nullptr){
				throw std::out_of_range("Posición inválida.");
			}
			return first->data;
		}

		Node<T>* current = first;

		for(int i = 0; i < pos && current != nullptr; i++){
			current = current->next;
		}

		if(current == nullptr){
			throw std::out_of_range("Posición inválida.");
		}

		return current->data;
	}
	
	int search(T e) const{
		Node<T>* current = first;
		int pos = 0;

		while(current != nullptr){
			if(current->data == e){
				return pos;
			}
			current = current->next;
			pos++;
		}

		return -1;
	}

	bool empty() const{
		return n == 0;
	}

	int size() const {
		return n;
	}

	void append(T e){
		insert(n, e);
	}

	void prepend(T e){
		insert(0, e);
	}

	T operator[](int pos){
		if(pos < 0 || pos >= n){
			throw std::out_of_range("Posición inválida.");
		}

		Node<T>* current = first;

		for(int i = 0; i < pos; i++){
			current = current->next;	
		}

		return current->data;
			
	}


	template <typename U>
	friend std::ostream& operator<<(std::ostream& out, const ListLinked<U>& list);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list){
	Node<T>*current = list.first;
	out << "[";
	while(current != nullptr){
		out << current->data;
		if(current->next != nullptr){
			out<<", ";
		}
		current = current->next;
	}
	
	out<<"]";
	return out;
}

#endif


