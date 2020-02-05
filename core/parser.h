/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "context.h"
#include "result.h"
#include "errors.h"
#include "utils.h"
#include "delegates.h"

#define PARSER_NAME(name) Parser(#name)

typedef QString Replace(QString match);

/**
 *--------------------------------------------------
 * @brief The Parser class
 */
class Parser: public Delegate{

public:
    Parser(QSharedPointer<DelegateInterface> delegate, QString name);
    Parser(QString name = "", QSharedPointer<DelegateInterface> d1 = nullDelegate, QSharedPointer<DelegateInterface> d2 = nullDelegate);
    Parser(const Parser &other);

    bool operator ==(const Parser& other);
    bool operator !=(const Parser& other);

    Delegate& operator =(const Delegate &other);

    Parser seq(const Parser &parser);
    Parser operator &(const Parser &parser);
    Parser oR(const Parser &parser);
    Parser operator |(const Parser &other);
    Parser optional();
    Parser star();
    Parser plus();
    Parser repeat(int min, int max = -1);
    Parser skip();
    QString removeFrom(QString input, int start = 0, int count = -1);
    QString replaceIn(QString input, QString replacement, int start = 0, int count = -1);
    QString replaceInMapped(QString input,Replace replace, int start = 0, int count = -1);
    bool hasMatch(QString input, int start = 0);
    bool isNull();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

private:
    // Delegate interface
    virtual Result parseOn(Context context);
};


/**
 *---------------------------
 * @brief The NullParser class
 */
class NullParser : public Parser{
public:
    NullParser();
};


/**
  *--------------------------------------
 * @brief The DebugParser class
 */
class DebugParser: public Parser {

public:
    DebugParser();

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

DebugParser debug();


/**
 *-----------------------------------
 * @brief The WrapParser class
 */
class WrapParser: public Parser{
public:
    WrapParser(QSharedPointer<DelegateInterface> d);

    QSharedPointer<DelegateInterface> makeShared() override;
private:
    Result parseOn(Context context) override;
};

WrapParser wrap(const Parser& another);


#endif // PARSER_H
