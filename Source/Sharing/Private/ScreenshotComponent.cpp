//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#include "SharingPrivatePCH.h"

void UScreenshotComponent::OnRegister()
{
	Super::OnRegister();
	
	GEngine->GameViewport->OnScreenshotCaptured().AddUObject(this, &UScreenshotComponent::ScreenshotCapturedDelegate_Handler);
}

void UScreenshotComponent::OnUnregister()
{
	Super::OnUnregister();
	
	GEngine->GameViewport->OnScreenshotCaptured().RemoveAll(this);
}

void UScreenshotComponent::ScreenshotCapturedDelegate_Handler(int32 Width, int32 Height, const TArray<FColor>& Pixels)
{
	if (ScreenshotCapturedTexture.IsBound())
	{
		UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height);
		FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
		
		uint8* MipData = static_cast<uint8*>(Mip.BulkData.Lock(LOCK_READ_WRITE));
		
		for(int32 y = 0; y < Height; y++)
		{
			uint8* DestPtr = &MipData[(Height - 1 - y) * Width * sizeof(FColor)];
			int32 PixelIndex = (Height - 1 - y) * Width;
			if (Pixels.IsValidIndex(PixelIndex))
			{
				FColor* SrcPtr = const_cast<FColor*>(&Pixels[PixelIndex]);
				for(int32 x = 0; x < Width; x++)
				{
					*DestPtr++ = SrcPtr->B;
					*DestPtr++ = SrcPtr->G;
					*DestPtr++ = SrcPtr->R;
					*DestPtr++ = 0xFF;
					SrcPtr++;
				}
			}
		}
		
		Mip.BulkData.Unlock();

		Texture->SRGB = true;
		Texture->CompressionSettings = TC_Default;
		Texture->UpdateResource();

		ScreenshotCapturedTexture.Broadcast(Texture);
	}
	
	if (ScreenshotCapturedImage.IsBound())
	{
		ScreenshotCapturedImage.Broadcast(FScreenshotImage(Pixels,Width,Height));
	}
}
