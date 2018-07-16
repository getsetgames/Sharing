//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "SharingPrivatePCH.h"
#include "SharingComponent.h"

void USharingComponent::OnRegister()
{
	Super::OnRegister();
	
	USharingComponent::SharingFinishedDelegate.AddUObject(this, &USharingComponent::SharingFinished_Handler);
}

void USharingComponent::OnUnregister()
{
	Super::OnUnregister();
	
	USharingComponent::SharingFinishedDelegate.RemoveAll(this);
}

USharingComponent::FSharingFinishedDelegate USharingComponent::SharingFinishedDelegate;
