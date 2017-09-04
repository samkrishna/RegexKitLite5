//
//  RegexKitLite5Tests.swift
//  SwiftRegexKitLite5Tests
//
//  Created by Sam Krishna on 8/27/17.
//  Copyright © 2017 Sam Krishna. All rights reserved.
//

import XCTest
@testable import SwiftRegexKitLite5

class RegexKitLite5Tests: XCTestCase {
    public let candidate = "2014-05-06 17:03:17.967 EXECUTION_DATA: -1 EUR EUR.JPY 14321016 orderId:439: clientId:75018, execId:0001f4e8.536956da.01.01, time:20140506  17:03:18, acctNumber:DU161169, exchange:IDEALPRO, side:SLD, shares:141500, price:141.73, permId:825657452, liquidation:0, cumQty:141500, avgPrice:141.73";

    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testIsMatchedBy() {
        let regex = "(.*) EXECUTION_DATA: .* (\\w{3}.\\w{3}) .* orderId:(\\d+): clientId:(\\w+), execId:(.*.01), .*, acctNumber:(\\w+).*, side:(\\w+), shares:(\\d+), price:(.*), permId:(\\d+).*"
        let result = try! candidate.isMatchedBy(regex)
        XCTAssert(result)
    }

    func testIsMatchedByRegexSearchRange() {
        let regex = "(.*) EXECUTION_DATA: .* (\\w{3}.\\w{3}) .* orderId:(\\d+): clientId:(\\w+), execId:(.*.01), .*, acctNumber:(\\w+).*, side:(\\w+), shares:(\\d+), price:(.*), permId:(\\d+).*"
        let resultWithFullRange = try! candidate.isMatchedBy(regex, searchRange: candidate.stringRange)
        XCTAssertTrue(resultWithFullRange)
        let resultWithHalfRange = try! candidate.isMatchedBy(regex, searchRange: NSMakeRange(0, (candidate.utf16.count / 2)))
        XCTAssertFalse(resultWithHalfRange)
    }

    func testIsMatchedByRegexOptions() {
        let regex = "(.*) execution_data: .* (\\w{3}.\\w{3}) .* orderId:(\\d+): clientId:(\\w+), execId:(.*.01), .*, acctNumber:(\\w+).*, side:(\\w+), shares:(\\d+), price:(.*), permId:(\\d+).*"
        let result = try! candidate.isMatchedBy(regex, options: .RKLCaseless)
        XCTAssertTrue(result)

        let failResult = try! candidate.isMatchedBy(regex, options: [.RKLCaseless, .RKLIgnoreMetacharacters ])
        XCTAssertFalse(failResult)
    }

    func testCustomOperators() {
        let regex = "(.*) EXECUTION_DATA: .* (\\w{3}.\\w{3}) .* orderId:(\\d+): clientId:(\\w+), execId:(.*.01), .*, acctNumber:(\\w+).*, side:(\\w+), shares:(\\d+), price:(.*), permId:(\\d+).*"
        XCTAssertTrue(candidate =~ regex)
        XCTAssertTrue(regex ~= candidate)
    }

    func testRangeOfRegex() {
        let regex = "((\\d+)-(\\d+)-(\\d+)) ((\\d+):(\\d+):(\\d+))"
        let captureRange = try! candidate.rangeOf(regex)
        XCTAssert(captureRange.location == 0);
        XCTAssert(captureRange.length == 19);

        let dateRange = try! candidate.rangeOf(regex, capture: 1)
        XCTAssert(dateRange.location == 0);
        XCTAssert(dateRange.length == 10);

        let yearRange = try! candidate.rangeOf(regex, capture: 2)
        XCTAssert(yearRange.location == 0);
        XCTAssert(yearRange.length == 4);

        let monthRange = try! candidate.rangeOf(regex, capture: 3)
        XCTAssert(monthRange.location == 5);
        XCTAssert(monthRange.length == 2);

        let dayRange = try! candidate.rangeOf(regex, capture: 4)
        XCTAssert(dayRange.location == 8);
        XCTAssert(dayRange.length == 2);

        let timeRange = try! candidate.rangeOf(regex, capture: 5)
        XCTAssert(timeRange.location == 11);
        XCTAssert(timeRange.length == 8);

        let hourRange = try! candidate.rangeOf(regex, capture: 6)
        XCTAssert(hourRange.location == 11);
        XCTAssert(hourRange.length == 2);

        let minuteRange = try! candidate.rangeOf(regex, capture: 7)
        XCTAssert(minuteRange.location == 14);
        XCTAssert(minuteRange.length == 2);

        let secondRange = try! candidate.rangeOf(regex, capture: 8)
        XCTAssert(secondRange.location == 17);
        XCTAssert(secondRange.length == 2);
    }

