/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef ERRORS_H
#define ERRORS_H

#include <QString>

/**
 *--------------------------------------------------
 * @brief The Error class
 */
class Error
{

public:
    Error(QString message);
    Error(const Error& other);
    virtual ~Error();
    virtual QString toString();

protected:
    QString message_;
};



/**
 *--------------------------------------------------
 * @brief The RangeError class
 */
class RangeError : public Error{
public:


    RangeError(int invalidValue, int minValue, int maxValue,
               QString name = QString(""), QString message= QString(""));

    /** The minimum value that [value] is allowed to assume. */
    int start() const;

    /** The maximum value that [value] is allowed to assume. */
    int end() const;

    /** Message describing the problem. */
    QString message() const;

    QString toString();
    static int checkValidRange(int start, int end, int length,
                               QString startName = QString(""),
                               QString endName = QString(""), QString message= QString(""));
private:
    int start_;
    int end_;
    /** The invalid value. */
    int invalidValue_;
    /** Name of the invalid argument, if available. */
    QString name_;
};

#endif // ERRORS_H
