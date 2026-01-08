#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
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
	    	ListLinked<TableEntry<V>>* table; 

    		int h(const std::string& key){
	        	int sum = 0;
		        for (size_t i = 0; i < key.size(); i++){
				sum += static_cast<int>(key[i]);
			}

		        return sum % max;
    		}

	public:
    		HashTable(int size) : n(0), max(size) {
			if(size <= 0) throw std::invalid_argument("Size must be > 0.");
			n = 0;
			max = size;
		        table = new ListLinked<TableEntry<V>>[max];
	    	}

		~HashTable() {
	        	delete[] table;
    		}

		int capacity() const{ 
			return max; 
		}

		int entries() override{ 
			return n; 
		}

   		void insert(std::string key, V value) override {
		        int idx = h(key);
        		TableEntry<V> entry(key, value);
        		if (table[idx].search(TableEntry<V>(key)) != -1) {
            			throw std::runtime_error("Key '" + key + "' already exists!");
       			}

		        table[idx].prepend(entry);
       	 		n++;
    		}

    		V search(std::string key) override {
		        int idx = h(key);
		        TableEntry<V> entry(key);
		        int pos = table[idx].search(entry);
		        if (pos == -1){
			       	throw std::runtime_error("Key '" + key + "' not found!");
			}

		        return table[idx].get(pos).value;
    		}

		V remove(std::string key) override {
       	 		int idx = h(key);
		        TableEntry<V> entry(key);
		        int pos = table[idx].search(entry);
		        if (pos == -1){
				throw std::runtime_error("Key '" + key + "' not found!");
			}

		        V val = table[idx].get(pos).value;
		        table[idx].remove(pos);
		        n--;
		        return val;
		}	

		V operator[](std::string key){ 
			return search(key); 
		}

	    	friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
		        out << "HashTable [entries: " << ht.n << ", capacity: " << ht.max << "]\n";
		        out << "==============\n\n";
		        for (int i = 0; i < ht.max; i++) {
		            out << "== Cubeta " << i << " ==\n\n";
		            out << "List => " << ht.table[i] << "\n\n";
		        }

		        out << "==============\n";
		        return out;
	    	}
};

#endif

