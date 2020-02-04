#include <iostream>
using namespace std;
struct part
{
	int partnumber;
	int modelnumber;
	float cost;
};

int main()
{
	part part1;
	part1.partnumber = 7529;
	part1.modelnumber = 172;
	part1.cost = 281.45F;

	part part2;
	part2.partnumber = 3429;
	part2.modelnumber = 10;
	part2.cost = 1895.99F;


	cout << "Part : " << part1.partnumber << endl;
	cout << "Model : " << part1.modelnumber << endl;
	cout << "Cost1 + Cost2 : " << part1.cost + part2.cost << endl;
	return 0;
}