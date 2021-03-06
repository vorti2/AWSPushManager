//
//  AWSPushManager.h
//
//
// Copyright 2016 Amazon.com, Inc. or its affiliates (Amazon). All Rights Reserved.
//
// Code generated by AWS Mobile Hub. Amazon gives unlimited permission to
// copy, distribute and modify it.
//
// Source code generated from template: aws-my-sample-app-ios-objc v0.5
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class AWSPushManager;
@class AWSPushTopic;
@protocol AWSPushManagerDelegate;
@protocol AWSPushTopicDelegate;

/**
 The error domain for `PushManager`.
 */
FOUNDATION_EXPORT NSString *const AWSPushManagerErrorDomain;

/**
 The error code for `AWSPushManagerErrorDomain`.
 */
typedef NS_ENUM(NSInteger, AWSPushManagerErrorType){
    /**
     An unknown error. This should not happen.
     */
    AWSPushManagerErrorTypeUnknown,
    /**
     The device token returned by the OS is invalid and cannot be processed.
     */
    AWSPushManagerErrorTypeInvalidDeviceToken,
    /**
     Unsubscribe requests failed while disabling `PushManager`.
     */
    AWSPushManagerErrorTypeUnsubscribeFailed,
};

/**
 The Push Manager registers the app on the device with Apple Push Notification
 Service (APNS) and registers the resulting device token in Amazon SNS. The result
 of this registration process is an Amazon SNS Endpoint ARN, which can be used to
 send push notifications directly to a specific device. The Push Manager also
 manages Amazon SNS topic subscriptions, allowing the app to subscribe to
 Amazon SNS topics, which let you target groups of devices with push notifications.
 */
@interface AWSPushManager : NSObject

/**
 The default platform application ARN
 */
+ (NSString *)defaultPlatformARN;
+ (void)setDefaultPlatformARN:(NSString *)defaultPlatformARN;

/**
 Indicates if `PushManager` is enabled or disabled.
 */
@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

/**
 The device token returned by iOS.
 */
@property (nonatomic, readonly) NSString *deviceToken;

/**
 The application platform endpoint ARN for Amazon SNS.
 */
@property (nonatomic, readonly) NSString *endpointARN;

/**
 The application platform ARN for the app.
 */
@property (nonatomic, readonly) NSString *platformARN;

/**
 The list of `PushTopic`.
 */
@property (nonatomic, readonly) NSArray *topics;

/**
 The delegate for receiving `PushManager` and `PushTopic` events.
 */
@property (nonatomic, weak) id<AWSPushManagerDelegate, AWSPushTopicDelegate> delegate;

/**
 Returns the singleton `PushManager` client.
 
 @return A singleton instance of `PushManager`.
 */
+ (instancetype)defaultPushManager;

/**
 Initializes `PushManager` with the list of topic ARNs.
 
 @param topicARNs A list of topic ARNs from Amazon SNS. It needs to be an `NSArray` containing only `NSString`.
 */
- (void)registerTopicARNs:(NSArray *)topicARNs;

/**
 Returns a topic associated with the specified topic ARN.
 
 @param topicARN A topic ARN from Amazon SNS.
 
 @return The topic with the specified topic ARN.
 */
- (AWSPushTopic *)topicForTopicARN:(NSString *)topicARN;

/**
 Initiates the process to enable Push Notifications.
 When called for the first time, it asks the user for the permission to enable Push Notifications. If the user decline it, it fails to enable Push Notifications.
 
 On success, it calls `- pushManagerDidRegister:` from `AWSPushManagerDelegate`.
 On failure, it calls `- pushManager:didFailToRegisterWithError:` from `AWSPushManagerDelegate`.
 */
- (void)registerForPushNotifications;

/**
 Unsubscribes from all subscribed topics, then marks `PushManager` as disabled.
 
 On success, it calls `- pushManagerDidDisable:` from `AWSPushManagerDelegate`.
 On failure, it calls `- pushManager:didFailToDisableWithError:` from `AWSPushManagerDelegate`.
 */
- (void)disablePushNotifications;

/**
 Intercepts the `- application:didFinishLaunchingWithOptions:` application delegate.
 
 @param application Your singleton app object.
 @param launchOptions A dictionary indicating the reason the app was launched (if any). The contents of this dictionary may be empty in situations where the user launched the app directly. For information about the possible keys in this dictionary and how to handle them, see Launch Options Keys.
 */
- (BOOL)interceptApplication:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

/**
 Intercepts the `- application:didRegisterForRemoteNotificationsWithDeviceToken:` application delegate.
 
 @param application The app object that initiated the remote-notification registration process.
 @param deviceToken A token that identifies the device to APNs.
 */
- (void)interceptApplication:(UIApplication *)application
didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

