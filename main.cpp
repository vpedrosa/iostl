#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>

#define THRESHOLD 10
#include "iostream.h"

using namespace std;


int main() {
	
	set<int> a = set<int>();

	for(int i = 0; i<100; i++) {
		a.insert(i);
	}
	cout << a << endl;
}