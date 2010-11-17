//
//  CWSystemInfo.h
//  Zangetsu
//
//  Created by Colin Wheeler on 11/14/10.
//  Copyright 2010. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define kSystemMajorVersion @"majorVersion"
#define kSystemMinorVersion @"minorVersion"
#define kSystemBugFixVersion @"bugfixVersion"


@interface CWSystemInfo : NSObject {}

+(NSDictionary *)hostVersion;
+(NSString *)hostVersionString;

@end