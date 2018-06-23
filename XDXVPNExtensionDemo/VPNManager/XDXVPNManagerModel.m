//
//  XDXVPNManagerModel.m
//  XDXRouterDemo
//
//  Created by 小东邪 on 02/04/2018.
//  Copyright © 2018 小东邪. All rights reserved.
//

#import "XDXVPNManagerModel.h"

@implementation XDXVPNManagerModel

- (void)configureInfoWithTunnelBundleId:(NSString *)tunnelBundleId serverAddress:(NSString *)serverAddress serverPort:(NSString *)serverPort mtu:(NSString *)mtu ip:(NSString *)ip subnet:(NSString *)subnet dns:(NSString *)dns {
    self.tunnelBundleId = tunnelBundleId;
    self.serverAddress  = serverAddress;
    self.serverPort     = serverPort;
    self.mtu            = mtu;
    self.ip             = ip;
    self.subnet         = subnet;
    self.dns            = dns;
}

@end
