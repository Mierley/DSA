#include <iostream>
#include <array>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <optional>

using namespace std;


template<class string, int CAPACITY>
class LinkedHashMap {

	array<list<string>, CAPACITY> buckets;

public:

	// We can pass the capacity of the hash table to the constructor
	//	LinkedHashMap(int capacity){
	//		this->CAPACITY = capacity;
	//	}

	virtual int getIndex(string key) {

		// taking an instance of hash struct
		auto hashfunc = hash<string>();

		// hashing function
		int hashcode = hashfunc(key);
		// the hashcode is of type unsigned int

		// the hashcode could be negative so we use abs function
		// to take the absolute value of the hashcode

		// compression function
		return abs(hashcode) % CAPACITY;
	}

	virtual int size() {

		int temp = 0;
		for (auto bucket : buckets) {
			if (bucket.size() > 0)
				temp += bucket.size();
			//			for (auto entry : bucket) {
			//				temp++;
			//			}
		}

		return temp;
	}

	virtual bool isEmpty() {
		return size() == 0;
	}

	virtual int capacity() {
		return CAPACITY;
	}

	virtual double loadFactor() {
		return 1.0 * size() / capacity();
	}

	virtual string* findFirst(string key) {
		int index = getIndex(key);

		// Pointer to the bucket of the key
		auto bucketP = &buckets[index];

		if (!bucketP->empty()) {

			for (auto it = bucketP->begin(); it != bucketP->end(); it++) {

				if (compareString(&(*it), key)) {
					return &(*it);
				}
			}
		}

		return NULL;
	}
	virtual bool compareString(char a, string& b)
	{
		for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++)
			if (a[i] != b[i])
				return false;

		return true;
	}
	virtual bool containsKey(string key) {
		auto entry_p = findFirst(key);
		return entry_p != NULL;
	}

	virtual void put(string key) {

		int index = getIndex(key);

		// Pointer to the bucket of the key
		auto bucketP = &buckets[index];

		// the key is not in the hashmap
		if (!containsKey(key)) {

			// insert a new key
			bucketP->push_back(key);
		}
		
	}

	virtual void remove(string key) {
		if (containsKey(key)) {
			int index = getIndex(key);

			auto bucketP = &buckets[index];

			// pointer to the entry of the key
			auto entryP = findFirst(key);

			// We are passing the entry of the key
			bucketP->remove(*entryP);
		}
	}
};

int main()
{

	int n, m;
	string s;
	cin >> n;
	LinkedHashMap<string, size_t(100000)> mySet;
	while (n--)
	{
		cin >> s;
			mySet.put(s);
	}
	cin >> m;
	vector <string> unique;
	while (m--)
	{
		cin >> s;
		if (!mySet.containsKey(s))
		{
			unique.push_back(s);
			mySet.put(s);
		}
	}
	cout << unique.size() << endl;
	for (auto u : unique)
		cout << u << endl;
	return 0;
}