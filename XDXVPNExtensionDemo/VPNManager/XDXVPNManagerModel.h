//
//  XDXVPNManagerModel.h
//  XDXRouterDemo
//
//  Created by 小东邪 on 02/04/2018.
//  Copyright © 2018 小东邪. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface XDXVPNManagerModel : NSObject

/**
 *  tunnelBundleId : Your extension(Target:PacketTunnel) bundle identifier.
 *  Note : The extension bundle identifier must be YourProject bundle identifier.targetDisplayName (The Project bundle identifier's format must be "com.xxxx.xxx")
 */
@property (nonatomic, copy  ) NSString *tunnelBundleId;

/**
 *  The VPN's name will display in the iPhone-Setting-General-VPN.
 */
@property (nonatomic, copy  ) NSString *serverAddress;

/**************** Base network setting  *********************************/

@property (nonatomic, copy  ) NSString *serverPort;
@property (nonatomic, copy  ) NSString *mtu;
@property (nonatomic, copy  ) NSString *ip;
@property (nonatomic, copy  ) NSString *subnet;
@property (nonatomic, copy  ) NSString *dns;

- (void)configureInfoWithTunnelBundleId:(NSString *)tunnelBundleId
                          serverAddress:(NSString *)serverAddress
                             serverPort:(NSString *)serverPort
                                    mtu:(NSString *)mtu
                                     ip:(NSString *)ip
                                 subnet:(NSString *)subnet
                                    dns:(NSString *)dns;

@end
