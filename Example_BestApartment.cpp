/*
Example_BestApartment.cpp

Problem:
Pick the block to live on which has the minimum maximum distance to any of the destinations Gym, Store, Office.
eg: If the maximum distance to any of the destinations for apt1 is 12 blocks, and the maximum distance to
any of the destinations for apt2 is 4 blocks, apt2 is the best apartment.
Each city block may have one destination, two destinations, all three destinations, or no destination.
Note: Our city streets are straight. Their ends do not circle back to their beginnings...

Solution:
Use a map (int, vector<bool>) to represent the street.
For each block, move two pointers right and left to find the distances of destinations in other blocks from the current block.

Author:
Matthew Breit (github.com/mattsprojects)
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int FindBestBlock(map<int, vector<bool>> &streetMap)
{
	int bestBlock = 0; // Block number of the "best block" based on walking distance to destinations.
	int longestWalk = INT_MAX; // the length in blocks of the longest walk from the best block to any destination.

	map<int, vector<bool>>::iterator it;

	for (it = streetMap.begin(); it != streetMap.end(); it++)
	{
		int largestDistToDest = 0;
		cout << endl;
		cout << "Block : " << it->first << endl;

		for (vector<bool>::iterator bt = it->second.begin(); bt != it->second.end(); bt++)
		{
			int distToDest = 0;

			// if the current block already has a gym, store, or office, then the distance to it is 0.
			if (*bt == true)
				cout << " Dest : " << bt - it->second.begin() + 1 << " : true " << " distL: 0" << " distR: 0" << endl;
			else
			{
				// If the current block doesn't have one of the destinations, then find the closest block that does.
				// We'll send out two "scout" pointers to search.
				// One will walk down the street to the right, and the other to the left, looking for destinations.
				auto scoutR = it;
				auto scoutL = it;
				int distR = 0;
				int distL = 0;

				while (scoutR->second.at(bt - it->second.begin()) == false)
				{
					distR++;
					scoutR++;
					if (scoutR == streetMap.end())
					{
						distR = INT_MAX;
						break;
					}
				}

				while (scoutL->second.at(bt - it->second.begin()) == false)
				{
					if (scoutL == streetMap.begin())
					{
						distL = INT_MAX;
						break;
					}
					distL++;
					scoutL--;
				}

				distToDest = min(distL, distR);

				cout << " Dest : " << bt - it->second.begin() + 1 << " : " << (*bt ? "true " : "false") << " distL: " << distL << " distR: " << distR << endl;
			}

			if (distToDest > largestDistToDest)
				largestDistToDest = distToDest;
		}

		cout << "Block : " << it->first << " Longest walk to reach a destination : " << largestDistToDest << endl;
		cout << endl;

		if (largestDistToDest < longestWalk)
		{
			longestWalk = largestDistToDest;
			bestBlock = it->first;
		}
	}

	return bestBlock;
}

int main()
{
	// our map of main street
	map<int, vector<bool>> mainStreet =
	{

		{1,{true,true,false}}, // block number one: has a gym, has a store, has no office.
		{2,{true,false,false}}, // block number two: has a gym, has no store, has no office.
		{3,{false,false,false}},
		{4,{false,false,true}},
		{5,{false,true,true}},
		{6,{false,true,false}},
		{7,{true,false,true}}
	};

	int bestBlock = FindBestBlock(mainStreet);
	cout << "Best Block to Live on : " << bestBlock << endl;

	return 0;

}
