#include "list.h"
#include "Node.h"
#include <string>

using namespace std;

class Hash{
public:
	Hash();
	static const size_t tableSize = 29;
	void insert(string name, double weight);
	Node* retrieve(string name);
	void clear();
	double operator[](string name);
	size_t size() const { return used; }

private:
	//Node *Head; dont need to put here, already done in list.h and node.h

	list data[tableSize];

	size_t used;
	size_t hash(const string& s) const{
		int result = 0;
		for (unsigned int i = 0; i < s.length(); i++){
			result = result + static_cast<int>(s[i]);
		}
		return(result%tableSize);
	}
};
