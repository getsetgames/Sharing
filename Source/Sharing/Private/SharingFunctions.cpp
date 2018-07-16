//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "SharingPrivatePCH.h"
#include "SharingFunctions.h"

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#import "IOSView.h"
#endif

void USharingFunctions::Share(FString EmailSubject, FString Message, FString Url, FScreenshotImage Image, FVector2D Origin)
{
#if PLATFORM_IOS
	NSMutableArray *items = [NSMutableArray array];
	
	if (Message.Len() > 0)
	{
		[items addObject:Message.GetNSString()];
	}
	
	if (Url.Len() > 0)
	{
		[items addObject:[NSURL URLWithString:Url.GetNSString()]];
	}
	
	if (Image.IsValid())
	{
		int32 Width = Image.Width;
		int32 Height = Image.Height;
		
		TArray<uint8> NewPixels;
		NewPixels.Reserve(Image.Pixels.Num() * 4);
		
		for(int32 y = Height-1; y >= 0; y--)
		{
			int32 PixelIndex = (Height - 1 - y) * Width;
			if (Image.Pixels.IsValidIndex(PixelIndex))
			{
				FColor* SrcPtr = const_cast<FColor*>(&Image.Pixels[PixelIndex]);
				for(int32 x = 0; x < Width; x++)
				{
					NewPixels.Add(SrcPtr->R);
					NewPixels.Add(SrcPtr->G);
					NewPixels.Add(SrcPtr->B);
					NewPixels.Add(SrcPtr->A);
					
					SrcPtr++;
				}
			}
		}
		
		CGColorSpaceRef ColorSpace = CGColorSpaceCreateDeviceRGB();
		CGContextRef BitmapContext = CGBitmapContextCreate(NewPixels.GetData(), Width, Height, 8, 4*Width, ColorSpace,  kCGImageAlphaNoneSkipLast);
		CFRelease(ColorSpace);
		
		CGImageRef cgImage = CGBitmapContextCreateImage(BitmapContext);
		CGContextRelease(BitmapContext);
		
		UIImage* SharingImage = [UIImage imageWithCGImage:cgImage];
		CGImageRelease(cgImage);
		
		[items addObject:SharingImage];
	}
	
	UIActivityViewController* activityViewController = [[UIActivityViewController alloc] initWithActivityItems:items applicationActivities:nil];
	
	if (activityViewController)
	{
		if (EmailSubject.Len() > 0)
		{
			[activityViewController setValue:EmailSubject.GetNSString() forKey:@"subject"];
		}
		
		[activityViewController setCompletionHandler:^(NSString *activityType, BOOL completed) {
								   USharingComponent::SharingFinishedDelegate.Broadcast(FString(activityType), completed);
		 }];
		
		IOSAppDelegate* AppDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];

		if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
		{
			UIPopoverController* Popover = [[[UIPopoverController alloc] initWithContentViewController:activityViewController] autorelease];
			
			if (Popover)
			{
				UIView* View = AppDelegate.IOSController.view;
				CGRect Rect = CGRectMake(Origin.X, Origin.Y, 100, 100);
				[Popover presentPopoverFromRect:Rect inView:View permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
			}
		}
		else
		{
			[AppDelegate.IOSController presentViewController:activityViewController animated:YES completion:nil];
		}
	}
	
	[activityViewController release];
#endif
}
