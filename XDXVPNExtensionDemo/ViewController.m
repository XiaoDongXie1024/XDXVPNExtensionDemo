//
//  ViewController.m
//  XDXVPNExtensionDemo
//
//  Created by 小东邪 on 12/04/2018.
//  Copyright © 2018 小东邪. All rights reserved.
//


/* 注意
    本文原理及做法在博客有详细介绍。
    如有疑问请先仔细阅读博客

 */

/*  快速阅读
 
    按照博客内容配置好两个APP BundleID后
 1. 点击左侧XDXVPNExtensionDemo工程，在General中，将申请好的两个Bundle ID分别填写到两个target工程中。
 2. 在viewDidLoad中 [model configureInfoWithTunnelBundleId:@"Extension Bundle ID" 第一行的TunnelBundleId换成配置好的extension TunnelBundleId即可。
 3. 运行程序在授权时必须进行授权操作。
 */

#import "ViewController.h"
#import <NetworkExtension/NetworkExtension.h>
#import "XDXVPNManager.h"
#import "XDXVPNManagerModel.h"

@interface ViewController ()<XDXVPNManagerDelegate>

@property (nonatomic, strong)           XDXVPNManager   *vpnManager;
@property (weak, nonatomic) IBOutlet    UIButton        *connectBtn;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    XDXVPNManagerModel *model = [[XDXVPNManagerModel alloc] init];
    
    /*  Note   - 在运行代码前必须按照博客所说配置好Target及开放权限，否则Demo无法正常运行
     *  @param TunnelBundleId : 必须填写你Extension Target的bundile ID,且必须合法，博客里有详细说明
     */
    [model configureInfoWithTunnelBundleId:@"com.xdxnetworks.xxx.xxxx"
                             serverAddress:@"XDX"
                                serverPort:@"54345"
                                       mtu:@"1400"
                                        ip:@"10.8.0.2"
                                    subnet:@"255.255.255.0"
                                       dns:@"8.8.8.8,8.4.4.4"];
    
    self.vpnManager = [[XDXVPNManager alloc] init];
    [self.vpnManager configManagerWithModel:model];
    self.vpnManager.delegate = self;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(vpnDidChange:) name:NEVPNStatusDidChangeNotification object:nil];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}
#pragma mark - UI

#pragma mark - Button Action
- (IBAction)didClickConnectBtn:(UIButton *)sender {
    if ([sender.currentTitle isEqualToString:@"Connect"]) {
        [self.vpnManager startVPN];
    }else {
        [self.vpnManager stopVPN];
    }
}

#pragma mark - Notification
- (void)vpnDidChange:(NSNotification *)notification {
    OSStatus status = self.vpnManager.vpnManager.connection.status;

    switch (status) {
        case NEVPNStatusConnecting:
        {
            NSLog(@"Connecting...");
            [self.connectBtn setTitle:@"Disconnect" forState:UIControlStateNormal];
        }
            break;
        case NEVPNStatusConnected:
        {
            NSLog(@"Connected...");
            [self.connectBtn setTitle:@"Disconnect" forState:UIControlStateNormal];
            
        }
            break;
        case NEVPNStatusDisconnecting:
        {
            NSLog(@"Disconnecting...");
            
        }
            break;
        case NEVPNStatusDisconnected:
        {
            NSLog(@"Disconnected...");
            [self.connectBtn setTitle:@"Connect" forState:UIControlStateNormal];
            
        }
            break;
        case NEVPNStatusInvalid:
            
            NSLog(@"Invliad");
//             [self.connectBtn setTitle:@"Connect" forState:UIControlStateNormal];
            break;
        case NEVPNStatusReasserting:
            NSLog(@"Reasserting...");
            break;
    }
}

#pragma mark - Delegate
- (void)loadFromPreferencesComplete {
    [self vpnDidChange:nil];
}

#pragma mark - Dealloc
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
