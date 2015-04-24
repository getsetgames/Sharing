//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "SharingPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogSharing);

#define LOCTEXT_NAMESPACE "Sharing"

class FSharing : public ISharing
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FSharing, Sharing )

void FSharing::StartupModule()
{

}


void FSharing::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
