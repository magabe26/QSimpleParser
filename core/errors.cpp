/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "errors.h"

/**
 *--------------------------------------------------
 * @brief The Error class
 */
Error::Error(QString message):message_{message}{}

Error::Error(const Error &other){
    message_ = other.message_;
}

Error::~Error(){}

QString Error::toString(){
    return message_;
}


/**
 *--------------------------------------------------
 * @brief The RangeError class
 */
RangeError::RangeError(int invalidValue, int minValue, int maxValue, QString name, QString message):Error(message){
    start_ = minValue;
    end_ = maxValue;
    this->invalidValue_ = invalidValue;
    this->name_ = name;
}

int RangeError::start() const
{
    return start_;
}

int RangeError::end() const
{
    return end_;
}

QString RangeError::message() const
{
    if(message_.isEmpty()){

        QString explanation = "";
        if (end_ > start_) {
            explanation = QString(": Not in range %1..%2, inclusive").arg(start_).arg(end_) ;
        } else if (end_ < start_) {
            explanation = ": Valid value range is empty";
        } else {
            explanation = QString(": Only valid value is %1").arg(start_);
        }
        return explanation;
    }else{
        return message_;
    }
}

QString RangeError::toString(){
    return message();
}

int RangeError::checkValidRange(int start, int end, int length, QString startName, QString endName, QString message) {
    // Comparing with `0` as receiver produces better dart2js type inference.
    // Ditto `start > end` below.
    if (0 > start || start > length) {
        if(startName.isEmpty())
            startName = "start";
        throw RangeError(start, 0, length, startName, message);
    }

    if (start > end || end > length) {
        if(endName.isEmpty())
            endName = "end";
        throw RangeError(end, start, length, endName, message);
    }
    return end;
}
