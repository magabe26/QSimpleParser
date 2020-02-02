/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#ifndef CHAR_PARSERS_H
#define CHAR_PARSERS_H

#include "core/core.h"
#include "any_character_parser.h"

/**
 *-----------------------------------------------
 * @brief The CharParser class
 */
class CharParser: public Parser {
public:
    CharParser(char c1_);
    CharParser(const CharParser& other);

    virtual ~CharParser();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

private:
    char char_;
    // Delegate interface
    Result parseOn(Context context);
};

/**
 *--------------------------------------------------
 * @brief The LastCharParserDelegate class
 */
class LastCharParserDelegate: public Parser {
public:

    LastCharParserDelegate();
    LastCharParserDelegate(const LastCharParserDelegate& other);
    virtual ~LastCharParserDelegate();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

/**
 *--------------------------------------------------
 * @brief The LastCharParser class
 */
class LastCharParser: public Parser {
public:

    LastCharParser();
    LastCharParser(const LastCharParser& other);
    virtual ~LastCharParser();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};


/**
 *----------------------------------------------------
 * @brief The FirstCharParser class
 */
class FirstCharParser: public Parser {
public:

    FirstCharParser();
    FirstCharParser(const FirstCharParser& other);
    virtual ~FirstCharParser();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

CharParser chaR(char c);

FirstCharParser firstChar();

LastCharParser lastChar();

Parser remainingChars();

Parser charsBefore(Parser parser);

Parser newLine();

#endif // CHAR_PARSERS_H
