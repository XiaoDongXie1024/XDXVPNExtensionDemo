//
//  NSMutableDictionary+XDXSafeSetRemove.h
//  XDXRouterFramework
//
//  Created by 小东邪 on 02/04/2018.
//  Copyright © 2018 小东邪. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 *  Prevent value of dictionary is nil will cause crash.
 */

@interface NSMutableDictionary (XDXSafeSetRemove)

/**
    Safe set key-value for dictionary.
 */
- (void)safeSetObject:(id)aObj
               forKey:(id<NSCopying>)aKey;

/**
    Safe read value for key.
 */
- (id)safeObjectForKey:(id<NSCopying>)aKey;

@end
