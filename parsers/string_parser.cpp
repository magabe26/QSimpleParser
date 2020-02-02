/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "string_parser.h"

StringParser::StringParser(QString string, bool caseSensitive)
    :PARSER_NAME(StringParser)
    ,string_{string}
    ,caseSensitive_{caseSensitive}
    ,failedAt_ {-1}{

}

StringParser::StringParser(const StringParser &other):PARSER_NAME(StringParser){
    string_ = other.string_;
    caseSensitive_ = other.caseSensitive_;
    failedAt_ = other.failedAt_;
}

StringParser::~StringParser(){}

Result StringParser::parseOn(Context context) {
    const QString buffer = context.buffer();
    if (context.position() < buffer.length()) {
        if ((failedAt_ != -1) && (context.position() <= failedAt_)) {
            return Failure(context.position(), "StringParser::Failed , No match found");
        }
        const int start = context.position();
        int end = context.position();

        for (int i = 0; i < string_.length(); i++, end++) {
            const bool match = caseSensitive_
                    ? (string_[i] == buffer[end])
                    : ((string_[i].toLower() == buffer[end]) ||
                       (string_[i].toUpper() == buffer[end]));

            if (!match) {
                failedAt_ = end;
                return Failure(failedAt_, "StringParser:: Failed , No match found");
            }
        }
        failedAt_ = -1;
        return Success(start, end);
    } else {
        return Failure(buffer.length(), "StringParser:: Failed , No match found");
    }
}

QSharedPointer<DelegateInterface> StringParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new StringParser(string_,caseSensitive_),&DelegateInterface::deleter);
}

StringParser string(QString string, bool caseSensitive) {return StringParser(string,caseSensitive);}
