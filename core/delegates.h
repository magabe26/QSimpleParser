/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef DELEGATES_H
#define DELEGATES_H

#include "context.h"
#include "result.h"
#include "utils.h"
#include "errors.h"
#include <QSharedPointer>

/**
 *--------------------------------------------
 * @brief The DelegateInterface class
 */
class DelegateInterface{
public:
    DelegateInterface(QString name = "");
    DelegateInterface (const DelegateInterface &other);

    virtual  ~DelegateInterface();

    bool operator ==(const DelegateInterface& other);
    bool operator !=(const DelegateInterface& other);

    DelegateInterface& operator =(const DelegateInterface &other);

    virtual Result firstMatch(QString input, int start = 0) = 0;
    virtual QString firstStringMatch(QString input, int start = 0) = 0;
    virtual Result lastMatch(QString input, int start = 0) = 0;
    virtual QString lastStringMatch(QString input, int start = 0) = 0;
    virtual QStringList allStringMatches(QString input, int start = 0) = 0;
    virtual QList<Success> allMatches(QString input, int start = 0) =0;
    virtual Result parse(QString input, int start = 0) = 0;
    virtual QSharedPointer<DelegateInterface> makeShared() = 0;
    static  void deleter(DelegateInterface* obj);
    virtual bool isNull();
    QString name() const;

protected:
    int i1_;
    int i2_;
    char c1_;
    char c2_;
    QString s1_;
    QString s2_;
private:
    QString name_;
    virtual Result parseOn(Context context) = 0;
};



/**
 *---------------------------------------
 * @brief The NullDelegate class
 */
class NullDelegate : public DelegateInterface{
    // DelegateInterface interface
public:
    NullDelegate(QString message = "NullDelegate");

    Result firstMatch(QString input, int start);
    QString firstStringMatch(QString input, int start);
    Result lastMatch(QString input, int start);
    QString lastStringMatch(QString input, int start);
    QStringList allStringMatches(QString input, int start);
    QList<Success> allMatches(QString input, int start);
    Result parse(QString input, int start);
    QSharedPointer<DelegateInterface> makeShared();

private:
   Result parseOn(Context context);
   QString message_;
};


static const QSharedPointer<DelegateInterface>  nullDelegate = NullDelegate().makeShared();


/**
  *-----------------------------------
 * @brief The Delegate class
 */

class Delegate : public DelegateInterface{

public:

    Delegate(QString name = "",QSharedPointer<DelegateInterface> d1 = nullDelegate,QSharedPointer<DelegateInterface> d2 = nullDelegate);
    virtual  ~Delegate(){}

    bool operator ==(const Delegate& other);
    bool operator !=(const Delegate& other);

    Delegate& operator =(const Delegate &other);

    Result firstMatch(QString input, int start = 0);
    QString firstStringMatch(QString input, int start = 0);
    Result lastMatch(QString input, int start = 0);
    QString lastStringMatch(QString input, int start = 0);
    QStringList allStringMatches(QString input, int start = 0);
    QList<Success> allMatches(QString input, int start = 0);
    Result parse(QString input, int start = 0);
    bool isNull();

protected:
    QSharedPointer<DelegateInterface> d1_; //do not use to test in operator == or !=
    QSharedPointer<DelegateInterface> d2_; //do not use to test in operator == or !=
    QSharedPointer<QList<QSharedPointer<Delegate>>> skippers_; //do not use to test in operator == or !=

    void copySkippers(const Delegate& from);

private:
    virtual Result parseOn(Context context) = 0;
    bool isSkipParser();
    int getQualifiedPosition(QString input, int start);
    static void skippersDeleter(QList<QSharedPointer<Delegate>> *skippers);
    Result parseImpl(QString input, int start);
};



/**
 *--------------------------------------
 * @brief The TestDelegate class
 */
class SuccessDelegate:public  Delegate{

    // Delegate interface
public:
    SuccessDelegate(int start,int end);
    // Delegate interface
    QSharedPointer<DelegateInterface> makeShared();

private:
    Result parseOn(Context context);
};
/**
 *--------------------------------------------------
 * @brief The SeqParserDelegate class
 */
class SeqParserDelegate: public Delegate{

public:
    SeqParserDelegate(QSharedPointer<DelegateInterface> first
                      , QSharedPointer<DelegateInterface> second);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

/**
 *--------------------------------------------------
 * @brief The OrParserDelegate class
 */
class OrParserDelegate: public Delegate{

public:
    OrParserDelegate(QSharedPointer<DelegateInterface> first
                     ,QSharedPointer<DelegateInterface> second);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

/**
 * ---------------------------------------------
 * @brief The StarParserDelegate class
 */
class StarParserDelegate: public Delegate{

public:
    StarParserDelegate(QSharedPointer<DelegateInterface> delegate);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

/**
 *-------------------------------------------------
 * @brief The PlusParserDelegate class
 */
class PlusParserDelegate: public Delegate{

public:
    PlusParserDelegate(QSharedPointer<DelegateInterface> delegate);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

/**
 *-------------------------------------
 * @brief The OptionalParserDelegate class
 */
class OptionalParserDelegate: public Delegate{

public:
    OptionalParserDelegate(QSharedPointer<DelegateInterface> delegate);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};

/**
 *--------------------------------------------------
 * @brief The RepeatParserDelegate class
 */
class RepeatParserDelegate: public Delegate{

public:
    RepeatParserDelegate(QSharedPointer<DelegateInterface> delegate,int min,int max);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};


/**
  *---------------------------------------------------
 * @brief The SkipParserDelegate class
 */
class SkipParserDelegate: public Delegate{

public:
    SkipParserDelegate(QSharedPointer<DelegateInterface> delegate);

    // DelegateInterface interface
    QSharedPointer<DelegateInterface> makeShared();

    // Delegate interface
private:
    Result parseOn(Context context);
};


#endif // DELEGATES_H
