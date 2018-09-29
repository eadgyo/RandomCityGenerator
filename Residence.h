#ifndef __RESIDENCE__
#define __RESIDENCE__
#include <vector>
#include "Building.h"
#include "ResidenceSettings.h"

struct Residence;
#include "AdvancedForm.h"
#include "tools.h"
#include "MainResidence.h"
struct Residence
{
	Residence();

	bool createBuilding(AForm& _AForm, MainResidence& _mainResidence);//a ajouter AForm devient un building

	void createRng(Residence& _residence, int iLevel, int _iResRemaining = 2);
	
	void createRng(int iLevel, int _iResRemaining = MAXL);

	vector<Building> vecBuilding;

	int iResRemaining;

};
#endif