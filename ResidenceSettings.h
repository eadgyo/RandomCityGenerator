#ifndef __RESIDENCESET__
#define __RESIDENCESET__
#include "BuildingSettings.h"
#include <vector>

//singleton
class ResidenceSet
{
public:
//==============================
//          Singleton
//==============================
	static ResidenceSet& getInstance()
	{
		static ResidenceSet instance;
		return instance;
	};
	int getVecSize()
	{
		return vecBuildSet.size();
	};

//==============================
//          Variables
//==============================
	vector<BuildingSet> vecBuildSet;

private:
//==============================
//         Constructor
//==============================
	ResidenceSet()
	{
		BuildingSet l_buildingSet[4];
		MinMax l_MinMax, l_MinMax2;
		l_MinMax.xMin = 50;
		l_MinMax.xMax = 200;
		l_MinMax2.xMin = MAXL - 5;
		l_MinMax2.xMax = MAXL;
		l_buildingSet[0].define("Hopital",l_MinMax, 400);
		vecBuildSet.push_back(l_buildingSet[0]);
		vecBuildSet[0].setLevel(l_MinMax2,0);
		l_MinMax2.xMin = 0;
		l_MinMax2.xMax = 1;
		vecBuildSet[0].setLevel(l_MinMax2,1);
		l_MinMax2.xMin = 0;
		l_MinMax2.xMax = 1;
		vecBuildSet[0].setLevel(l_MinMax2,2);
		

		/*
		l_MinMax.xMin = 100;
		l_MinMax.xMax = 200;
		l_MinMax2.xMin = 0;
		l_MinMax2.xMax = 10;
		l_buildingSet[1].define("Armee",l_MinMax);
		l_buildingSet[1].setLevel(l_MinMax2,1);
		vecBuildSet.push_back(l_buildingSet[1]);

		l_MinMax.xMin = 40;
		l_MinMax.xMax = 70;
		l_MinMax2.xMin = 1;
		l_MinMax2.xMax = 20;
		l_buildingSet[2].define("Boutique",l_MinMax);
		l_buildingSet[2].setLevel(l_MinMax2,1);
		vecBuildSet.push_back(l_buildingSet[2]);
		l_MinMax2.xMin = 0;
		l_MinMax2.xMax = 1;



		l_MinMax.xMin = 30;
		l_MinMax.xMax = 40;
		l_MinMax2.xMin = 2;
		l_MinMax2.xMax = 4;
		l_buildingSet[3].define("Pharmacie",l_MinMax);
		l_buildingSet[3].setLevel(l_MinMax2,1);
		vecBuildSet.push_back(l_buildingSet[3]);*/

	};


};
#endif