//
//  RegexKitX.h
//  RegexKitX

/*
 Created by Sam Krishna on 6/12/17.
 Copyright © 2017 Sam Krishna. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of the Sam Krishna nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import <Foundation/Foundation.h>

/** The constants that define the regular expression options. */
typedef NS_OPTIONS(NSUInteger, RKXRegexOptions) {
    /** No regular expression options specified. */
    RKXNoOptions                = 0,
    /** Match letters in the pattern independent of case. */
    RKXCaseless                 = NSRegularExpressionCaseInsensitive,
    /** Ignore whitespace and #-prefixed comments in the pattern. */
    RKXComments                 = NSRegularExpressionAllowCommentsAndWhitespace,
    /** Treat the entire pattern as a literal string. */
    RKXIgnoreMetacharacters     = NSRegularExpressionIgnoreMetacharacters,
    /** Allow . to match any character, including line separators. */
    RKXDotAll                   = NSRegularExpressionDotMatchesLineSeparators,
    /** Allow ^ and $ to match the start and end of lines. */
    RKXMultiline                = NSRegularExpressionAnchorsMatchLines,
    /** Treat only \n as a line separator (otherwise, all standard line separators are used). */
    RKXUseUnixLineSeparators    = NSRegularExpressionUseUnixLineSeparators,
    /** Use Unicode TR#29 to specify word boundaries (otherwise, traditional regular expression word boundaries are used). */
    RKXUnicodeWordBoundaries    = NSRegularExpressionUseUnicodeWordBoundaries
};

@interface NSString (RangeMechanics)

/**
 Returns the full NSRange of the receiver. Equivalent to @c NSMakeRange(0, self.length).
 */
- (NSRange)stringRange;

/**
 Returns the @c NSRange from @c location to the end of the receiver, in UTF-16 code units.
 */
- (NSRange)rangeFromLocation:(NSUInteger)location;

/**
 Returns the @c NSRange from @c 0 to the @c location, in UTF-16 code units.
 */
- (NSRange)rangeToLocation:(NSUInteger)location;
@end

@interface NSString (RegexKitX)

#pragma mark - componentsSeparatedByRegex:

/**
 Returns an array containing substrings within the receiver that have been divided by the regular expression @c pattern.
 
 @param pattern A @c NSString containing a regular expression.
 @return A @c NSArray object containing the substrings from the receiver that have been divided by @c pattern.
 */
- (NSArray *)componentsSeparatedByRegex:(NSString *)pattern;

/**
 Returns an array containing substrings within @c searchRange of the receiver that have been divided by the regular expression @c pattern.
 
 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSArray object containing the substrings from the receiver that have been divided by @c pattern.
 @return Returns @c nil if @c pattern is invalid.
 */
- (NSArray *)componentsSeparatedByRegex:(NSString *)pattern range:(NSRange)searchRange;

/**
 Returns an array containing substrings within @c searchRange of the receiver that have been divided by the regular expression @c pattern using @c options.
 
 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray object containing the substrings from the receiver that have been divided by @c pattern. If there is no match, returns an array with the receiver as the single element.
 @return Returns @c nil if @c pattern is invalid and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)componentsSeparatedByRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error;

/**
 Returns an array containing substrings within @c searchRange of the receiver that have been divided by the regular expression @c pattern using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray object containing the substrings from the receiver that have been divided by @c pattern. If there is no match, returns an array with the receiver as the single element.
 @return Returns @c nil if @c pattern is invalid and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)componentsSeparatedByRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error;

#pragma mark - matchesRegex:

/**
 Returns a Boolean value that indicates whether the receiver is matched by @c pattern.

 @param pattern A @c NSString containing a regular expression.
 @return A @c BOOL value indicating whether or not the pattern has been matched in the receiver.
 @return Will return @c NO if @c pattern is invalid.
 */
- (BOOL)matchesRegex:(NSString *)pattern;

