/* Copyright Avaya Inc. */

/**
 * @file AOAttributeList.h
 * @brief Defines the AOAttributeList class.
 */

@interface AOAttributeList : NSObject

/**
 * Can create an array of attributes using array literals or by creating an array of dictionaries.
 * Attributes describe characteristics of the customers' request.
 * These attributes act on the routing rules when selecting the optimum resource to handle the request.
 * Examples of attributes are : @[ 
 *                                   @{ @"name":@"Language", 
 *                                      @"values" : @[English],
 *                                 }];
 * Using these attribute values, a suitable agent is selected when the customer initiates an interaction.
 */
@property (nonatomic) NSArray* attributes;

@end
