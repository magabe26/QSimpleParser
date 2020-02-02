/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef PATTERN_PARSER_H
#define PATTERN_PARSER_H

#include "core/core.h"

/**
  *--------------------------------------
 * @brief The PatternParser class
 */
class PatternParser: public Parser {

public:
    PatternParser(const char* pattern);
    PatternParser(const PatternParser& other);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

private:
    const char* pattern_;
    // Delegate interface
    Result parseOn(Context context);
};

PatternParser pattern(const char* pattern);

PatternParser letter();

PatternParser digit();

Parser word();

#endif // PATTERN_PARSER_H