/**
 Returns a Boolean value that indicates whether the receiver is matched by @c pattern within @c searchRange.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c BOOL value indicating whether or not the pattern has been matched in the receiver.
 @return Will return @c NO if @c pattern is invalid.
 */
- (BOOL)matchesRegex:(NSString *)pattern inRange:(NSRange)searchRange;

/**
 Returns a Boolean value that indicates whether the receiver is matched by @c pattern within @c searchRange using @c options.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c BOOL value indicating whether or not the @c pattern has been matched in the receiver.
 @return Will return @c NO if @c pattern is invalid and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)matchesRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error;

/**
 Returns a Boolean value that indicates whether the receiver is matched by @c pattern within @c searchRange using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c BOOL value indicating whether or not the pattern has been matched in the receiver.
 @return Will return @c NO if @c pattern is invalid and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)matchesRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error;

#pragma mark - rangeOfRegex:

/**
 Returns the range for the first match of @c pattern.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSRange structure giving the location and length of the first match of @c pattern within @c searchRange of the receiver. Returns @c {NSNotFound, 0} if the receiver is not matched by @c pattern.
 @return Returns @c {NSNotFound, 0} if an error occurs.
 */
- (NSRange)rangeOfRegex:(NSString *)pattern;

/**
 Returns the range of capture number @c capture for the first match of @c pattern in the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param capture The matching range of the capture number from @c pattern to return. Use @c 0 for the entire range that @c pattern matched.
 @return A @c NSRange structure giving the location and length of the first match of @c pattern within @c searchRange of the receiver. Returns @c {NSNotFound, 0} if the receiver is not matched by @c pattern within @c searchRange or an error occurs.
 @return Returns @c {NSNotFound, 0} if an error occurs.
 */
- (NSRange)rangeOfRegex:(NSString *)pattern capture:(NSUInteger)capture;

/**
 Returns the range for the first match of @c pattern within @c searchRange of the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSRange structure giving the location and length of capture number @c capture for the first match of @c pattern. Returns @c {NSNotFound, 0} if the receiver is not matched by @c pattern.
 @return Returns @c {NSNotFound, 0} if an error occurs.
 */
- (NSRange)rangeOfRegex:(NSString *)pattern inRange:(NSRange)searchRange;

/**
 Returns the range of capture number @c capture for the first match of @c pattern within @c searchRange of the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param capture The matching range of the capture number from @c pattern to return. Use @c 0 for the entire range that @c pattern matched.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSRange structure giving the location and length of capture number @c capture for the first match of @c pattern within @c searchRange of the receiver. Returns @c {NSNotFound, 0} if the receiver is not matched by @c pattern within @c searchRange.
 @return Returns @c {NSNotFound, 0} if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSRange)rangeOfRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error;

/**
 Returns the range of capture number @c capture for the first match of @c pattern within @c searchRange of the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param capture The matching range of the capture number from @c pattern to return. Use @c 0 for the entire range that @c pattern matched.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSRange structure giving the location and length of capture number @c capture for the first match of @c pattern within @c searchRange of the receiver.
 @return Returns @c {NSNotFound, 0} if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSRange)rangeOfRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error;

#pragma mark - rangesOfRegex:

/**
 Returns an @c NSArray of @c NSValue-wrapped @c NSRanges of all captures of @c pattern matched in the receiver.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSArray of @c NSValue-wrapped NSRanges of all captures matched by @c pattern.
 @return Will return @c nil if @c pattern is invalid.
 */
- (NSArray *)rangesOfRegex:(NSString *)pattern;

/**
 Returns an @c NSArray of @c NSValue-wrapped @c NSRanges of all captures of @c pattern for all matches within @c searchRange of the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSArray of @c NSValue-wrapped @c NSRanges of all captures matched by @c pattern in @c searchRange.
 @return Will return @c nil if @c pattern is invalid.
 */
- (NSArray *)rangesOfRegex:(NSString *)pattern inRange:(NSRange)searchRange;

