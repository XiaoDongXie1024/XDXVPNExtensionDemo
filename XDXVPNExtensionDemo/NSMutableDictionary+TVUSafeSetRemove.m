//
//  NSMutableDictionary+XDXSafeSetRemove.m
//  XDXRouterFramework
//
//  Created by 小东邪 on 02/04/2018.
//  Copyright © 2018 小东邪. All rights reserved.
//

#import "NSMutableDictionary+XDXSafeSetRemove.h"

@implementation NSMutableDictionary (XDXSafeSetRemove)

- (void)safeSetObject:(id)obj forKeyedSubscript:(id<NSCopying>)key {
    if (!key) {
        return ;
    }
    
    if (!obj) {
        [self removeObjectForKey:key];
    }else {
        [self setObject:obj forKey:key];
    }
}

- (void)safeSetObject:(id)aObj forKey:(id<NSCopying>)aKey {
    if (aObj && ![aObj isKindOfClass:[NSNull class]] && aKey) {
        [self setObject:aObj forKey:aKey];
    } else {
        return;
    }
}

- (id)safeObjectForKey:(id<NSCopying>)aKey {
    if (aKey != nil) {
        return [self objectForKey:aKey];
    } else {
        return nil;
    }
}

@end
