#pragma once

#include "ModuleManager.h"

class ISharing : public IModuleInterface
{

public:

	static inline ISharing& Get()
	{
		return FModuleManager::LoadModuleChecked< ISharing >( "Sharing" );
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "Sharing" );
	}
};

