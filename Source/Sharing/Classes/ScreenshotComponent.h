//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "ScreenshotComponent.generated.h"

USTRUCT(BlueprintType)
struct FScreenshotImage
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY()
	TArray<FColor> Pixels;
	
	UPROPERTY()
	int32 Width;
	
	UPROPERTY()
	int32 Height;
		
	FScreenshotImage()
	{
		
	}

	FScreenshotImage(TArray<FColor> InPixels, int32 InWidth, int32 InHeight)
	: Pixels(InPixels), Width(InWidth), Height(InHeight)
	{
		
	}
	
	FORCEINLINE bool IsValid() const
	{
		return Pixels.Num() > 0 && Width > 0 && Height > 0;
	}
};

UCLASS(ClassGroup=Utility, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UScreenshotComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScreenshotCapturedTextureDelegate, UTexture2D*, Texture);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScreenshotCapturedImageDelegate, FScreenshotImage, Image);
	
	UPROPERTY(BlueprintAssignable)
	FScreenshotCapturedTextureDelegate ScreenshotCapturedTexture;
	
	UPROPERTY(BlueprintAssignable)
	FScreenshotCapturedImageDelegate ScreenshotCapturedImage;
	
public:
	void OnRegister() override;
	void OnUnregister() override;

private:	
	void ScreenshotCapturedDelegate_Handler(int32 Width, int32 Height, const TArray<FColor>& Pixels);	
};