/**
 Returns a @c NSArray of @c NSValue-wrapped @c NSRanges of all captures of @c pattern for all matches within @c searchRange of the receiver using @c options.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray of @c NSValue-wrapped @c NSRanges of all captures matched by @c pattern in @c searchRange. Returns an empty array if there are no matches in the receiver for @c searchRange.
 @return Will return @c nil if @c pattern is invalid and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)rangesOfRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error;

/**
 Returns a @c NSArray of @c NSValue-wrapped @c NSRanges of all captures of @c pattern for all matches within @c searchRange of the receiver using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray of NSValue-wrapped NSRanges of all captures matched by @c pattern in @c searchRange. Returns an empty array if there are no matches in the receiver for @c searchRange.
 @return Will return @c nil if @c pattern is invalid and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)rangesOfRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error;

#pragma mark - stringByMatching:

/**
 Returns a string created from the characters of the receiver that are in the range of the first match of @c pattern.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSString containing the substring of the receiver matched by @c pattern.
 @return Returns @c nil if the receiver is not matched by @c pattern or an error occurs.
 */
- (NSString *)stringByMatching:(NSString *)pattern;

/**
 Returns a string created from the characters of the receiver that are in the range of the first match of @c pattern using @c options and @c matchingOptions within @c searchRange of the receiver for capture.

 @param pattern A @c NSString containing a regular expression.
 @param capture The string matched by capture from @c pattern to return. Use @c 0 for the entire string that @c pattern matched.
 @return A @c NSString containing the substring of the receiver matched by capture number capture of @c pattern.
 @return Returns @c nil if the receiver is not matched by @c pattern or an error occurs.
 */
- (NSString *)stringByMatching:(NSString *)pattern capture:(NSUInteger)capture;

/**
 Returns a string created from the characters of the receiver that are in the range of the first match of @c pattern using @c options and @c matchingOptions within @c searchRange of the receiver for capture.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSString containing the substring of the receiver matched by capture number capture of @c pattern within the searchRange of the receiver.
 @return Returns @c nil if the receiver is not matched by @c pattern or an error occurs.
 */
- (NSString *)stringByMatching:(NSString *)pattern inRange:(NSRange)searchRange;

/**
 Returns a string created from the characters of the receiver that are in the range of the first match of @c pattern using @c options and @c matchingOptions within @c searchRange of the receiver for capture.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param capture The string matched by capture from @c pattern to return. Use @c 0 for the entire string that @c pattern matched.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSString containing the substring of the receiver matched by capture number capture of @c pattern within @c searchRange of the receiver. Returns @c nil if the receiver is not matched by @c pattern within @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSString *)stringByMatching:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error;

/**
 Returns a string created from the characters of the receiver that are in the range of the first match of @c pattern using @c options and @c matchingOptions within @c searchRange of the receiver for capture.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param capture The string matched by capture from @c pattern to return. Use @c 0 for the entire string that @c pattern matched.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSString containing the substring of the receiver matched by capture number capture of @c pattern within @c searchRange of the receiver.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSString *)stringByMatching:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error;

#pragma mark - stringByReplacincOccurrencesOfRegex:withTemplate:

/**
 Returns a string created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options and @c matchingOptions are replaced with the contents of the @c template string after performing capture group substitutions.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSString created from the characters of the receiver in which all matches of the regular expression @c pattern are replaced with the contents of the @c template string after performing capture group substitutions.
 @return If the receiver is not matched by @c pattern then the string that is returned is a copy of the receiver as if @c stringWithString: had been sent to it.
 @return Will return @c nil if an error occurs.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template;

/**
 Returns a string created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options and @c matchingOptions are replaced with the contents of the @c template string after performing capture group substitutions.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSString created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern are replaced with the contents of the @c template string after performing capture group substitutions.
 @return Returns the characters within @c searchRange as if @c substringWithRange: had been sent to the receiver if the substring is not matched by @c pattern.
 @return Will return @c nil if an error occurs.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template range:(NSRange)searchRange;

/**
 Returns a string created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options are replaced with the contents of the @c template string after performing capture group substitutions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSString created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options and @c matchingOptions are replaced with the contents of the @c template string after performing capture group substitutions. Returns the characters within @c searchRange as if @c substringWithRange: had been sent to the receiver if the substring is not matched by @c pattern.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error;


/**
 Returns a string created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options and @c matchingOptions are replaced with the contents of the @c template string after performing capture group substitutions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSString created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options and @c matchingOptions are replaced with the contents of the @c template string after performing capture group substitutions. Returns the characters within @c searchRange as if @c substringWithRange: had been sent to the receiver if the substring is not matched by @c pattern.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error;

#pragma mark - captureCount:

/**
 Returns the number of captures that the regex contains.

 @return The number of captures in the regex is returned, or @c 0 if the regex does not contain any captures.
 @return Returns @c NSNotFound if an error occurs.
 */
