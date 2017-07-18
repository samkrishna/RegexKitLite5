//
//  RegexKitLite5.m
//  RegexKitLite5
//
//  Created by Sam Krishna on 6/12/17.
//  Copyright © 2017 Sam Krishna. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

/*
  License
  Copyright © 2007-2008, John Engelhart

  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
  Neither the name of the Zang Industries nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import "RegexKitLite5.h"

#define RKL_EXPECTED(cond, expect)       __builtin_expect((long)(cond), (expect))

@implementation NSString (EntireRange)

- (NSRange)stringRange
{
    return NSMakeRange(0, self.length);
}

@end

@implementation NSString (RegexKitLite5)

#pragma mark - Caching Methods

+ (NSString *)cacheKeyForRegex:(NSString *)regexPattern options:(RKLRegexOptions)options
{
    NSString *key = [NSString stringWithFormat:@"%@_%lu", regexPattern, options];
    return key;
}

+ (NSRegularExpression *)cachedRegexForPattern:(NSString *)patten options:(RKLRegexOptions)options error:(NSError **)error
{
    NSString *regexKey = [NSString cacheKeyForRegex:patten options:options];
    NSMutableDictionary *dictionary = [[NSThread currentThread] threadDictionary];
    NSRegularExpression *regex = dictionary[regexKey];
    
    if (!regex) {
        NSRegularExpressionOptions regexOptions = (NSRegularExpressionOptions)options;
        regex = [NSRegularExpression regularExpressionWithPattern:patten options:regexOptions error:error];
        if (!regex) return nil;
        dictionary[regexKey] = regex;
    }
    
    return regex;
}

#pragma mark - componentsSeparatedByRegex:

- (NSArray *)componentsSeparatedByRegex:(NSString *)regexPattern
{
    return [self componentsSeparatedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:[self stringRange] error:NULL];
}

- (NSArray *)componentsSeparatedByRegex:(NSString *)regexPattern range:(NSRange)range
{
    return [self componentsSeparatedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:range error:NULL];
}

- (NSArray *)componentsSeparatedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error
{
    return [self componentsSeparatedByRegex:regexPattern options:options matchingOptions:0 range:range error:NULL];
}

- (NSArray *)componentsSeparatedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }

    // Repurposed from https://stackoverflow.com/a/9185677
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    NSArray *matchResults = [regex matchesInString:self options:matchingOptions range:range];
    NSMutableArray *returnArray = [NSMutableArray arrayWithCapacity:matchResults.count];
    __block NSUInteger pos = 0;

    [regex enumerateMatchesInString:self options:matchingOptions range:range usingBlock:^(NSTextCheckingResult * _Nullable result, NSMatchingFlags flags, BOOL * _Nonnull stop) {
        NSRange substrRange = NSMakeRange(pos, [result range].location - pos);
        [returnArray addObject:[self substringWithRange:substrRange]];
        pos = [result range].location + [result range].length;
    }];
    
    if (pos < range.length) {
        [returnArray addObject:[self substringFromIndex:pos]];
    }
    
    return returnArray;
}

#pragma mark - isMatchedByRegex:

- (BOOL)isMatchedByRegex:(NSString *)regexPattern
{
    return [self isMatchedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] error:NULL];
}

- (BOOL)isMatchedByRegex:(NSString *)regexPattern inRange:(NSRange)range
{
    return [self isMatchedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:range error:NULL];
}

- (BOOL)isMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)range error:(NSError **)error
{
    return [self isMatchedByRegex:regexPattern options:options matchingOptions:0 inRange:range error:error];
}

- (BOOL)isMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)range error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return NO;
    }

    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return NO;
    NSUInteger matchCount = [regex numberOfMatchesInString:self options:matchingOptions range:range];

    return (matchCount > 0);
}

#pragma mark - rangeOfRegex:

- (NSRange)rangeOfRegex:(NSString *)regexPattern
{
    return [self rangeOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] capture:0 error:NULL];
}

- (NSRange)rangeOfRegex:(NSString *)regexPattern capture:(NSUInteger)capture
{
    return [self rangeOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] capture:capture error:NULL];
}

- (NSRange)rangeOfRegex:(NSString *)regexPattern inRange:(NSRange)range
{
    return [self rangeOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:range capture:0 error:NULL];
}

- (NSRange)rangeOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)range capture:(NSUInteger)capture error:(NSError **)error
{
    return [self rangeOfRegex:regexPattern options:options matchingOptions:0 inRange:range capture:capture error:error];
}

- (NSRange)rangeOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)range capture:(NSUInteger)capture error:(NSError **)error
{
    NSCParameterAssert(capture >= 0);
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return NSMakeRange(NSNotFound, NSIntegerMax);
    }

    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return NSMakeRange(NSNotFound, NSIntegerMax);

    if ([self isMatchedByRegex:regexPattern options:options matchingOptions:matchingOptions inRange:range error:error]) {
        NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
        NSTextCheckingResult *firstMatch = matches[0];
        return [firstMatch rangeAtIndex:capture];
    }

    return NSMakeRange(NSNotFound, 0);
}

#pragma mark - rangesOfRegex:

- (NSArray *)rangesOfRegex:(NSString *)regexPattern
{
    return [self rangesOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] error:NULL];
}

- (NSArray *)rangesOfRegex:(NSString *)regexPattern inRange:(NSRange)searchRange
{
    return [self rangesOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:searchRange error:NULL];
}

- (NSArray *)rangesOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)searchRange error:(NSError **)error
{
    return [self rangesOfRegex:regexPattern options:options matchingOptions:0 inRange:searchRange error:error];
}

- (NSArray *)rangesOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }

    NSMutableArray *ranges = [NSMutableArray array];
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;

    if ([self isMatchedByRegex:regexPattern options:options matchingOptions:matchingOptions inRange:searchRange error:error]) {
        [regex enumerateMatchesInString:self options:matchingOptions range:searchRange usingBlock:^(NSTextCheckingResult * _Nullable match, NSMatchingFlags flags, BOOL * _Nonnull stop) {
            for (NSUInteger i = 0; i < match.numberOfRanges; i++) {
                NSRange matchRange = [match rangeAtIndex:i];
                [ranges addObject:[NSValue valueWithRange:matchRange]];
            }
        }];

        return [ranges copy];
    }

    return nil;
}

#pragma mark - stringByMatching:

- (NSString *)stringByMatching:(NSString *)regexPattern
{
    return [self stringByMatching:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] capture:0 error:NULL];
}

- (NSString *)stringByMatching:(NSString *)regexPattern capture:(NSUInteger)capture
{
    return [self stringByMatching:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] capture:capture error:NULL];
}

- (NSString *)stringByMatching:(NSString *)regexPattern inRange:(NSRange)searchRange
{
    return [self stringByMatching:regexPattern options:RKLNoOptions matchingOptions:0 inRange:searchRange capture:0 error:NULL];
}

- (NSString *)stringByMatching:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error
{
    return [self stringByMatching:regexPattern options:options matchingOptions:0 inRange:searchRange capture:capture error:error];
}

- (NSString *)stringByMatching:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)searchRange capture:(NSUInteger)capture error:(NSError **)error
{
    NSCParameterAssert(capture >= 0);
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }

    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    __block NSTextCheckingResult *firstMatch = nil;
    
    [regex enumerateMatchesInString:self options:matchingOptions range:searchRange usingBlock:^(NSTextCheckingResult * _Nullable result, NSMatchingFlags flags, BOOL * _Nonnull stop) {
        firstMatch = result;
        *stop = YES;
    }];
    
    if (firstMatch) {
        NSString *result = [self substringWithRange:[firstMatch rangeAtIndex:capture]];
        return result;
    }
    
    return nil;
}

#pragma mark - stringByReplacincOccurrencesOfRegex:withString:


- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement
{
    return [self stringByReplacingOccurrencesOfRegex:regexPattern withString:replacement options:RKLNoOptions matchingOptions:0 range:[self stringRange] error:NULL];
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement range:(NSRange)searchRange
{
    return [self stringByReplacingOccurrencesOfRegex:regexPattern withString:replacement options:RKLNoOptions matchingOptions:0 range:searchRange error:NULL];
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement options:(RKLRegexOptions)options range:(NSRange)searchRange error:(NSError **)error
{
    return [self stringByReplacingOccurrencesOfRegex:regexPattern withString:replacement options:options matchingOptions:0 range:searchRange error:error];
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:searchRange];
    NSMutableString *target = [self mutableCopy];

    if (![matches count]) {
        return [self substringWithRange:searchRange];
    }

    for (NSTextCheckingResult *match in [matches reverseObjectEnumerator]) {
        if (match.range.location != NSNotFound) {
            [target replaceCharactersInRange:match.range withString:replacement];
        }
    }
    
    return [target copy];
}

#pragma mark - captureCount:

- (NSInteger)captureCount
{
    NSError *error;
    return [self captureCountWithOptions:RKLNoOptions error:&error];
}

- (NSInteger)captureCountWithOptions:(RKLRegexOptions)options error:(NSError **)error
{
    if (error == NULL) {
        if (![self isRegexValid]) return -1;
    }

    NSRegularExpression *regex = [NSString cachedRegexForPattern:self options:options error:error];
    
    if (regex) {
        return (NSInteger)regex.numberOfCaptureGroups;
    }
    
    return -1;
}

#pragma mark - isRegexValid

- (BOOL)isRegexValid
{
    return [self isRegexValidWithOptions:RKLNoOptions error:NULL];
}

- (BOOL)isRegexValidWithOptions:(RKLRegexOptions)options error:(NSError **)error
{
    if (error == NULL) {
        NSError *localError;
        [NSString cachedRegexForPattern:self options:options error:&localError];
        if (localError) return NO;
    }
    else {
        [NSString cachedRegexForPattern:self options:options error:error];
        if (*error) return NO;
    }

    return YES;
}

#pragma mark - componentsMatchedByRegex:

- (NSArray *)componentsMatchedByRegex:(NSString *)regexPattern
{
    return [self componentsMatchedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:[self stringRange] capture:0 error:NULL];
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regexPattern capture:(NSUInteger)capture
{
    return [self componentsMatchedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:[self stringRange] capture:capture error:NULL];
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regexPattern range:(NSRange)range
{
    return [self componentsMatchedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:range capture:0 error:NULL];
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range capture:(NSUInteger)capture error:(NSError **)error
{
    return [self componentsMatchedByRegex:regexPattern options:options matchingOptions:0 range:range capture:capture error:error];
}

- (NSArray *)componentsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range capture:(NSUInteger)capture error:(NSError **)error
{
    NSCParameterAssert(capture >= 0);
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }

    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    
    if ([self isMatchedByRegex:regexPattern options:options matchingOptions:matchingOptions inRange:range error:error]) {
        NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
        NSMutableArray *finalCaptures = [NSMutableArray array];
        
        for (NSTextCheckingResult *match in matches) {
            NSMutableArray *captureArray = [NSMutableArray arrayWithCapacity:match.numberOfRanges];

            for (NSUInteger i = 0; i < match.numberOfRanges; i++) {
                NSRange matchRange = [match rangeAtIndex:i];
                NSString *matchString = (matchRange.location != NSNotFound) ? [self substringWithRange:matchRange] : @"";
                [captureArray addObject:matchString];
            }
            
            [finalCaptures addObject:captureArray[capture]];
        }
        
        return [finalCaptures copy];
    }
    
    return nil;
}

#pragma mark - captureComponentsMatchedByRegex:

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regexPattern
{
    return [self captureComponentsMatchedByRegex:regexPattern options:RKLNoOptions range:[self stringRange] error:NULL];
}

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regexPattern range:(NSRange)range
{
    return [self captureComponentsMatchedByRegex:regexPattern options:RKLNoOptions range:range error:NULL];
}

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error
{
    return [self captureComponentsMatchedByRegex:regexPattern options:options range:range error:error];
}

- (NSArray *)captureComponentsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
    NSTextCheckingResult *firstMatch = matches[0];
    NSMutableArray *captureArray = [NSMutableArray arrayWithCapacity:firstMatch.numberOfRanges];
    
    for (NSUInteger i = 0; i < firstMatch.numberOfRanges; i++) {
        NSRange matchRange = [firstMatch rangeAtIndex:i];
        NSString *matchString = (matchRange.location != NSNotFound) ? [self substringWithRange:matchRange] : @"";
        [captureArray addObject:matchString];
    }
    
    return [captureArray copy];
}

#pragma mark - arrayOfCaptureComponentsMatchedByRegex:
// Eventually use this: https://gist.github.com/kamiro/3902122

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regexPattern
{
    return [self arrayOfCaptureComponentsMatchedByRegex:regexPattern options:RKLNoOptions range:[self stringRange] error:NULL];
}

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regexPattern range:(NSRange)range
{
    return [self arrayOfCaptureComponentsMatchedByRegex:regexPattern options:RKLNoOptions range:range error:NULL];
}

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error
{
    return [self arrayOfCaptureComponentsMatchedByRegex:regexPattern options:options range:range error:NULL];
}

- (NSArray *)arrayOfCaptureComponentsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }

    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
    NSMutableArray *matchCaptures = [NSMutableArray array];
    
    for (NSTextCheckingResult *match in matches) {
        NSMutableArray *captureArray = [NSMutableArray arrayWithCapacity:match.numberOfRanges];
        
        for (NSUInteger i = 0; i < match.numberOfRanges; i++) {
            NSRange matchRange = [match rangeAtIndex:i];
            NSString *matchString = (matchRange.location != NSNotFound) ? [self substringWithRange:matchRange] : @"";
            [captureArray addObject:matchString];
        }
        
        [matchCaptures addObject:captureArray];
    }
    
    return [matchCaptures copy];
}

#pragma mark - arrayOfDictionariesByMatchingRegex:

- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)regexPattern withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSArray *dictArray = [self arrayOfDictionariesByMatchingRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:[self stringRange] error:NULL withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    
    return dictArray;
}

- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)regexPattern range:(NSRange)range withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSArray *dictArray = [self arrayOfDictionariesByMatchingRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:range error:NULL withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    
    return dictArray;
}

- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSArray *dictArray = [self arrayOfDictionariesByMatchingRegex:regexPattern options:options matchingOptions:0 range:range error:error withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    
    return dictArray;
}

- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSArray *dictArray = [self arrayOfDictionariesByMatchingRegex:regexPattern options:options matchingOptions:0 range:range error:error withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);

    return dictArray;
}

- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures
{
    return [self arrayOfDictionariesByMatchingRegex:regexPattern options:options matchingOptions:0 range:range error:error withKeys:keys forCaptures:captures];
}

- (NSArray *)arrayOfDictionariesByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures
{
    NSCParameterAssert([keys count] == [captures count]);
    
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }
    else {
        [NSString cachedRegexForPattern:regexPattern options:options error:error];
        if (error) return nil;
    }

    NSMutableArray *arrayOfDicts = [NSMutableArray array];
    
    [self enumerateStringsMatchedByRegex:regexPattern options:options matchingOptions:matchingOptions inRange:range error:error enumerationOptions:0 usingBlock:^(NSUInteger captureCount, NSArray *capturedStrings, const NSRange *capturedRanges, volatile BOOL *const stop) {
        NSString *mainString = capturedStrings[0];
        NSDictionary *dict = [mainString dictionaryByMatchingRegex:regexPattern options:options matchingOptions:matchingOptions range:[mainString stringRange] error:error withKeys:keys forCaptures:captures];
        [arrayOfDicts addObject:dict];
    }];
    
    return [arrayOfDicts copy];
}

#pragma mark - dictionaryByMatchingRegex:

- (NSArray *)_keysForVarArgsList:(va_list)varArgsList withFirstKey:(id)firstKey andIndexes:(NSArray **)captureIndexes
{
    NSMutableArray *captureKeys = [NSMutableArray arrayWithCapacity:64];
    NSMutableArray *captureKeyIndexes = [NSMutableArray arrayWithCapacity:64];
    NSUInteger captureKeysCount = 0UL;
    
    if (varArgsList != NULL) {
        while (captureKeysCount < 62UL) {
            id  thisCaptureKey = (captureKeysCount == 0) ? firstKey : va_arg(varArgsList, id);
            if (RKL_EXPECTED(thisCaptureKey == NULL, 0L)) { break; }
            int thisCaptureKeyIndex = va_arg(varArgsList, int);
            [captureKeys addObject:thisCaptureKey];
            [captureKeyIndexes addObject:@(thisCaptureKeyIndex)];
            captureKeysCount++;
        }
    }
    
    *captureIndexes = [captureKeyIndexes copy];
    return [captureKeys copy];
}

- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)regexPattern withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSDictionary *dict = [self dictionaryByMatchingRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:[self stringRange] error:NULL withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    return dict;
}

- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)regexPattern range:(NSRange)range withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *keys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSDictionary *dict = [self dictionaryByMatchingRegex:regexPattern options:RKLNoOptions matchingOptions:0 range:range error:NULL withKeys:keys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    return dict;
}

- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSDictionary *dict = [self dictionaryByMatchingRegex:regexPattern options:options matchingOptions:0 range:range error:error withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    return dict;
}

- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error withKeysAndCaptures:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION
{
    va_list varArgsList;
    va_start(varArgsList, firstKey);
    NSArray *captureKeyIndexes;
    NSArray *captureKeys = [self _keysForVarArgsList:varArgsList withFirstKey:firstKey andIndexes:&captureKeyIndexes];
    NSDictionary *dict = [self dictionaryByMatchingRegex:regexPattern options:options matchingOptions:matchingOptions range:range error:error withKeys:captureKeys forCaptures:captureKeyIndexes];
    va_end(varArgsList);
    return dict;
}

- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options range:(NSRange)range error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures
{
    return [self dictionaryByMatchingRegex:regexPattern options:options matchingOptions:0 range:range error:error withKeys:keys forCaptures:captures];
}

- (NSDictionary *)dictionaryByMatchingRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)range error:(NSError **)error withKeys:(NSArray *)keys forCaptures:(NSArray *)captures
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }
    else {
        [NSString cachedRegexForPattern:regexPattern options:options error:error];
        if (error) return nil;
    }
    
    NSUInteger count = [keys count];
    NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithCapacity:count];
    
    for (NSUInteger i = 0; i < count; i++) {
        id key = keys[i];
        NSUInteger capture = [captures[i] unsignedIntegerValue];
        NSRange captureRange = [self rangeOfRegex:regexPattern options:options matchingOptions:matchingOptions inRange:range capture:capture error:error];
        if (captureRange.location == NSNotFound && captureRange.length == NSIntegerMax) return @{};
        dict[key] = (captureRange.location != NSNotFound) ? [self substringWithRange:captureRange] : @"";
    }
    
    return [dict copy];
}

#pragma mark - enumerateStringsMatchedByRegex:usingBlock:

- (BOOL)enumerateStringsMatchedByRegex:(NSString *)regexPattern usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self enumerateStringsMatchedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] error:NULL enumerationOptions:0 usingBlock:block];
}

- (BOOL)enumerateStringsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)range error:(NSError **)error usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self enumerateStringsMatchedByRegex:regexPattern options:options matchingOptions:0 inRange:range error:NULL enumerationOptions:0 usingBlock:block];
}

- (BOOL)enumerateStringsMatchedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)range error:(NSError **)error enumerationOptions:(NSEnumerationOptions)enumerationOptions usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return NO;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return NO;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
    __block BOOL blockStop = NO;
    
    [matches enumerateObjectsWithOptions:enumerationOptions usingBlock:^(NSTextCheckingResult *match, NSUInteger idx, BOOL * _Nonnull stop) {
        NSUInteger captureCount = match.numberOfRanges;
        NSMutableArray *captures = [NSMutableArray array];
        NSRange rangeCaptures[captureCount];
        
        for (NSUInteger rangeIndex = 0; rangeIndex < captureCount; rangeIndex++) {
            NSRange subrange = [match rangeAtIndex:rangeIndex];
            rangeCaptures[rangeIndex] = subrange;
            NSString *substring = (subrange.location != NSNotFound) ? [self substringWithRange:subrange] : @"";
            [captures addObject:substring];
        }
        
        rangeCaptures[captureCount] = NSMakeRange(NSNotFound, NSIntegerMax);
        block(captureCount, [captures copy], rangeCaptures, &blockStop);
        *stop = blockStop;
    }];

    return YES;
}

#pragma mark - enumerateStringsSeparatedByRegex:usingBlock:

- (BOOL)enumerateStringsSeparatedByRegex:(NSString *)regexPattern usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self enumerateStringsSeparatedByRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] error:NULL usingBlock:block];
}

- (BOOL)enumerateStringsSeparatedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)range error:(NSError **)error usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self enumerateStringsSeparatedByRegex:regexPattern options:options matchingOptions:0 inRange:range error:error usingBlock:block];
}

- (BOOL)enumerateStringsSeparatedByRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)range error:(NSError **)error usingBlock:(void (^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return NO;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return NO;
    NSString *cloneString = [NSString stringWithString:self];
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
    __block BOOL blockStop = NO;
    __block NSRange remainderRange;
    
    [matches enumerateObjectsUsingBlock:^(NSTextCheckingResult *match, NSUInteger idx, BOOL * _Nonnull stop) {
        NSUInteger captureCount = match.numberOfRanges;
        NSMutableArray *captures = [NSMutableArray array];
        NSRange rangeCaptures[captureCount];
        
        for (NSUInteger rangeIndex = 0; rangeIndex < captureCount; rangeIndex++) {
            NSRange subrange = [match rangeAtIndex:rangeIndex];
            
            if (![captures count]) {
                NSString *targetString;
                NSRange targetRange;
                
                if (idx == 0) {
                    targetString = [cloneString substringToIndex:subrange.location];
                    targetRange = [cloneString rangeOfString:targetString];
                }
                else {
                    targetRange = NSMakeRange(remainderRange.location, (subrange.location - remainderRange.location));
                    targetString = [cloneString substringWithRange:targetRange];
                }

                [captures addObject:targetString];
                rangeCaptures[rangeIndex] = targetRange;
                NSUInteger newLocation = subrange.location + subrange.length;
                NSString *remainderString = [cloneString substringFromIndex:newLocation];
                remainderRange = [cloneString rangeOfString:remainderString];
            }
            else {
                rangeCaptures[rangeIndex] = subrange;
                NSString *substring = (subrange.location != NSNotFound) ? [self substringWithRange:subrange] : @"";
                [captures addObject:substring];
            }
        }
        
        rangeCaptures[captureCount] = NSMakeRange(NSNotFound, NSIntegerMax);
        block(captureCount, [captures copy], rangeCaptures, &blockStop);
        *stop = blockStop;
    }];
    
    return YES;
}


#pragma mark - stringByReplacingOccurrencesOfRegex:usingBlock:

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self stringByReplacingOccurrencesOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] error:NULL usingBlock:block];
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)range error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self stringByReplacingOccurrencesOfRegex:regexPattern options:options matchingOptions:0 inRange:range error:error usingBlock:block];
}

- (NSString *)stringByReplacingOccurrencesOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)range error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return nil;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return nil;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
    NSMutableString *target = [NSMutableString stringWithString:self];
    BOOL stop = NO;
    
    if (![matches count]) {
        return [NSString stringWithString:self];
    }
    
    for (NSTextCheckingResult *match in [matches reverseObjectEnumerator]) {
        NSUInteger captureCount = match.numberOfRanges;
        NSMutableArray *captures = [NSMutableArray array];
        NSRange rangeCaptures[captureCount];
        
        for (NSUInteger rangeIndex = 0; rangeIndex < captureCount; rangeIndex++) {
            NSRange subrange = [match rangeAtIndex:rangeIndex];
            rangeCaptures[rangeIndex] = subrange;
            NSString *substring = (subrange.location != NSNotFound) ? [self substringWithRange:subrange] : @"";
            [captures addObject:substring];
        }
        
        rangeCaptures[captureCount] = NSMakeRange(NSNotFound, NSIntegerMax);
        NSString *replacement = block(captureCount, [captures copy], rangeCaptures, &stop);
        [target replaceCharactersInRange:match.range withString:replacement];
        
        if (stop == YES) {
            break;
        }
    }
    
    return [target copy];
}

@end

@implementation NSMutableString (RegexKitLite5)

#pragma mark - replaceOccurrencesOfRegex:withString:


- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement
{
    return [self replaceOccurrencesOfRegex:regexPattern withString:replacement options:RKLNoOptions matchingOptions:0 range:[self stringRange] error:NULL];
}

- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement range:(NSRange)searchRange
{
    return [self replaceOccurrencesOfRegex:regexPattern withString:replacement options:RKLNoOptions matchingOptions:0 range:searchRange error:NULL];
}

- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement options:(RKLRegexOptions)options range:(NSRange)searchRange error:(NSError **)error
{
    return [self replaceOccurrencesOfRegex:regexPattern withString:replacement options:options matchingOptions:0 range:searchRange error:error];
}

- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern withString:(NSString *)replacement options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions range:(NSRange)searchRange error:(NSError **)error
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return -1;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return -1;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:searchRange];
    NSInteger count = 0;
    
    for (NSTextCheckingResult *match in [matches reverseObjectEnumerator]) {
        if (match.range.location != NSNotFound) {
            [self replaceCharactersInRange:match.range withString:replacement];
            count++;
        }
    }
    
    return count;
}


#pragma mark - replaceOccurrencesOfRegex:usingBlock:

- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self replaceOccurrencesOfRegex:regexPattern options:RKLNoOptions matchingOptions:0 inRange:[self stringRange] error:NULL usingBlock:block];
}

- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options inRange:(NSRange)range error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    return [self replaceOccurrencesOfRegex:regexPattern options:options matchingOptions:0 inRange:range error:error usingBlock:block];
}

- (NSInteger)replaceOccurrencesOfRegex:(NSString *)regexPattern options:(RKLRegexOptions)options matchingOptions:(NSMatchingOptions)matchingOptions inRange:(NSRange)range error:(NSError **)error usingBlock:(NSString *(^)(NSUInteger captureCount, NSArray *capturedStrings, const NSRange capturedRanges[captureCount], volatile BOOL * const stop))block
{
    if (error == NULL) {
        if (![regexPattern isRegexValid]) return -1;
    }
    
    NSRegularExpression *regex = [NSString cachedRegexForPattern:regexPattern options:options error:error];
    if (error) return -1;
    NSArray *matches = [regex matchesInString:self options:matchingOptions range:range];
    NSInteger count = 0;
    BOOL stop = NO;
    
    if (![matches count]) {
        return 0;
    }
    
    for (NSTextCheckingResult *match in [matches reverseObjectEnumerator]) {
        NSUInteger captureCount = match.numberOfRanges;
        NSMutableArray *captures = [NSMutableArray array];
        NSRange rangeCaptures[captureCount];
        
        for (NSUInteger rangeIndex = 0; rangeIndex < captureCount; rangeIndex++) {
            NSRange subrange = [match rangeAtIndex:rangeIndex];
            rangeCaptures[rangeIndex] = subrange;
            NSString *substring = (subrange.location != NSNotFound) ? [self substringWithRange:subrange] : @"";
            [captures addObject:substring];
        }
        
        rangeCaptures[captureCount] = NSMakeRange(NSNotFound, NSIntegerMax);
        NSString *replacement = block(captureCount, [captures copy], rangeCaptures, &stop);
        [self replaceCharactersInRange:match.range withString:replacement];
        count++;
        
        if (stop == YES) {
            break;
        }
    }
    
    return count;
}

@end


