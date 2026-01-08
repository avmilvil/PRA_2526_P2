#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
	class BSTree {
		private:
			int nelem;
		    	BSNode<T>* root;
    			BSNode<T>* search(BSNode<T>* n, T e) const {
        			if (!n){
					throw std::runtime_error("Element not found!");
				}

        			if (e == n->elem){
				       	return n;
				}

        			if (e < n->elem){ 
					return search(n->left, e);
				}

        			return search(n->right, e);
    			}

		    	BSNode<T>* insert(BSNode<T>* n, T e) {
	        		if (!n) {
            				nelem++;
            				return new BSNode<T>(e);
        			}

        			if (e == n->elem){
				       	throw std::runtime_error("Duplicated element!");
				}

			        if (e < n->elem){
				       	n->left = insert(n->left, e);
				} else {
					n->right = insert(n->right, e);
				}

			        return n;
    			}

    			void print_inorder(std::ostream& out, BSNode<T>* n) const {
			        if (!n) return;
	        		print_inorder(out, n->left);
        			out << n->elem << " ";
				print_inorder(out, n->right);
    			}


    			BSNode<T>* remove(BSNode<T>* n, T e) {
			        if (!n){
				       	throw std::runtime_error("Element not found!");
				}

			        if (e < n->elem){
				       	n->left = remove(n->left, e);
				}

			        else if (e > n->elem){
					n->right = remove(n->right, e);
				}

			        else {
		           
			        	if (!n->left) {
		                		BSNode<T>* right_sub = n->right;
	                			delete n;
                				return right_sub;
            				}

            				if (!n->right) {
                				BSNode<T>* left_sub = n->left;
				                delete n;
				                return left_sub;
				        }

            				T m = max(n->left);
            				n->elem = m;
            				n->left = remove_max(n->left);
        			}

        			return n;
    			}

    			T max(BSNode<T>* n) const {
        			if (!n){
					throw std::runtime_error("Árbol vacío");
				}

			        while (n->right) n = n->right;
			        return n->elem;
			}

		    	BSNode<T>* remove_max(BSNode<T>* n) {
	 		       	if (!n->right) {
			       		BSNode<T>* left_sub = n->left;
		               		delete n;
            				return left_sub;
        			}

        			n->right = remove_max(n->right);
        			return n;
    			}

       			void delete_cascade(BSNode<T>* n) {
        			if (!n) return;
        			delete_cascade(n->left);
        			delete_cascade(n->right);
        			delete n;
    			}

	public:
    		BSTree() : nelem(0), root(nullptr) {}

		int size() const { 
			return nelem; 
		}

    		T search(T e) const { 
			return search(root, e)->elem; 
		}
	
    		T operator[](T e) const { 
			return search(e); 
		}
	
    		void insert(T e) { 
			root = insert(root, e); 
		}
		
		friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        		bst.print_inorder(out, bst.root);
        		return out;
    		}

    		void remove(T e) { 
			root = remove(root, e); 
			nelem--;
		}

    		~BSTree() { 
			delete_cascade(root); 
		}

};

#endif