- (NSUInteger)captureCount;

/**
 Returns the number of captures that the regex contains.

 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param error The optional error parameter, if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return The number of captures in the regex is returned, or @c 0 if the regex does not contain any captures.
 @return Returns @c NSNotFound if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSUInteger)captureCountWithOptions:(RKXRegexOptions)options error:(NSError **)error;

#pragma mark - isRegexValid

/**
 Returns a BOOL value that indicates whether the regular expression contained in the receiver.
 @return Returns a @c YES if the regex is valid; @c NO otherwise.
 */
- (BOOL)isRegexValid;

/**
 Returns a BOOL value that indicates whether the regular expression contained in the receiver is valid using @c options.

 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param error The optional error parameter, if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return Returns a @c YES if the regex is valid; @c NO otherwise and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)isRegexValidWithOptions:(RKXRegexOptions)options error:(NSError **)error;

#pragma mark - componentsMatchedByRegex:

- (NSArray *)componentsMatchedByRegex:(NSString *)pattern;

/**
 Returns an array containing all the substrings from the receiver that were matched by capture number capture from the regular expression @c pattern.

 @param pattern A @c NSString containing a regular expression.
 @param capture The string matched by capture from @c pattern to return. Use @c 0 for the entire string that @c pattern matched.
 @return A @c NSArray object containing all the substrings for capture group capture from the receiver that were matched by @c pattern.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)componentsMatchedByRegex:(NSString *)pattern capture:(NSUInteger)capture;

/**
 Returns an array containing all the substrings from the receiver that were matched by capture number capture from the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSArray object containing all the substrings from the receiver that were matched by @c pattern within @c searchRange.
 @return Returns an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)componentsMatchedByRegex:(NSString *)pattern range:(NSRange)searchRange;

/**
 Returns an array containing all the substrings from the receiver that were matched by capture number @c capture from the regular expression @c pattern within @c searchRange using @c options.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param capture The string matched by capture from @c pattern to return. Use @c 0 for the entire string that @c pattern matched.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray object containing all the substrings from the receiver that were matched by capture number capture from @c pattern within @c searchRange using @c options and @c matchingOptions. Will return an empty array if @c pattern fails to match in @c searchRange.
 @return Returns an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)componentsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error;

/**
 Returns an array containing all the substrings from the receiver that were matched by capture number @c capture from the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param capture The string matched by capture from @c pattern to return. Use @c 0 for the entire string that @c pattern matched.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray object containing all the substrings from the receiver that were matched by capture number capture from @c pattern within @c searchRange using @c options and @c matchingOptions.
 @return Returns an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)componentsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error;

#pragma mark - captureComponentsMatchedByRegex:

/**
 Returns an array containing the substrings matched by each capture group present in @c pattern for the first match of @c pattern.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSArray containing the substrings matched by each capture group present in pattern for the first match of @c pattern. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group.
 @return Will return an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)captureComponentsMatchedByRegex:(NSString *)pattern;

/**
 Returns an array containing the substrings matched by each capture group present in @c pattern for the first match of @c pattern within @c searchRange of the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSArray containing the substrings matched by each capture group present in pattern for the first match of @c pattern within @c searchRange of the receiver. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group.
 @return Returns an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)captureComponentsMatchedByRegex:(NSString *)pattern range:(NSRange)searchRange;

/**
 Returns an array containing the substrings matched by each capture group present in @c pattern for the first match of @c pattern within @c searchRange of the receiver using @c options.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray containing the substrings matched by each capture group present in pattern for the first match of @c pattern within @c searchRange of the receiver using @c options. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group.
 @return Returns an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)captureComponentsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error;

/**
 Returns an array containing the substrings matched by each capture group present in @c pattern for the first match of @c pattern within @c searchRange of the receiver using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray containing the substrings matched by each capture group present in pattern for the first match of @c pattern within @c searchRange of the receiver using @c options. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group.
 @return Returns an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)captureComponentsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error;

#pragma mark - arrayOfCaptureComponentsMatchedByRegex:

/**
 Returns an array containing all the matches from the receiver that were matched by the regular expression @c pattern. Each match result consists of an array of the substrings matched by all the capture groups present in the regular expression.

 @param pattern A @c NSString containing a regular expression.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSArray which contains all the capture groups present in @c pattern. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group. Will return an empty array if @c pattern fails to match.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)pattern;

/**
 Returns an array containing all the matches from the receiver that were matched by the regular expression @c pattern within @c searchRange. Each match result consists of an array of the substrings matched by all the capture groups present in the regular expression.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSArray which contains all the capture groups present in @c pattern. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group. Will return an empty array if @c pattern fails to match in @c searchRange.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)pattern range:(NSRange)searchRange;

/**
 Returns an array containing all the matches from the receiver that were matched by the regular expression @c pattern within @c searchRange using @c options. Each match result consists of an array of the substrings matched by all the capture groups present in the regular expression.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSArray which contains all the capture groups present in @c pattern. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error;

/**
 Returns an array containing all the matches from the receiver that were matched by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions. Each match result consists of an array of the substrings matched by all the capture groups present in the regular expression.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSArray which contains all the capture groups present in @c pattern. Array index @c 0 represents all of the text matched by @c pattern and subsequent array indexes contain the text matched by their respective capture group.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error;

#pragma mark - arrayOfDictionariesByMatchingRegex:

/**
 Returns an array containing all the matches in the receiver that were matched by the regular expression @c pattern. Each match result consists of a dictionary containing that matches substrings constructed from the specified set of keys and captures.

 @param pattern A @c NSString containing a regular expression.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSDictionary containing that matches substrings constructed from the specified set of keys and captures.
 @return Will return an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)pattern withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Returns an array containing all the matches in the receiver that were matched by the regular expression @c pattern within @c searchRange. Each match result consists of a dictionary containing that matches substrings constructed from the specified set of keys and captures.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSDictionary containing that matches substrings constructed from the specified set of keys and captures.
 @return Will return an empty array if @c pattern fails to match in @c searchRange.
 @return Will return @c nil if an error occurs.
 */
- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)pattern range:(NSRange)searchRange withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Returns an array containing all the matches in the receiver that were matched by the regular expression @c pattern within @c searchRange. Each match result consists of a dictionary containing the matching substrings constructed from the specified set of keys and captures.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSDictionary containing that matches substrings constructed from the specified set of keys and captures.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Returns an array containing all the matches in the receiver that were matched by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions. Each match result consists of a dictionary containing that matches substrings constructed from the specified set of keys and captures.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSDictionary containing that matches substrings constructed from the specified set of keys and captures.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Returns an array containing all the matches in the receiver that were matched by the regular expression @c pattern within @c searchRange using @c options. Each match result consists of a dictionary containing that matches substrings constructed from the specified set of keys and captures.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param keys A @c NSArray object of NSString keys for the dictionaries.
 @param captures A @c NSArray object of NSNumber capture group values for the dictionaries.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSDictionary containing that matches substrings constructed from the specified set of keys and captures
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures;

/**
 Returns an array containing all the matches in the receiver that were matched by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions. Each match result consists of a dictionary containing that matches substrings constructed from the specified set of keys and captures.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param keys A @c NSArray object of NSString keys for the dictionaries.
 @param captures A @c NSArray object of NSNumber capture group values for the dictionaries.
 @return A @c NSArray object containing all the matches from the receiver by @c pattern. Each match result consists of a @c NSDictionary containing that matches substrings constructed from the specified set of keys and captures.
 @return Returns an empty array if @c pattern fails to match.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures;

#pragma mark - dictionaryByMatchingRegex:

/**
 Creates and returns a dictionary containing the matches constructed from the specified set of keys and captures for the first match of @c pattern in the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSDictionary containing the matched substrings constructed from the specified set of keys and captures.
 @return Will return @c nil if an error occurs.
 */
- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)pattern withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Creates and returns a dictionary containing the matches constructed from the specified set of keys and captures for the first match of @c pattern within @c searchRange of the receiver.

 @param pattern A @c NSString containing a regular expression.
 @param searchRange The range of the receiver to search.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSDictionary containing the matched substrings constructed from the specified set of keys and captures.
 @return Will return @c nil if an error occurs.
 */
- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)pattern range:(NSRange)searchRange withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Creates and returns a dictionary containing the matches constructed from the specified set of keys and captures for the first match of @c pattern within @c searchRange of the receiver using @c options.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSDictionary containing the matched substrings constructed from the specified set of keys and captures.
 @return Returns an empty dictionary if @c pattern fails to match withing @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Creates and returns a dictionary containing the matches constructed from the specified set of keys and captures for the first match of @c pattern within @c searchRange of the receiver using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param firstKey The first key to add to the new dictionary.
 @return A @c NSDictionary containing the matched substrings constructed from the specified set of keys and captures.
 @return Returns an empty dictionary if @c pattern fails to match withing @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Creates and returns a dictionary containing the matches constructed from the specified set of keys and captures for the first match of @c pattern within @c searchRange of the receiver using @c options.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param keys A @c NSArray object of NSString keys for the dictionary.
 @param captures A @c NSArray object of NSNumber capture group values for the dictionary.
 @return A @c NSDictionary containing the matched substrings constructed from the specified set of keys and captures.
 @return Returns an empty dictionary if @c pattern fails to match withing @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures;

/**
 Creates and returns a dictionary containing the matches constructed from the specified set of keys and captures for the first match of @c pattern within @c searchRange of the receiver using @c options and @c matchingOptions.

 @param pattern A @c NSString containing a regular expression.
 @param options A mask of options specified by combining @c RKXRegexOptions or @c NSRegularExpressionOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions The matching options to use. See @c NSMatchingOptions for possible values.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param keys A @c NSArray object of NSString keys for the dictionary.
 @param captures A @c NSArray object of NSNumber capture group values for the dictionary.
 @return A @c NSDictionary containing the matched substrings constructed from the specified set of keys and captures. 
 @return Returns an empty dictionary if @c pattern fails to match withing @c searchRange.
 @return Will return @c nil if an error occurs and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures;

#pragma mark - enumerateStringsMatchedByRegex:usingBlock:

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

/**
 Enumerates the matches in the receiver by the regular expression @c pattern and executes the block serially from left-to-right for each match found.

 @param pattern A @c NSString containing a valid regular expression.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns @c YES if there was no error, otherwise returns @c NO.
 */
