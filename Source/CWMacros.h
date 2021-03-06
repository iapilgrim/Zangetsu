/*
 *  CWMacros.h
 *  Gitty
 *
 *  Created by Colin Wheeler on 5/17/09.
 *  Copyright 2009. All rights reserved.
 *
 
 Copyright (c) 2012 Colin Wheeler
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */
#define Z_HOST_OS_IS_MAC_OS_X !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#pragma mark - General Functions
#define NSSET(...) [NSSet setWithObjects: __VA_ARGS__, nil]

#define NSCOLOR(r,g,b,a) [NSColor colorWithCalibratedRed:r green:g blue:b alpha:a]
#define NSDEVICECOLOR(r,g,b,a) [NSColor colorWithDeviceRed:r green:g blue:b alpha:a]

#pragma mark - Log Functions

#ifdef DEBUG
#	define CWPrintClassAndMethod() NSLog(@"%s%i:\n",__PRETTY_FUNCTION__,__LINE__)
#	define CWDebugLog(args...) NSLog(@"%s %i: %@",__PRETTY_FUNCTION__,__LINE__,[NSString stringWithFormat:args])
#else
#	define CWPrintClassAndMethod() /**/
#	define CWDebugLog(args...) /**/
#endif

#define CWLog(args...) NSLog(@"%s %i: %@",__PRETTY_FUNCTION__,__LINE__,[NSString stringWithFormat:args]);

#define CWDebugLocationString() [NSString stringWithFormat:@"%s[%i]",__PRETTY_FUNCTION__,__LINE__]

#define CWConditionalLog(cond,args...) \
do { \
	if((cond)){ \
		NSLog(@"%s%i: %@",__PRETTY_FUNCTION__,__LINE__,[NSString stringWithFormat:args]); \
	} \
} while(0);
	

#pragma mark - GCD Macros

#define CWGCDPriorityQueueLow() dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW,0)
#define CWGCDPriorityQueueNormal() dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0)
#define CWGCDPriorityQueueHigh() dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH,0)
#define CWGCDPriorityQueueBackground() dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND,0)
