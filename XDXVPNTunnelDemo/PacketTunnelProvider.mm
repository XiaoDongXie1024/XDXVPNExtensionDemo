//
//  PacketTunnelProvider.m
//  XDXVPNTunnelDemo
//
//  Created by 小东邪 on 12/04/2018.
//Copyright © 2018 小东邪. All rights reserved.
//

#import "PacketTunnelProvider.h"
#include "log4cplus.h"

// 解析域名导入库
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define XDX_NET_MTU                        1400
#define XDX_NET_REMOTEADDRESS              "222.222.222.222"
#define XDX_NET_SUBNETMASKS                "255.255.255.255"
#define XDX_NET_DNS                        "223.5.5.5"
#define XDX_LOCAL_ADDRESS                  "127.0.0.1"
#define XDX_NET_TUNNEL_IPADDRESS           "10.10.10.10"

@interface PacketTunnelProvider ()
@property NWTCPConnection *connection;
@property (strong) void (^pendingStartCompletion)(NSError *);
@end

@implementation PacketTunnelProvider

- (void)startTunnelWithOptions:(NSDictionary *)options completionHandler:(void (^)(NSError *))completionHandler
{
    log4cplus_info("XDXVPNManager", "XDXPacketTunnelManager - Start Tunel !");
    NSString *remoteAddress = [self queryIpWithDomain:@"www.baidu.com"];
    NEPacketTunnelNetworkSettings *tunnelNetworkSettings = [[NEPacketTunnelNetworkSettings alloc] initWithTunnelRemoteAddress:@XDX_NET_REMOTEADDRESS];
    tunnelNetworkSettings.MTU = [NSNumber numberWithInteger:XDX_NET_MTU];
    tunnelNetworkSettings.IPv4Settings = [[NEIPv4Settings alloc] initWithAddresses:[NSArray arrayWithObjects:@XDX_NET_TUNNEL_IPADDRESS, nil]  subnetMasks:[NSArray arrayWithObjects:@XDX_NET_SUBNETMASKS, nil]];
    tunnelNetworkSettings.IPv4Settings.includedRoutes = @[[NEIPv4Route defaultRoute]];
    // 此处不可随意设置，可根据真实情况设置
    //    NEIPv4Route *excludeRoute = [[NEIPv4Route alloc] initWithDestinationAddress:@"10.12.23.90" subnetMask:@"255.255.255.255"];
    //    tunnelNetworkSettings.IPv4Settings.excludedRoutes = @[excludeRoute];

    [self setTunnelNetworkSettings:tunnelNetworkSettings completionHandler:^(NSError * _Nullable error) {
        if (error == nil) {
            log4cplus_info("XDXVPNManager", "XDXPacketTunnelManager - Start Tunel Success !");
            completionHandler(nil);
        }else {
            log4cplus_error("XDXVPNManager", "XDXPacketTunnelManager - Start Tunel Failed - %s !",error.debugDescription.UTF8String);
            completionHandler(error);
            return;
        }
    }];

    [self readPakcets];
}

- (void)stopTunnelWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler
{
	// Add code here to start the process of stopping the tunnel
	[self.connection cancel];
	completionHandler();
}

- (void)readPakcets {
    __weak PacketTunnelProvider *weakSelf = self;
    [self.packetFlow readPacketsWithCompletionHandler:^(NSArray<NSData *> * _Nonnull packets, NSArray<NSNumber *> * _Nonnull protocols) {
        for (NSData *packet in packets) {
            // log4cplus_debug("XDXVPNManager", "Read Packet - %s",[NSString stringWithFormat:@"%@",packet].UTF8String);
            __typeof__(self) strongSelf = weakSelf;
            // TODO ...
            
            NSLog(@"XDX : read packet - %@",packet);
        }
        [weakSelf readPakcets];
    }];
}


- (NSString *)queryIpWithDomain:(NSString *)domain {
    struct hostent *hs;
    struct sockaddr_in server;
    if ((hs = gethostbyname([domain UTF8String])) != NULL) {
        server.sin_addr = *((struct in_addr*)hs->h_addr_list[0]);
        return [NSString stringWithUTF8String:inet_ntoa(server.sin_addr)];
    }
    
    return nil;
}

@end
