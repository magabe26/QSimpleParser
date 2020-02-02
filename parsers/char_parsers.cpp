/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "char_parsers.h"

/**
 *-----------------------------------------------
 * @brief The CharParser class
 */
CharParser::CharParser(char c):PARSER_NAME(CharParser) {
    char_ = c;
}

CharParser::CharParser(const CharParser &other)
    :PARSER_NAME(CharParser)
    ,char_ {other.char_}{

}

CharParser::~CharParser(){}

Result CharParser::parseOn(Context context) {
    const QString buffer = context.buffer();
    const int position = context.position();
    if (position < buffer.length()) {
        if (buffer[position] == char_) {
            const int start = position;
            const int end = start + 1;
            return Success(start, end);
        } else {
            return Failure(position);
        }
    }
    return Failure(buffer.length());
}

QSharedPointer<DelegateInterface> CharParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new CharParser(char_),&DelegateInterface::deleter);
}


/**
 *--------------------------------------------------
 * @brief The LastCharParserDelegate class
 */
LastCharParserDelegate::LastCharParserDelegate():PARSER_NAME(LastCharParserDelegate){}

LastCharParserDelegate::LastCharParserDelegate(const LastCharParserDelegate &other)
    : PARSER_NAME(LastCharParserDelegate)
{
    Q_UNUSED(other)
}


LastCharParserDelegate::~LastCharParserDelegate(){}

Result LastCharParserDelegate::parseOn(Context context) {
    const QString buffer = context.buffer();
    const int position = context.position();
    if (position == buffer.length() - 1) {
        return Success(position, buffer.length());
    } else {
        return Failure(position, "Not the end of input");
    }
}

QSharedPointer<DelegateInterface> LastCharParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new LastCharParserDelegate(),&DelegateInterface::deleter);
}


/**
 *--------------------------------------------------
 * @brief The LastCharParser class
 */
LastCharParser::LastCharParser():PARSER_NAME(LastCharParser){}

LastCharParser::LastCharParser(const LastCharParser &other):PARSER_NAME(LastCharParser){
    Q_UNUSED(other)
}

LastCharParser::~LastCharParser(){}

Result LastCharParser::parseOn(Context context) {
    try {
        return LastCharParserDelegate().plus().parse(context.buffer(),context.position());
    } catch (Error e) {
        return  Failure(context.position(),e.toString());
    }
}

QSharedPointer<DelegateInterface> LastCharParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new LastCharParser(),&DelegateInterface::deleter);
}


/**
 *----------------------------------------------------
 * @brief The FirstCharParser class
 */
FirstCharParser::FirstCharParser():PARSER_NAME(FirstCharParser){}

FirstCharParser::FirstCharParser(const FirstCharParser &other):PARSER_NAME(FirstCharParser){
    Q_UNUSED(other)
}

FirstCharParser::~FirstCharParser(){}

Result FirstCharParser::parseOn(Context context) {
    const int position = context.position();
    if (position == 0) {
        return Success(position, 1);
    } else {
        return Failure(position, "Not the end of input");
    }
}

QSharedPointer<DelegateInterface> FirstCharParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new FirstCharParser(),&DelegateInterface::deleter);
}

CharParser chaR(char c) {
    return CharParser(c);
}

FirstCharParser firstChar()  {
    return FirstCharParser();
}

LastCharParser lastChar() {
    return LastCharParser();
}

Parser remainingChars() { return any(lastChar()).star().seq(lastChar()); }

Parser charsBefore(Parser parser) {return any(parser).star();}

Parser newLine() { return  chaR('\n'); }
