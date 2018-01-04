#include "Node.h"

class list
{
public:
	list(){
		head = nullptr;
	}
	~list(){
		destroyList(head);
	}
	void append(double weight, string name){
		head = append(head, weight, name);
	}
	Node* findValue(string name){
		return findValue(head, name);
	}
	int getSize(){
		return getSize(head);
	}

	void destroyList(){
		destroyList(head);
	}

private:
	Node* head;

	void destroyList(Node *n){
		if (n->next != nullptr){
			destroyList(n->next);
		}
		delete n;
	}

	Node* append(Node *n, double w, string nm){
		if (n == nullptr){
			return new Node(w, nm);
		}
		else{
			n->next = append(n->next, w, nm);
		}
		return n;
	}

	Node* findValue(Node *n, string nm){
		if (n->name == nm){
			return n;
		}
		else if (n->next != nullptr){
			return findValue(n->next, nm);
		}
		else{
			return nullptr;
		}
	}

	int getSize(Node *n, int i = 0){
		if (n != nullptr){
			++i;
			return getSize(n->next, i);
		}
		return i;
	}
};
