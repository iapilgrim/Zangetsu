/*
//  NSManagedObjectContextAdditions.h
//  Zangetsu
//
//  Created by Colin Wheeler on 12/22/11.
//  Copyright (c) 2011. All rights reserved.
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

#import <CoreData/CoreData.h>

@interface NSManagedObjectContext (CWNSManagedObjectContextAdditions)

#ifdef DEBUG

-(NSString *)cw_debugName;

-(void)cw_setDebugName:(NSString *)cwdebugname;

#endif

-(NSManagedObjectContext *)cw_newChildContextWithConcurrencyType:(NSManagedObjectContextConcurrencyType)type;

-(NSUInteger)cw_countForEntity:(NSString *)entityName error:(NSError **)error;

-(NSArray *)cw_allEntitiesOfName:(NSString *)entityName 
				   withPredicate:(NSPredicate *)predicate 
						   error:(NSError **)error;

-(NSArray *)cw_allEntitiesOfName:(NSString *)entityName 
				   withPredicate:(NSPredicate *)predicate 
					  properties:(NSArray *)properties 
				 sortDescriptors:(NSArray *)sortDescriptors
						   error:(NSError **)error;
@end