- (BOOL)enumerateStringsMatchedByRegex:(NSString *)pattern usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the matches in the receiver by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions and executes the block using enumerationOptions for each match found.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns @c YES if there was no error, otherwise returns @c NO and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)enumerateStringsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;
/**
 Enumerates the matches in the receiver by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions and executes the block using @c enumOpts for each match found.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions A mask of options specified by combining NSMatchingOptions flags with the C bitwise @c OR operator. 0 may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param enumOpts Options for block enumeration operations. Use @c 0 for serial forward operations (best with left-to-right languages). Use @c NSEnumerationReverse for right-to-left languages. Behavior is undefined for @c NSEnumerationConcurrent.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns @c YES if there was no error, otherwise returns @c NO and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)enumerateStringsMatchedByRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error enumerationOptions:(NSEnumerationOptions)enumOpts usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

#pragma mark - enumerateStringsSeparatedByRegex:usingBlock:

/**
 Enumerates the strings of the receiver that have been divided by the regular expression @c pattern within @c searchRange using @c options and executes @c block for each divided string. The enumeration occurrs serially from left-to-right.

 @param pattern A @c NSString containing a valid regular expression.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns @c YES if there was no error, otherwise returns @c NO.
 */
- (BOOL)enumerateStringsSeparatedByRegex:(NSString *)pattern usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the strings of the receiver that have been divided by the regular expression @c pattern within @c searchRange using @c options and executes @c block for each divided string. The enumeration occurrs serially from left-to-right.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns @c YES if there was no error, otherwise returns @c NO and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)enumerateStringsSeparatedByRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the strings of the receiver that have been divided by the regular expression @c pattern within @c searchRange using @c options and and @c matchingOptions and executes @c block for each divided string. The enumeration is set by @c enumOpts.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions A mask of options specified by combining NSMatchingOptions flags with the C bitwise @c OR operator. 0 may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param enumOpts Options for block enumeration operations. Use @c 0 for serial forward operations (best with left-to-right languages). Use @c NSEnumerationReverse for right-to-left languages. Behavior is undefined for @c NSEnumerationConcurrent.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns @c YES if there was no error, otherwise returns @c NO and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (BOOL)enumerateStringsSeparatedByRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error enumerationOptions:(NSEnumerationOptions)enumOpts usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

#pragma mark - stringByReplacingOccurrencesOfRegex:usingBlock:

