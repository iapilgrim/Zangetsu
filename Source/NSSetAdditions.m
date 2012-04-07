/*
//  NSSetAdditions.m
//  Zangetsu
//
//  Created by Colin Wheeler on 11/15/10.
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

#import "NSSetAdditions.h"


@implementation NSSet (CWNSSetAdditions)

/**
 Ruby Inspired method for enumerating over Objects in a set
 
 This method is really a wrapper for NSArrays -enumerateObjectsUsingBlock
 now and makes the code a little more conscice. It enumerates over all the
 objects in the set or until the bool pointer is set to YES.
 
 @param block a block taking a id and BOOL pointer arguments
 */
-(void)cw_each:(void (^)(id obj, BOOL *stop))block 
{	
	[self enumerateObjectsUsingBlock:block];
}

/**
 Enumerates over all the objects in a set or until the blocks stop pointer is set to YES
 
 Enumerates over all the objects in a set. This method creates its own dispatch_queue_t
 and gives it a unique label such as "com.Zangetsu.NSSetAdditions_ConncurrentEach" appended
 with a UUID string. This method then concurrently enumerates all objects or until the 
 stop pointer is set to yes and waits until all blocks have finished executing before exiting.
 
 @param block a Block taking a id and BOOL* arguments
 */
-(void)cw_eachConcurrentlyWithBlock:(void (^)(id obj,BOOL *stop))block 
{	
	dispatch_group_t group = dispatch_group_create();
	dispatch_queue_t queue = dispatch_queue_create(CWUUIDCStringPrependedWithString(@"com.Zangetsu.NSSetAdditions_ConncurrentEach_"), DISPATCH_QUEUE_CONCURRENT);
	__block BOOL _stop = NO;

	for(id object in self){

		if (_stop) { break; }

		dispatch_group_async(group, queue, ^{
			block(object,&_stop);
		});
	}

	dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
	dispatch_release(group);
	dispatch_release(queue);
}

/**
 Enumerates over all the object in a set till a block returns YES & returns that, otherwise returns nil
 
 Enumerates over all the objects in a set calling block and passing in a object from the set and checking
 to see if the return value is YES or NO. As soon as any block returns YES then this method exits and
 returns the object that it passed to the block that returned YES. Otherwise if no block returns YES then
 this method simply returns nil.
 
 @param block a Block taking a id argument and expecting a BOOL return value
 @return an object if any block returned YES, otherwise nil
 */
-(id)cw_findWithBlock:(BOOL (^)(id obj))block
{
	for(id obj in self){
		if(block(obj)){
			return obj;
		}
	}
	return nil;
}

/**
 Enumerates over all objects in a set and returns all objects where the block callback returned YES
 
 This method allows you to deeply inspect all objects in a set and return multiple objects you have
 an interest in. This method creates a new set and adds the objects it passed in to blocks that
 returned YES to that set.
 
 @param block a block taking an id argument which is an object in the set and returning a BOOL value
 @return a NSSet with all objects where blocks returned YES or an empty NSSet
 */
-(NSSet *)cw_findAllWithBlock:(BOOL (^)(id obj))block
{
	NSMutableSet *results = [[NSMutableSet alloc] init];
	for (id obj in self) {
		if (block(obj)) {
			[results addObject:obj];
		}
	}
	return results;
}

/**
 Enumerates over all the objects with a block till one returns YES otherwise returns NO
 
 This method enumerates over all the objects in a set till a block callback returns YES,
 otherwise it returns NO. 
 
 @param a block taking an id argument and returning a BOOL value
 @return a BOOL value with YES if a block returned YES otherwise returns NO
 */
-(BOOL)cw_isObjectInSetWithBlock:(BOOL (^)(id obj))block
{
	id obj = nil;
	obj = [self cw_findWithBlock:block];
	return (obj) ? YES : NO;
}

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

/**
 This method is the same as cw_findAllWithBlock except that it stores the objects in a NSHashTable
 
 This method enumerates over all the objects in a set and returns a NSHashTable with all objects
 where the block callback returned YES. If no blocks returned YES then this returns an empty
 NSHashTable.
 
 @param a block with a id argument and a BOOL return value
 @return a NSHashTable with all objects where the block call back returned YES, otherwise an empty NSHashTable if none return YES
 */
-(NSHashTable *)cw_findAllIntoWeakRefsWithBlock:(BOOL (^)(id))block
{
	NSHashTable *results = [NSHashTable hashTableWithWeakObjects];
	for (id obj in self) {
		if (block(obj)) {
			[results addObject:obj];
		}
	}
	return results;
}
#endif

/**
 Maps an NSSet to a new NSSet
 
 This method allows you to map one NSSet to another one and in the process you can alter the set
 or simply do 1-to-1 mapping. This method calls a block with each object in a set and expects to
 get an object back or nil. If the block returns an object it stores that object in the new set,
 otherwise if it gets nil back then it does not store anything in the new set for that specific 
 block callback. 
 
 @param block a block with an id object argument for the object being enumerated over in the set and expecting an id object or nil back
 @return a NSSet with the mapped set. If nil was returned for all block callbacks this simply returns an empty NSSet
 */
-(NSSet *)cw_mapSet:(id (^)(id obj))block
{
	NSMutableSet *mappedSet = [[NSMutableSet alloc] init];
	[self cw_each:^(id obj, BOOL *stop) {
		id rObj = block(obj);
		if (rObj) {
			[mappedSet addObject:rObj];
		}
	}];
    return mappedSet;
}

@end
