//
//  Created by Derek van Vliet on 2015-03-25.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "SharingPrivatePCH.h"

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#import "IOSView.h"
#endif

void USharingFunctions::Share(FString EmailSubject, FString Message, FString Url, FVector2D Origin)
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
