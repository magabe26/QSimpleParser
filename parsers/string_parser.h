/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include "core/core.h"
#include <QString>

/**
 * @brief The StringParser class
 */
class StringParser: public Parser {
public:

    StringParser(QString string,bool caseSensitive = true);
    StringParser(const StringParser& other );

    virtual ~StringParser();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

private:
    QString string_;
    bool caseSensitive_;
    int failedAt_;

    // Delegate interface
    Result parseOn(Context context);
};

StringParser string(
        QString string,
        bool caseSensitive = true
        );


#endif // STRING_PARSER_H
