/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#include "result.h"

/**
 *  ---------------------------------------------------
 * @brief The Success class
 */

Success::Success(int start, int end){
    start_ = start;
    end_ = end;
}

Success::Success(const Success &other){
    start_ = other.start_;
    end_ = other.end_;
    value_ = other.value_;
}

Success &Success::operator=(const Success &other){
    start_ = other.start_;
    end_ = other.end_;
    value_ = other.value_;
    return *this;
}

bool Success::operator ==(Success other) {
    return  ((start_ == other.start_) &&
             (end_ == other.end_) &&
             (value_ == other.value_));
}

bool Success::operator !=(Success other) {
    return  ((start_ != other.start_) ||
             (end_ != other.end_) ||
             (value_ != other.value_));
}

int Success::start() const
{
    return start_;
}

int Success::end() const
{
    return end_;
}

QString Success::value() const
{
    return value_;
}

Success Success::setValue(const QString &value)
{
    if(value_.isEmpty() || value_.isNull()){
        value_ = value;
    }
    return  *this;
}

QString Success::toString() {
    return QString(">>> Success:  %1 (start: %2 - end: %3) <<<")
            .arg(value_).arg(start_).arg(end_);
}



/**
 *  ---------------------------------------------------
 * @brief The Failure class
 */
Failure::Failure(int position, QString message) {
    position_ = position;
    message_ = message;
}

Failure::Failure(const Failure &other){
    position_ = other.position_;
    message_ = other.message_;
}



Failure &Failure::operator=(const Failure &other){
    position_ = other.position_;
    message_ = other.message_;
    return *this;
}

bool Failure::operator ==(Failure other) {
    return  ((position_ == other.position_) &&
             (message_ == other.message_));
}

bool Failure::operator !=(Failure other) {
    return  ((position_ != other.position_) ||
             (message_ != other.message_));
}

int Failure::position() const
{
    return position_;
}

QString Failure::message() const
{
    return message_;
}

QString Failure::toString() {
    return QString(">>> Failure:  (position: %1)\n%2 <<<\n")
            .arg(position_).arg(message_);
}

/**
 *  ---------------------------------------------------
 * @brief The Result class
 */

Result::Result(const Result &other)
    :success_ {other.success_}
    ,failure_{other.failure_}
{
    isSuccess_ = other.isSuccess_;
    isFailure_ = other.isFailure_;
}



Result::Result(const Success &success)
    :success_{success}
    ,failure_{Failure(-1)}{
    isSuccess_ = true;
    isFailure_ = false;
}

Result::Result(const Failure &failure)
    :success_{Success(-1,-1)}
    ,failure_{failure}{
    isSuccess_ = false;
    isFailure_ = true;
}

bool Result::isSuccess() const{
    return  isSuccess_;
}

bool Result::isFailure() const{
    return  isFailure_;
}

Success Result::success() const
{
    Q_ASSERT(isSuccess_);
    return success_;
}

Failure Result::failure() const
{
    Q_ASSERT(isFailure_);
    return failure_;
}

QDebug operator <<(QDebug debug, const Success &success){
    debug.noquote();debug.space() << const_cast<Success&>(success).toString();
    return debug.quote();
}

QDebug operator <<(QDebug debug, const Failure &failure){
    debug.noquote();debug.space() << const_cast<Failure&>(failure).toString();
    return debug.quote();
}

QDebug operator <<(QDebug debug, const Result &result){
    debug.noquote();debug.space() << (result.isFailure()? result.failure().toString() : result.success().toString());
    return debug.quote();
}
