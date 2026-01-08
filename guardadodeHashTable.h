#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2526_P1/ListLinked.h"  

template <typename V>
class HashTable : public Dict<V> {
	private:
    		int n;
    		int max;
    		ListLinked<TableEntry<V>>** table;

   		int h(std::string key) const {
        		int sum = 0;
        		for (size_t i = 0; i < key.size(); i++) {
            			sum += int(key.at(i));
        		}

        		return sum % max;
    		}

	public:
		HashTable(int size) : n(0), max(size) {
	        	table = new ListLinked<TableEntry<V>>*[max];
    		}

    		~HashTable() {
        		delete[] table;
    		}

    		int capacity() const {
        		return max;
    		}

    		void insert(std::string key, V value) override {
        		int pos = h(key);
        		TableEntry<V> entry(key, value);
	        	if (table[pos].search(entry) != -1) {
        	    		throw std::runtime_error("Clave ya existe");
        		}

	        	table[pos].append(entry);
        		n++;
    		}
