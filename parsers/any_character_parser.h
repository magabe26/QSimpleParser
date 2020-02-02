/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef ANY_CHARACTER_PARSER_H
#define ANY_CHARACTER_PARSER_H
#include "core/core.h"
#include <QString>

/**
 *------------------------------------------
 * @brief The AnyCharacterParser class
 */
class AnyCharacterParser: public Parser {
public:
    AnyCharacterParser(QSharedPointer<DelegateInterface> end,QString except);
    AnyCharacterParser(const AnyCharacterParser& other);
    virtual ~AnyCharacterParser();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};


AnyCharacterParser any(const Parser& end,QString except = QString());

#endif // ANY_CHARACTER_PARSER_H
