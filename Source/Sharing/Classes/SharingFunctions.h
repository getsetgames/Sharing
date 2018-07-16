//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "ScreenshotComponent.h"
#include "SharingFunctions.generated.h"

UCLASS(NotBlueprintable)
class USharingFunctions : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * Triggers a native share sheet
	 * @param EmailSubject If the user selects to share by email, this will be set as the subject
	 * @param Message If specified, this will be set as the message body in any sharing activity
	 * @param Url If specified, this will be set as the link in any sharing activity
	 * @param Origin If specified, this will be the origin of the sharing popover on iPad
	 */
	UFUNCTION(BlueprintCallable, Category = Sharing)
	static void Share(FString EmailSubject, FString Message, FString Url, FScreenshotImage Image, FVector2D Origin = FVector2D(0,0));
};
