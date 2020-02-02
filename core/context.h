/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef CONTEXT_H
#define CONTEXT_H

#include <QString>

/**
 * @brief The Context class
 */
class Context
{
public:
    Context(QString buffer,int position);
    Context(const Context &other);

    Context &operator=(const Context &other);

    bool operator ==(Context other);
    bool operator !=(Context other);

    int position() const;
    QString buffer() const;

private:
    QString buffer_;
    int position_;
};

#endif // CONTEXT_H
