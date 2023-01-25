#include <iostream>
#include "entities.h"
#include <gmp.h>
using namespace std;

int main()
{
	cout << "Test successful." << endl;
	mpq_t number;
	mpq_init(number); // Intialize to 0/1
	mpq_set_si(number, 2, 1); // Set to 2/1
	cout << number;
	return 0;
}
