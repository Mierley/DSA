#include <functional>
#include <iostream>
#include <vector>

using namespace std;

vector <vector<int>> arrays;

void print()
{
	cout << endl << "answer:" << endl;
	for (auto array : arrays)
	{
		for (auto item : array)
			cout << item <<  " ";

		cout << endl;
	}
	cout << endl << "---------------------" << endl;
}

void insertMany(vector<int> values) {

	if (arrays.empty())
		arrays.push_back(values);
	
	else {
		vector<int> head = arrays[0];
		if (head.size() > values.size())
		{
			reverse(arrays.begin(), arrays.end());
			arrays.push_back(values);
			reverse(arrays.begin(), arrays.end());
			//print();
		}

		else {
			vector<int> merged(values.size() + head.size());
			int i = 0, j = 0;
			for (int k = 0; k < merged.size();k++)
			{
				if (j >= head.size()) {
					merged[k] = values[i++];
				}
				else if (i >= values.size()) {
					merged[k] = head[j++];
				}
				else if (values[i] <= head[j]) {
					merged[k] = values[i++];
				}
				else { merged[k] = head[j++]; }
			}
			arrays.erase(arrays.begin());
			//print();
			insertMany(merged);
		}
	}
}


void insert(int value) {
	vector<int> values(1);
	values[0] = value;
	insertMany(values);
}


bool search(int value) {
	for (auto array : arrays)
	{
		int l = 0, r = array.size();

		while (l < r) {
			int mid = (l + r) / 2;

			if (array[mid] < value)
				l = mid + 1;
			else if (array[mid] > value)
				r = mid;
			else
				return true;
		}
	}
	return false;
}

int main()
{

	int n;
	while(cin >> n)
	{
		insert(n);
		print();
	}
	//vector<int> my;
	//my.push_back(1);
	//my.push_back(2);
	//my.push_back(3);
	//insertMany(my);

	////insert(4);
	////insert(6);
	////insert(1);

	//vector<int> my2;
	//my2.push_back(7);
	//my2.push_back(8);
	//my2.push_back(9);
	//my2.push_back(10);
	//insertMany(my2);

	//vector<int> my3;
	//my3.push_back(11);
	//my3.push_back(12);
	//my3.push_back(13);
	//
	//insertMany(my3);

	
}
