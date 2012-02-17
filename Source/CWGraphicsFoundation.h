/*
//  CWGraphicsFoundation.h
//  Zangetsu
//
//  Created by Colin Wheeler on 12/24/10.
//  Copyright 2010. All rights reserved.
//

Copyright (c) 2011 Colin Wheeler

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


#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

#define CWCGColorFloat(_x_) (_x_ / 255)

extern CGRect CWCenteredRect(CGRect smallRect, CGRect largeRect);

extern CGContextRef CWCurrentCGContext();

extern void CWAddRoundedRectToPath(CGContextRef context,
								   CGRect rect,
								   float ovalWidth,
								   float ovalHeight);

extern void CWSaveAndRestoreCGContextState(CGContextRef ctx, void(^block)(void));

extern void CWContextDrawLinearGradientBetweenPoints(CGContextRef context, CGPoint point1, CGPoint point2,
											  CGFloat colora[4], CGFloat colorb[4]);

extern CGColorRef CWCreateCGColor(CGFloat r, CGFloat g, CGFloat b, CGFloat a);

extern CGColorRef CWCreateCGColorWithSpace(CGFloat r, CGFloat g, CGFloat b, CGFloat a, CGColorSpaceRef cspace);

#define CWCGColorMethod(_name_) extern CGColorRef CWCGColor##_name_(CGFloat alpha) CF_RETURNS_RETAINED

CWCGColorMethod(LightGray);
CWCGColorMethod(Gray);
CWCGColorMethod(DarkGray);
CWCGColorMethod(Blue);

#undef CWCGColorMethod
