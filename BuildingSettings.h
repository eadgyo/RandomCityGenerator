#ifndef __BUILDINGSET__
#define __BUILDINGSET__
#include <iostream>
#include <vector>
#include "MinMax.h"
using namespace std;
struct BuildingSet
{
	string sName;
	MinMax mmTaille;
	vector<MinMax> vecMinMax;
	float fdistMin;

	BuildingSet()
	{};

	BuildingSet(string _sName, MinMax _mmTaille, float _fdistMin)
	{
		sName = _sName;
		mmTaille = _mmTaille;
		fdistMin = _fdistMin;
		for(int i=0; i<LEVEL_MAX + 1; i++)
		{
			MinMax l_MinMax;
			l_MinMax.xMin = 0;
			l_MinMax.xMax = INT_MAX;
			vecMinMax.push_back(l_MinMax);
		}
	};

	void define(string _sName, MinMax _mmTaille, float _fdistMin)
	{
		sName = _sName;
		mmTaille = _mmTaille;
		fdistMin = _fdistMin;
		vecMinMax.clear();
		for(int i=0; i<LEVEL_MAX; i++)
		{
			MinMax l_MinMax;
			l_MinMax.xMin = 0;
			l_MinMax.xMax = INT_MAX;
			vecMinMax.push_back(l_MinMax);
		}
	};

	void setLevel(MinMax _MinMax, int _iLevel)
	{
		MinMax l_MinMax;
		for(int i=vecMinMax.size()-1; i>=_iLevel; i--)
		{
			l_MinMax = _MinMax;
			if(vecMinMax[i].xMin > _MinMax.xMin)
				l_MinMax.xMin = vecMinMax[i].xMin;
			vecMinMax[i] = l_MinMax;
		}
		for(int i=_iLevel; i<vecMinMax.size(); i++)
		{
			l_MinMax = _MinMax;
			if(vecMinMax[i].xMax < _MinMax.xMax)
				l_MinMax.xMax = vecMinMax[i].xMax;
			vecMinMax[i] = l_MinMax;
		}
	};

};

#endif