/**
 Intercepts the `- application:didFailToRegisterForRemoteNotificationsWithError:` application delegate.
 
 @param application The app object that initiated the remote-notification registration process.
 @param error       An `NSError` object that encapsulates information why registration did not succeed.
 */
- (void)interceptApplication:(UIApplication *)application
didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

/**
 Intercepts the `- application:didReceiveRemoteNotification:` application delegate.
 
 @param application The app object that received the remote notification.
 @param userInfo    A dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data. The provider originates it as a JSON-defined dictionary that iOS converts to an `NSDictionary` object; the dictionary may contain only property-list objects plus `NSNull`.
 */
- (void)interceptApplication:(UIApplication *)application
didReceiveRemoteNotification:(NSDictionary *)userInfo;

@end

/**
 A topic object.
 */
@interface AWSPushTopic : NSObject

/**
 Initializes the topic object with a given topic ARN.
 
 @param topicARN A topic ARN from Amazon SNS.
 
 @return An initialized instance of `PushTopic`.
 */
- (instancetype)initWithTopicARN:(NSString *)topicARN;

/**
 The topic ARN.
 */
@property (nonatomic, readonly) NSString *topicARN;

/**
 The topic name.
 */
@property (nonatomic, readonly) NSString *topicName;

/**
 Indicates if the device is registered for the topic.
 */
@property (nonatomic, readonly, getter=isSubscribed) BOOL subscribed;

/**
 The subscription ARN from Amazon SNS.
 */
@property (nonatomic, readonly) NSString *subscriptionARN;

/**
 Subscribes the device to the topic.
 
 On success, it calls `- topicDidSubscribe:` from `AWSPushTopicDelegate`.
 On failure, it calls `topic:didFailToSubscribeWithError:` from `AWSPushTopicDelegate`.
 */
- (void)subscribe;

/**
 Unsubscribes the device from the topic.
 
 On success, it calls `- topicDidUnsubscribe:` from `AWSPushTopicDelegate`.
 On failure, it calls `topic:didFailToUnsubscribeWithError:` from `AWSPushTopicDelegate`.
 */
- (void)unsubscribe;

@end

/**
 A delegate for receiving `PushManager` events.
 */
@protocol AWSPushManagerDelegate <NSObject>

@required

/**
 Indicates the success of the `- registerForPushNotifications` call.
 
 @param pushManager An instance of `PushManager`.
 */
- (void)pushManagerDidRegister:(AWSPushManager *)pushManager;

/**
 Indicates the failure of the `- registerForPushNotifications` call.
 
 @param pushManager An instance of `PushManager`.
 @param error       An `NSError` object that encapsulates information why registration did not succeed.
 */
- (void)pushManager:(AWSPushManager *)pushManager
didFailToRegisterWithError:(NSError *)error;

@optional

/**
 Indicates the device received a Push Notifiation.
 
 @param userInfo    A dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data. The provider originates it as a JSON-defined dictionary that iOS converts to an `NSDictionary` object; the dictionary may contain only property-list objects plus `NSNull`.
 */
- (void)pushManager:(AWSPushManager *)pushManager
didReceivePushNotification:(NSDictionary *)userInfo;

/**
 Indicates the success of the `- disablePushNotifications` call.
 
 @param pushManager An instance of `PushManager`.
 */
- (void)pushManagerDidDisable:(AWSPushManager *)pushManager;

/**
 Indicates the failure of the `- disablePushNotifications` call.
 
 @param pushManager An instance of `PushManager`.
 @param error       An `NSError` object that encapsulates information why disable did not succeed.
 */
- (void)pushManager:(AWSPushManager *)pushManager
didFailToDisableWithError:(NSError *)error;

@end

/**
 A delegate for receiving `PushTopic` events.
 */
@protocol AWSPushTopicDelegate <NSObject>

@optional

/**
 Indicates the subscribe succeeded.
 
 @param topic The topic object.
 */
- (void)topicDidSubscribe:(AWSPushTopic *)topic;

/**
 Indicates the subscribe failed.
 
 @param topic The topic object.
 @param error An `NSError` object that encapsulates information why subscribe did not succeed.
 */
- (void)topic:(AWSPushTopic *)topic
didFailToSubscribeWithError:(NSError *)error;

/**
 Indicates the unsubscribe succeeded.
 
 @param topic The topic object.
 */
- (void)topicDidUnsubscribe:(AWSPushTopic *)topic;

/**
 Indicates the unsubscribe failed.
 
 @param topic The topic object.
 @param error An `NSError` object that encapsulates information why unsubscribe did not succeed.
 */
- (void)topic:(AWSPushTopic *)topic
didFailToUnsubscribeWithError:(NSError *)error;

@end
