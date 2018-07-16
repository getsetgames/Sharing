//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "Components/ActorComponent.h"
#include "SharingComponent.generated.h"

UCLASS(ClassGroup=Sharing, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class USharingComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FSharingFinishedDelegate, FString, bool);
	
	static FSharingFinishedDelegate SharingFinishedDelegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSharingFinishedDynDelegate, FString, Service, bool, Success);
	
	UPROPERTY(BlueprintAssignable)
	FSharingFinishedDynDelegate SharingFinished;

	void OnRegister() override;
	void OnUnregister() override;
	
private:
	void SharingFinished_Handler(FString Service, bool Success) { SharingFinished.Broadcast(Service, Success); }
};
