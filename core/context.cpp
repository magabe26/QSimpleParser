/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "context.h"

Context::Context(QString buffer, int position){
    buffer_ = buffer;
    position_ = position;
}

Context::Context(const Context &other){
    buffer_ = other.buffer_;
    position_ = other.position_;
}

Context &Context::operator=(const Context &other){
    buffer_ = other.buffer_;
    position_ = other.position_;
    return *this;
}

bool Context::operator ==(Context other) {
    return ((buffer_ == other.buffer_) &&
            (position_ == other.position_));
}

bool Context::operator !=(Context other) {
    return ((buffer_ != other.buffer_) ||
            (position_ != other.position_));
}

int Context::position() const
{
    return position_;
}

QString Context::buffer() const
{
    return buffer_;
}
