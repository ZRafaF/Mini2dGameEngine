#include "EntityMaster.h"

EntityMaster::EntityMaster(Global* globalVariables, std::string myName) : componentHandler(globalVariables)
{

	global = globalVariables;
	name = myName;
}

EntityMaster::~EntityMaster()
{

}

void EntityMaster::beforePlay()
{
	componentHandler.beforePlay();
}


void EntityMaster::beginPlay()
{
	componentHandler.beginPlay();
}

void EntityMaster::process()
{
	componentHandler.process();
	
	transform = componentHandler.transform;
}

void EntityMaster::endGame()
{
	componentHandler.endGame();
}

void EntityMaster::draw()
{
	componentHandler.draw();
}