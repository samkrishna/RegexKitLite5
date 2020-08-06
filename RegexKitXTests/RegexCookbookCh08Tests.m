//
//  RegexCookbookCh08Tests.m
//  RegexKitXTests
//
//  Created by Sam Krishna on 10/14/19.
//  Copyright © 2019 Sam Krishna. All rights reserved.
//

#import "RegexKitX.h"
#import <XCTest/XCTest.h>

@interface RegexCookbookCh08Tests : XCTestCase

@end

@implementation RegexCookbookCh08Tests

- (void)testAllowsAlmostAnyURLRegex
{
    NSString *allowAlmostAnyURLRegex = @"^(https?|ftp|file):\\/\\/.+$";
    NSString *httpSample = @"http://example.com";
    NSString *ftpSample = @"http://example.com";
    NSString *fileSample = @"http://example.com";
    XCTAssertTrue([httpSample isMatchedByRegex:allowAlmostAnyURLRegex options:RKXCaseless]);
    XCTAssertTrue([ftpSample isMatchedByRegex:allowAlmostAnyURLRegex options:RKXCaseless]);
    XCTAssertTrue([fileSample isMatchedByRegex:allowAlmostAnyURLRegex options:RKXCaseless]);
}

- (void)testRegexForRequiringDomainNameWithoutUsernameOrPassword
{
    NSString *regex = @"^(https?|ftp)://[a-z0-9-]+(\\.[a-z0-9-]+)+([/?].+)?$";
    NSString *sample123 = @"https://www.apple.com/easyAs123.html";
    XCTAssertTrue([sample123 isMatchedByRegex:regex options:RKXCaseless]);
}

- (void)testRegexForRequiringDomainNameWithAllowedOmittanceByInference
{
    NSString *regex = @"^((https?|ftp):\\/\\/|(www|ftp)\\.)([a-z0-9-]+\\.[a-z0-9-]+)+([\\/?].*)?$";
    NSString *sample = @"www.apple.com/easyAs123.html";
    XCTAssertTrue([sample isMatchedByRegex:regex options:RKXCaseless]);

    NSArray<NSString *> *captures = [sample captureSubstringsMatchedByRegex:regex options:RKXCaseless];
    XCTAssertTrue([captures[4] isEqualToString:@"apple.com"]);
}

- (void)testRegexForMatchingURLWithImageFilePath
{
    NSString *regex = @"^(https?|ftp)://[a-z0-9-]+(\\.[a-z0-9-]+)+(/[\\w-]+)*/[\\w-]+\\.(gif|png|jpg)$";
    NSString *sample = @"https://www.apple.com/apple.png";
    XCTAssertTrue([sample isMatchedByRegex:regex options:RKXCaseless]);
}

- (void)testRegexFromSection85
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection86
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection87
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection88
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection89
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection810
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection811
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection812
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection813
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection814
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection815
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection816
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection817
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection818
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection819
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection820
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection821
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection822
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection823
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection824
{
    XCTFail(@"Not filled out yet");
}

- (void)testRegexFromSection825
{
    XCTFail(@"Not filled out yet");
}

@end
