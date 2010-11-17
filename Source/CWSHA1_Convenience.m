//
//  CWSHA1_Convenience.m
//  Zangetsu
//


#import "CWSHA1_Convenience.h"
#import <CommonCrypto/CommonDigest.h>

@implementation NSString ( CCSHA1_Convenience )

//
// Return the sha value of the string passed in
//
+(NSString *)sha1HashFromString:(NSString *)str 
{
	if(str == nil){
		return nil;
	}
	
	const char *cStringRep = [str UTF8String];
	unsigned char shaHash[CC_SHA1_DIGEST_LENGTH];
	
	CC_SHA1(cStringRep, (CC_LONG)strlen(cStringRep), shaHash);
	
	NSString *shaHashString = [NSString  stringWithFormat:
				   @"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
				   shaHash[0], shaHash[1], shaHash[2], shaHash[3], shaHash[4],
				   shaHash[5], shaHash[6], shaHash[7], shaHash[8], shaHash[9],
				   shaHash[10], shaHash[11], shaHash[12], shaHash[13], shaHash[14], 
				   shaHash[15], shaHash[16], shaHash[17], shaHash[18], shaHash[19]];
	
	return [shaHashString lowercaseString];
}

@end

@implementation NSData (CCSHA1_Convenience)

//
// Convience method to return the SHA1 value of the contents of a NSData object given
//
-(NSString *)sha1StringFromData
{
	NSString *str = [[NSString alloc] initWithData:self encoding:NSUTF8StringEncoding];
	const char *cStringRep = [str UTF8String];
	unsigned char shaHash[CC_SHA1_DIGEST_LENGTH];
	
	CC_SHA1(cStringRep, (CC_LONG)strlen(cStringRep), shaHash);
	
	NSString *shaHashString = [NSString  stringWithFormat:
				   @"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
				   shaHash[0], shaHash[1], shaHash[2], shaHash[3], shaHash[4],
				   shaHash[5], shaHash[6], shaHash[7], shaHash[8], shaHash[9], 
				   shaHash[10], shaHash[11], shaHash[12], shaHash[13], shaHash[14],
				   shaHash[15], shaHash[16], shaHash[17], shaHash[18], shaHash[19]];
	
	return [shaHashString lowercaseString];
}

@end