/**
 Enumerates the matches in the receiver by the regular expression @c pattern and executes @c block for each match found. Returns a string created by replacing the characters that were matched in the receiver with the contents of the string returned by @c block.

 @param pattern A @c NSString containing a valid regular expression.
 @param block The block that is executed for each match of @c pattern in the receiver. The block returns a @c NSString and takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return A @c NSString created from the characters of the receiver in which all matches of the regular expression @c pattern are replaced with the contents of the @c NSString returned by @c block. If the receiver is not matched by @c pattern then the string that is returned is a copy of the receiver as if @c stringWithString: had been sent to it.
 @return Returns @c nil if there was an error.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the matches in the receiver by the regular expression @c pattern within @c searchRange using @c options and executes @c block for each match found. Returns a string created by replacing the characters that were matched in the receiver with the contents of the string returned by @c block.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param block The block that is executed for each match of @c pattern in the receiver. The block returns a @c NSString and takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return A @c NSString created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options are replaced with the contents of the @c NSString returned by @c block. Returns the characters within @c searchRange as if @c substringWithRange: had been sent to the receiver if the substring is not matched by @c pattern.
 @return Returns @c nil if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the matches in the receiver by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions and executes @c block for each match found. Returns a string created by replacing the characters that were matched in the receiver with the contents of the string returned by @c block.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions A mask of options specified by combining NSMatchingOptions flags with the C bitwise @c OR operator. 0 may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param block The block that is executed for each match of @c pattern in the receiver. The block takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return A @c NSString created from the characters within @c searchRange of the receiver in which all matches of the regular expression @c pattern using @c options are replaced with the contents of the @c NSString returned by @c block. Returns the characters within @c searchRange as if @c substringWithRange: had been sent to the receiver if the substring is not matched by @c pattern.
 @return Returns @c nil if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;
#pragma clang diagnostic pop

@end

#pragma mark -

@interface NSMutableString (RegexKitX)

#pragma mark - replaceOccurrencesOfRegex:withTemplate:

/**
 Replaces all occurrences of the regular expression @c pattern using @c options and @c matchingOptions within @c searchRange with the contents of @c replacement string after performing capture group substitutions, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param template The string to use as the template text for matches by @c pattern. See ICU Replacement Text Syntax for more information.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template;

/**
 Replaces all occurrences of the regular expression @c pattern using @c options and @c matchingOptions within @c searchRange with the contents of @c replacement string after performing capture group substitutions, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param template The string to use as the template text for matches by @c pattern. See ICU Replacement Text Syntax for more information.
 @param searchRange The range of the receiver to search.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template range:(NSRange)searchRange;

/**
 Replaces all occurrences of the regular expression @c pattern using @c options and @c matchingOptions within @c searchRange with the contents of @c replacement string after performing capture group substitutions, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param template The string to use as the template text for matches by @c pattern. See ICU Replacement Text Syntax for more information.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template options:(RKXRegexOptions)options range:(NSRange)searchRange error:(NSError **)error;

/**
 Replaces all occurrences of the regular expression @c pattern using @c options and @c matchingOptions within @c searchRange with the contents of @c replacement string after performing capture group substitutions, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param template The string to use as the template text for matches by @c pattern. See ICU Replacement Text Syntax for more information.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions A mask of options specified by combining NSMatchingOptions flags with the C bitwise @c OR operator. @c 0 may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern withTemplate:(NSString *)template options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error;

#pragma mark - replaceOccurrencesOfRegex:usingBlock:

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

/**
 Enumerates the matches in the receiver by the regular expression @c pattern and executes @c block for each match found. Replaces the characters that were matched with the contents of the string returned by @c block, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param block The block that is executed for each match of @c pattern in the receiver. The block returns a @c NSString and takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the matches in the receiver by the regular expression @c pattern within @c searchRange using @c options and executes @c block for each match found. Replaces the characters that were matched with the contents of the string returned by @c block, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param block The block that is executed for each match of @c pattern in the receiver. The block returns a @c NSString and takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern options:(RKXRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;

/**
 Enumerates the matches in the receiver by the regular expression @c pattern within @c searchRange using @c options and @c matchingOptions and executes @c block for each match found. Replaces the characters that were matched with the contents of the string returned by @c block, returning the number of replacements made.

 @param pattern A @c NSString containing a valid regular expression.
 @param options A mask of options specified by combining RKXRegexOptions flags with the C bitwise @c OR operator. Either @c 0 or @c RKXNoOptions may be used if no options are required.
 @param matchingOptions A mask of options specified by combining NSMatchingOptions flags with the C bitwise @c OR operator. @c 0 may be used if no options are required.
 @param searchRange The range of the receiver to search.
 @param error An optional parameter that if set and an error occurs, will contain a @c NSError object that describes the problem. This may be set to @c NULL if information about any errors is not required.
 @param block The block that is executed for each match of @c pattern in the receiver. The block returns a @c NSString and takes four arguments:
 @param &nbsp;&nbsp;captureCount The number of strings that @c pattern captured. @c captureCount is always at least 1.
 @param &nbsp;&nbsp;capturedStrings A @c NSArray containing the substrings matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a pointer to a string that is equal to @c @@"".
 @param &nbsp;&nbsp;capturedRanges An array containing the ranges matched by each capture group present in @c pattern. The size of the array is @c captureCount. If a capture group did not match anything, it will contain a @c NSRange equal to @c {NSNotFound, 0}. The termination range at @c capturedRanges[captureCount] is @c {NSNotFound, NSUIntegerMax}.
 @param &nbsp;&nbsp;stop A reference to a Boolean value. The block can set the value to @c YES to stop further enumeration of the array. If a block stops further enumeration, that block continues to run until it’s finished. The stop argument is an out-only argument. You should only ever set this Boolean to @c YES within the block.
 @return Returns number of successful substitutions of the matched @c pattern.
 @return Returns @c NSNotFound if there was an error and indirectly returns a @c NSError object if @c error is not @c NULL.
 */
- (NSUInteger)replaceOccurrencesOfRegex:(NSString *)pattern options:(RKXRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block;
#pragma clang diagnostic pop

@end