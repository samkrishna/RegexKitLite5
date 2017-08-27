//
//  SwiftRegexKitLite5Tests.swift
//  SwiftRegexKitLite5Tests
//
//  Created by Sam Krishna on 8/27/17.
//  Copyright © 2017 Sam Krishna. All rights reserved.
//

import XCTest
@testable import SwiftRegexKitLite5

class SwiftRegexKitLite5Tests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testIsMatchedByRegexRangeOptionsMatchingOptions() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
        let testString = String("a test")
        let result = try! testString.isMatchedBy(regexPattern: "\\s+")
        XCTAssert(result)
    }
}
