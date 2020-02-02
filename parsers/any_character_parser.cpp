/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "any_character_parser.h"

/**
 *------------------------------------------
 * @brief The AnyCharacterParser class
 */

AnyCharacterParser::AnyCharacterParser(QSharedPointer<DelegateInterface> end, QString except)
    :Parser("AnyCharacterParser",end){
    s1_ = except;
}

AnyCharacterParser::~AnyCharacterParser(){}

Result AnyCharacterParser::parseOn(Context context) {
    const QString buffer = context.buffer();
    const int position = context.position();

    Result match = d1_->firstMatch(buffer, position);
    if (match.isSuccess()) {
        const int start = position;
        const int end = match.success().start();
        const QString except = s1_;
        if (start < end) {
            QRegExp rx = QRegExp(QString("([^%1])").arg(except));
            if(except.isEmpty() || except.isNull()){
                return Success(start,start+1);
            }
            QChar c  = buffer[start];
            if (rx.exactMatch(c)) {
                return Success(start,start+1);
            }else{
                return Failure(start, "AnyCharacterParser: unwanted character found");
            }
        }else{
            return Failure(start, "AnyCharacterParser: character not found");
        }
    } else {
        return Failure(position, "AnyCharacterParser: end not found");
    }

}

QSharedPointer<DelegateInterface> AnyCharacterParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new AnyCharacterParser(d1_,s1_),&DelegateInterface::deleter);
}


AnyCharacterParser any(const Parser &end, QString except) {
    return AnyCharacterParser(const_cast<Parser&>(end).makeShared(), except);
}

