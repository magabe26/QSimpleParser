/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef RESULT_H
#define RESULT_H

#include <QString>
#include <QDebug>

/**
 *  ---------------------------------------------------
 * @brief The Success class
 */
class Success{

public:
    Success(int start, int end);
    Success(const Success &other);

    Success &operator=(const Success &other);

    bool operator ==(Success other);
    bool operator !=(Success other);

    int start() const;
    int end() const;

    QString value() const;
    Success  setValue(const QString &value);

    QString toString();
private:
    int start_;
    int end_;
    QString value_;

};

/**
 *  ---------------------------------------------------
 * @brief The Failure class
 */
class Failure{

    // Result interface
public:
    Failure(int position, QString message = QString());
    Failure(const Failure &other);

    Failure &operator=(const Failure &other);

    bool operator ==(Failure other);
    bool operator !=(Failure other);

    int position() const;

    QString message() const;

    QString toString();

private:
    int position_;
    QString message_;
};
/**
 *  ---------------------------------------------------
 * @brief The Result class
 */
class Result
{
public:
    Result(const Result &other);

    Result(const Success &success);
    Result(const Failure &failure);


    bool isSuccess() const;
    bool isFailure() const;

    Success success() const;
    Failure failure() const;

private:
    Success success_;
    Failure failure_;
    bool isSuccess_;
    bool isFailure_;
};

QDebug operator <<(QDebug debug, const Success& success);

QDebug operator <<(QDebug debug, const Failure& failure);

QDebug operator <<(QDebug debug, const Result& result);

#endif // RESULT_H
