//
//  RegexKitLite5.swift
//  RegexKitLite5
//
//  Created by Sam Krishna on 8/27/17.
//  Copyright © 2017 Sam Krishna. All rights reserved.
//

import Foundation

infix operator =~

public func =~ (string: String, regex: String) -> Bool {
    do {
        let result = try string.isMatchedBy(regexPattern: regex)
        return result
    } catch {
        return false
    }
}

public func ~= (regex: String, string: String) -> Bool {
    do {
        let result = try string.isMatchedBy(regexPattern: regex)
        return result
    } catch {
        return false
    }
}

public struct RKLRegexOptions: OptionSet {
    public let rawValue: Int

    public init(rawValue: Int) {
        self.rawValue = rawValue
    }

    static let RKLNoOptions             = RKLRegexOptions(rawValue: 0)
    static let RKLCaseless              = RKLRegexOptions(rawValue: 1 << 0)
    static let RKLComments              = RKLRegexOptions(rawValue: 1 << 1)
    static let RKLIgnoreMetacharacters  = RKLRegexOptions(rawValue: 1 << 2)
    static let RKLDotAll                = RKLRegexOptions(rawValue: 1 << 3)
    static let RKLMultiline             = RKLRegexOptions(rawValue: 1 << 4)
    static let RKLUseUnixLineSeparators = RKLRegexOptions(rawValue: 1 << 5)
    static let RKLUnicodeWordBoundaries = RKLRegexOptions(rawValue: 1 << 6)

    fileprivate func coerceToNSRegularExpressionOptions() -> NSRegularExpression.Options {
        var options = NSRegularExpression.Options()
        if contains(.RKLNoOptions) { options.insert(NSRegularExpression.Options(rawValue: 0)) }
        if contains(.RKLCaseless) { options.insert(.caseInsensitive) }
        if contains(.RKLComments) { options.insert(.allowCommentsAndWhitespace) }
        if contains(.RKLIgnoreMetacharacters) { options.insert(.ignoreMetacharacters) }
        if contains(.RKLDotAll) { options.insert(.dotMatchesLineSeparators) }
        if contains(.RKLMultiline) { options.insert(.anchorsMatchLines) }
        if contains(.RKLUseUnixLineSeparators) { options.insert(.useUnixLineSeparators) }
        if contains(.RKLUnicodeWordBoundaries) { options.insert(.useUnicodeWordBoundaries) }
        return options
    }
}

public extension String {
    var stringRange: NSRange {
        return NSRange(location: 0, length: utf16.count)
    }

    func isMatchedBy(regexPattern: String,
                     range: NSRange? = nil,
                     options: RKLRegexOptions = RKLRegexOptions(rawValue: 0),
                     matchingOptions: NSRegularExpression.MatchingOptions = [NSRegularExpression.MatchingOptions(rawValue: 0)])
        throws -> Bool {
            let nsregexopts = options.coerceToNSRegularExpressionOptions()
            let regex = try NSRegularExpression(pattern: regexPattern, options: nsregexopts)
            let match = regex.firstMatch(in: self, options: matchingOptions, range: range ?? stringRange)
            return (match != nil)
    }
}
