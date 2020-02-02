/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "pattern_parser.h"
#include <QString>
#include <QRegExp>


PatternParser::PatternParser(const char *pattern)
    : PARSER_NAME(PatternParser) {
    pattern_ = pattern;
}

PatternParser::PatternParser(const PatternParser &other)
    : PARSER_NAME(PatternParser){
    pattern_ = other.pattern_;
}

Result PatternParser::parseOn(Context context) {
    const QString buffer = context.buffer();
    const int position = context.position();
    QRegExp rx = QRegExp(QString("([%1])").arg(pattern_));
    if(position < buffer.length()){
        const QChar c  = buffer[position];
        if(rx.exactMatch(c)){
            return Success(position, position+1);
        }else{
            return Failure(position);
        }
    }else{
        return Failure(buffer.length());
    }
}

QSharedPointer<DelegateInterface> PatternParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new PatternParser(pattern_),&DelegateInterface::deleter);
}

PatternParser pattern(const char *pattern) {return  PatternParser(pattern);}

PatternParser letter() {return pattern("a-zA-Z");}

PatternParser digit() {return  pattern("0-9");}

Parser word() { return (letter() | digit()); }