    func testFailedRangeOfRegex() {
        let failRange: NSRange = try! candidate.rangeOf("blah")
        XCTAssert(failRange.location == NSNotFound)
        XCTAssert(failRange.length == 0)
    }

    func testStringByMatching() {
        // @"2014-05-06 17:03:17.967 EXECUTION_DATA: -1 EUR EUR.JPY 14321016 orderId:439: clientId:75018, execId:0001f4e8.536956da.01.01, time:20140506  17:03:18, acctNumber:DU161169, exchange:IDEALPRO, side:SLD, shares:141500, price:141.73, permId:825657452, liquidation:0, cumQty:141500, avgPrice:141.73";

        let regex = "((\\d+)-(\\d+)-(\\d+)) ((\\d+):(\\d+):(\\d+))";
        let timestamp = try! candidate.stringByMatching(regex)
        XCTAssert(timestamp == "2014-05-06 17:03:17");
    }

    func testStringByReplacingOccurrencesOf() {
        let failedPattern = "2014-05-06 17:03:17.967 EXECUTION_DINO"
        let failureControl = "2014-05-06 17:03:17.967 EXECUTION_DATA"
        let failureRange = NSMakeRange(0, 38);
        let failureResult = try! candidate.stringByReplacingOccurrencesOf(failedPattern, replacement: "BARNEY RUBBLE", searchRange: failureRange)
        XCTAssert(failureResult == failureControl)

        let successPattern = "2014-05-06 17:03:17.967 EXECUTION_DATA"
        let successResult = try! candidate.stringByReplacingOccurrencesOf(successPattern, replacement: "BARNEY RUBBLE", searchRange: failureRange)
        XCTAssert(try! successResult.isMatchedBy("BARNEY RUBBLE"))
    }

    func testComponentsMatchedBy() {
        let list = "$10.23, $1024.42, $3099"
        let listItems: [String] = try! list.componentsMatchedBy("\\$((\\d+)(?:\\.(\\d+)|\\.?))", capture: 3)

        XCTAssert(listItems[0] == "23")
        XCTAssert(listItems[1] == "42")
        XCTAssert(listItems[2] == "")
    }

    func testCaptureComponentsMatcheBy() {
        let list = "$10.23, $1024.42, $3099"
        let listItems: [String] = try! list.captureComponentsMatchedBy("\\$((\\d+)(?:\\.(\\d+)|\\.?))")
        XCTAssert(listItems.count == 4)
        XCTAssert(listItems[0] == "$10.23")
        XCTAssert(listItems[1] == "10.23")
        XCTAssert(listItems[2] == "10")
        XCTAssert(listItems[3] == "23")
    }

    func testArrayOfCaptureComponentsMatchedBy() {
        let list = "$10.23, $1024.42, $3099"
        let listItems: [[String]] = try! list.arrayOfCaptureComponentsMatchedBy("\\$((\\d+)(?:\\.(\\d+)|\\.?))")
        XCTAssert(listItems.count == 3)

        let list0 = listItems[0]
        XCTAssert(list0 == [ "$10.23", "10.23", "10", "23" ]);
        let list1 = listItems[1];
        XCTAssert(list1 == [ "$1024.42", "1024.42", "1024", "42" ])
        let list2 = listItems[2];
        XCTAssert(list2 == [ "$3099", "3099", "3099", "" ])
    }

    func testDictionaryByMatching() {
        let name = "Name: Joe";
        let regex = "Name:\\s*(\\w*)\\s*(\\w*)";
        let firstKey = "first";
        let lastKey = "last";

        let dict = try! name.dictionaryByMatching(regex, keysAndCaptures: firstKey, 1, lastKey, 2)
        XCTAssert(dict[firstKey] == "Joe")
        XCTAssert(dict[lastKey] == "")

        let badRegex = "Name:\\s*(\\w*)\\s*(\\w*";
        XCTAssertThrowsError(try name.dictionaryByMatching(badRegex, keysAndCaptures: firstKey, 1, lastKey, 2))
    }

    func testArrayOfDictionariesByMatching() {
        let name = "Name: Bob\n" + "Name: John Smith"
        let regex = "(?m)^Name:\\s*(\\w*)\\s*(\\w*)$"
        let firstKey = "first"
        let lastKey = "last"

        let nameArray = try! name.arrayOfDictionariesByMatching(regex, keysAndCaptures: firstKey, 1, lastKey, 2)

        let name0 = nameArray[0];
        XCTAssert(name0[firstKey] == "Bob");
        XCTAssert(name0[lastKey] == "");

        let name1 = nameArray[1];
        XCTAssert(name1[firstKey] == "John");
        XCTAssert(name1[lastKey] == "Smith");
    }

    func testEnumerateStringMatchedByRegexBlock() {
        let searchString = "Name: Bob\n" + "Name: John Smith"
        let regex = "(?m)^Name:\\s*(\\w*)\\s*(\\w*)$"
        var matchCount = 0

        let result = try! searchString.enumerateStringsMatchedBy(regex, { (stringArray, ranges) in
            print("stringArray = \(stringArray)")
            print("ranges = \(ranges)")
            matchCount += 1
        })

        XCTAssert(result)
        XCTAssert(matchCount == 2)
    }

    func testComponentsSeparatedBy() {
        let regex = ", ";
        let captures = try! candidate.componentsSeparatedBy(regex)
        XCTAssert(captures.count == 12);

        for substring in captures {
            let result = try! substring.isMatchedBy(regex)
            XCTAssertFalse(result)
        }
    }

    func testEnumerateStringsSeparatedyBy() {
        // @"2014-05-06 17:03:17.967 EXECUTION_DATA: -1 EUR EUR.JPY 14321016 orderId:439: clientId:75018, execId:0001f4e8.536956da.01.01, time:20140506  17:03:18, acctNumber:DU161169, exchange:IDEALPRO, side:SLD, shares:141500, price:141.73, permId:825657452, liquidation:0, cumQty:141500, avgPrice:141.73";
        let regexPattern = ",(\\s+)";
        let rangeValueChecks = [ NSMakeRange(0, 91),
                                 NSMakeRange(93, 30),
                                 NSMakeRange(125, 23),
                                 NSMakeRange(150, 19),
                                 NSMakeRange(171, 17),
                                 NSMakeRange(190, 8),
                                 NSMakeRange(200, 13),
                                 NSMakeRange(215, 12),
                                 NSMakeRange(229, 16),
                                 NSMakeRange(247, 13),
                                 NSMakeRange(262, 13),
                                 NSMakeRange(277, 15) ];

        var index = 0;
        let result = try! candidate.enumerateStringsSeparatedBy(regexPattern) { (capturedStrings, capturedRanges) in
            let string = capturedStrings[0]
            let range = capturedRanges[0]
            let rangeCheck = rangeValueChecks[index]
            print("Forward: string = \(string) and range = \(range)")
            XCTAssert(NSEqualRanges(range, rangeCheck))
            index += 1
        }

        XCTAssert(result);
    }
}
