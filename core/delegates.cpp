/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#include "delegates.h"

static const char *nullDelegateName = "NullDelegate";
static const char *skipParserDelegate = "SkipParserDelegate";
static const char *successDelegate = "SuccessDelegate";
static const char *seqParserDelegate = "SeqParserDelegate";
static const char *orParserDelegate = "OrParserDelegate";
static const char *starParserDelegate = "StarParserDelegate";
static const char *plusParserDelegate = "PlusParserDelegate";
static const char *optionalParserDelegate = "OptionalParserDelegate";
static const char *repeatParserDelegate = "RepeatParserDelegate";

static const char *skipParser = "SkipParser";

/**
 * @brief DelegateInterface::name
 * @return
 */
DelegateInterface::DelegateInterface(QString name)
    :i1_{-1}
    ,i2_{-1}
    ,c1_{' '}
    ,c2_{' '}
    ,s1_{QString()}
    ,s2_{QString()}
    ,name_{name}
{}

DelegateInterface::DelegateInterface(const DelegateInterface &other)
{
    name_ = other.name_;
    i1_ = other.i1_;
    i2_ = other.i2_;
    c1_ = other.c1_;
    c2_ = other.c2_;
    s1_ = other.s1_;
    s2_ = other.s2_;

}

DelegateInterface::~DelegateInterface() {}

bool DelegateInterface::operator ==(const DelegateInterface &other)
{
    return (this == &other) || ((name_ == other.name_) &&
                                (i1_ == other.i1_) &&
                                (i2_ == other.i2_) &&
                                (c1_ == other.c1_) &&
                                (c2_ == other.c2_) &&
                                (s1_ == other.s1_) &&
                                (s2_ == other.s2_));
}

bool DelegateInterface::operator !=(const DelegateInterface &other)
{
    return ((name_ != other.name_) ||
            (i1_ != other.i1_) ||
            (i2_ != other.i2_) ||
            (c1_ != other.c1_) ||
            (c2_ != other.c2_) ||
            (s1_ != other.s1_) ||
            (s2_ != other.s2_));
}

DelegateInterface &DelegateInterface::operator =(const DelegateInterface &other)
{
    name_ = other.name_;
    i1_ = other.i1_;
    i2_ = other.i2_;
    c1_ = other.c1_;
    c2_ = other.c2_;
    s1_ = other.s1_;
    s2_ = other.s2_;
    return *this;
}

void DelegateInterface::deleter(DelegateInterface *obj){
    if(obj != nullptr){
        //QString name = obj->name_;
        //long long addr= reinterpret_cast<long long>(obj);

        delete obj;
        obj = nullptr;
        // qDebug() << QString("DelegateInterface::deleter : %1::%2 deleted").arg(name).arg(addr);
    }
}

bool DelegateInterface::isNull(){
    return ((i1_ == -1) &&
            (i2_ == -1) &&
            (c1_ == ' ') &&
            (c2_ == ' ') &&
            (s1_.isNull() || s1_.isEmpty()) &&
            (s2_.isNull() || s2_.isEmpty()));
}

QString DelegateInterface::name() const {return name_;}




/**
*---------------------------------------
* @brief The NullDelegate class
*/

NullDelegate::NullDelegate(QString message)
    :DelegateInterface(nullDelegateName/*to pass the null delegate test*/)
    ,message_{message}{}

Result NullDelegate::firstMatch(QString input, int start){
    Q_UNUSED(input)
    return  Failure(start,message_);
}

QString NullDelegate::firstStringMatch(QString input, int start){
    Q_UNUSED(input)
    Q_UNUSED(start)
    return "";
}

Result NullDelegate::lastMatch(QString input, int start){
    Q_UNUSED(input)
    return  Failure(start,message_);
}

QString NullDelegate::lastStringMatch(QString input, int start){
    Q_UNUSED(input)
    Q_UNUSED(start)
    return "";
}

QStringList NullDelegate::allStringMatches(QString input, int start){
    Q_UNUSED(input)
    Q_UNUSED(start)
    return QStringList();
}

QList<Success> NullDelegate::allMatches(QString input, int start){
    Q_UNUSED(input)
    Q_UNUSED(start)
    return QList<Success>();
}

Result NullDelegate::parse(QString input, int start){
    Q_UNUSED(input)
    return  Failure(start,message_);
}

QSharedPointer<DelegateInterface> NullDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new NullDelegate(),&DelegateInterface::deleter);
}

Result NullDelegate::parseOn(Context context){
    Q_UNUSED(context)
    return  Failure(context.position(),message_);
}


/**
  *-----------------------------------------
 * @brief The Delegate class
 */

Delegate::Delegate(QString name,QSharedPointer<DelegateInterface> d1,QSharedPointer<DelegateInterface> d2)
    :DelegateInterface(name)
    ,d1_ {d1}
    ,d2_ {d2}
    ,skippers_(QSharedPointer<QList<QSharedPointer<Delegate>>>(new QList<QSharedPointer<Delegate>>(),&Delegate::skippersDeleter)){}

bool Delegate::operator ==(const Delegate &other){
    return (DelegateInterface::operator==(other) &&
            (skippers_->length() == other.skippers_->length()));
}

bool Delegate::operator !=(const Delegate &other){
    return (DelegateInterface::operator!=(other)||
            (skippers_->length() != other.skippers_->length()));
}

Delegate& Delegate::Delegate::operator =(const Delegate &other){
    DelegateInterface::operator=(other);
    d1_ = other.d1_;
    d2_ = other.d2_;
    return *this;
}

Result Delegate::firstMatch(QString input, int start) {
    int position =  getQualifiedPosition(input,start);

    QString message;
    while ((position >= 0) && (position < input.length())) {
        Result result = parseImpl(input, position);
        if (result.isSuccess()) {
            return result;
        } else {
            message = result.failure().message();
            position++;
        }
    }
    return Failure(position, message);
}

QString Delegate::firstStringMatch(QString input, int start) {
    const Result result = firstMatch(input, start);
    if (result.isSuccess()) {
        return result.success().value();
    } else {
        return QString();
    }
}

Result Delegate::lastMatch(QString input, int start) {
    auto matches = allMatches(input, start);
    return (!matches.isEmpty()) ? Result(matches.last())  : Failure(start);
}

QString Delegate::lastStringMatch(QString input, int start) {
    Result match = lastMatch(input, start);
    if (match.isSuccess()) {
        return match.success().value();
    } else {
        return QString();
    }
}

QStringList Delegate::allStringMatches(QString input, int start) {
    auto list = QStringList();
    const auto matches = allMatches(input, start);
    for(auto match : matches){
        list.append(match.value());
    }
    return  list;
}

QList<Success> Delegate::allMatches(QString input, int start) {
    auto list = QList<Success>();
    int position =  getQualifiedPosition(input,start);

    while ((position >= 0) && (position < input.length())) {
        Result result = parseImpl(input, position);
        if (result.isSuccess()) {
            const QString value = result.success().value();
            Success success = result.success();
            if (!value.isEmpty()) {
                list.append(success);
            }
            if (position == success.end()) {
                position++;
            } else {
                position = success.end();
            }
        } else {
            position++;
        }
    }
    return list;
}

Result Delegate::parse(QString input, int start) {
    return parseImpl(input,getQualifiedPosition(input,start));
}

Result Delegate::parseImpl(QString input, int start) {
    int position =  start;
    RangeError::checkValidRange(position, input.length(), input.length());
    Result result = parseOn(Context(input, position));
    if (result.isSuccess()) {
        Success success = result.success();
        const int start = success.start();
        const int end = success.end();
        RangeError::checkValidRange(start, end, input.length());
        return success.setValue(_::getSubstring(input,start,end));
    } else {
        return result;
    }
}

bool Delegate::isNull()
{
    return (DelegateInterface::isNull()||
            (d1_.isNull() || (dynamic_cast<NullDelegate*>(d1_.data()) != nullptr)) ||
            (d2_.isNull() || (dynamic_cast<NullDelegate*>(d2_.data()) != nullptr)) );

}

void Delegate::copySkippers(const Delegate &from)
{
    skippers_ = from.skippers_;
}

int Delegate::getQualifiedPosition(QString input, int start){
    if(!skippers_->isEmpty()){
        int index = 0;
        for(auto skipper : *skippers_.data()){
            if(skipper->isSkipParser()){
                try {
                    Result result =  skipper->parse(input,start);
                    if(result.isSuccess()){
                        if(result.success().end() > start){
                            start = result.success().end();

                        }
                    }
                } catch (...) {}
            }
            skippers_->removeAt(index);
            index++;
        }
    }

    return start;
}

void Delegate::skippersDeleter(QList<QSharedPointer<Delegate> > *skippers){
    if(skippers != nullptr){
        //long long addr = reinterpret_cast<long long>(skippers);
        skippers->clear();
        delete skippers;
        skippers = nullptr;
        // qDebug() << QString("skippers list #%1 deleted").arg(addr);
    }
}

/**
*--------------------------------------
* @brief The TestDelegate class
*/
SuccessDelegate::SuccessDelegate(int start, int end)
    :Delegate(successDelegate){
    i1_ = start;
    i2_ = end;
}

Result SuccessDelegate::parseOn(Context context){
    Q_UNUSED(context)
    return  Success(i1_,i2_);
}

QSharedPointer<DelegateInterface> SuccessDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new SuccessDelegate(i1_,i2_),&DelegateInterface::deleter);
}


/**
*--------------------------------------------------
* @brief The SeqParserDelegate class
*/
SeqParserDelegate::SeqParserDelegate(QSharedPointer<DelegateInterface> first, QSharedPointer<DelegateInterface> second)
    :Delegate(seqParserDelegate,first,second){}

Result SeqParserDelegate::parseOn(Context context){
    const QString buffer = context.buffer();
    const int start = context.position();
    int position = context.position();

    if(d1_->name() == skipParser){
        try {
            return d2_->parse(buffer, position);
        } catch (Error e) {
            return Failure(position,e.toString());
        }
    }

    try {
        Result result = d1_->parse(buffer, position);
        if (result.isSuccess()) {
            position = result.success().end();
            try {
                result = d2_->parse(buffer, position);
                if (result.isSuccess()) {
                    position = result.success().end();

                } else {
                    return result;
                }
            } catch (Error e) {
                return Failure(position,e.toString());
            }
        } else {
            return result;
        }
    } catch (Error e) {
        return Failure(position,e.toString());
    }

    return Success(start, position).setValue(_::getSubstring(buffer,start,position));

}

QSharedPointer<DelegateInterface> SeqParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new SeqParserDelegate(d1_, d2_),&DelegateInterface::deleter);
}



/**
*--------------------------------------------------
* @brief The OrParserDelegate class
*/
OrParserDelegate::OrParserDelegate(QSharedPointer<DelegateInterface> first, QSharedPointer<DelegateInterface> second)
    :Delegate(orParserDelegate,first,second){}

Result OrParserDelegate::parseOn(Context context){

    try {
        Result result = d1_->parse(context.buffer(), context.position());
        if (result.isFailure()) {
            try {
                result = d2_->parse(context.buffer(), context.position());
            } catch (Error e) {
                result = Failure(context.position(), e.toString());
            }
        }
        return result;
    } catch (Error e) {
        try {
            return d2_->parse(context.buffer(), context.position());
        } catch (Error e) {
            return Failure(context.position(), e.toString());
        }
    }
}

QSharedPointer<DelegateInterface> OrParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new OrParserDelegate(d1_,d2_),&DelegateInterface::deleter);
}


/**
* ---------------------------------------------
* @brief The StarParserDelegate class
*/
StarParserDelegate::StarParserDelegate(QSharedPointer<DelegateInterface> delegate)
    :Delegate(starParserDelegate,delegate){}

Result StarParserDelegate::parseOn(Context context){
    const int start = context.position();
    int end = context.position();
    try {
        Result result = d1_->parse(context.buffer(), end);
        while (result.isSuccess()) {
            end = result.success().end();
            try {
                result = d1_->parse(context.buffer(), end);
            } catch (Error e) {
                break;
            }
        }
        return Success(start, end);
    } catch (Error e) {
        return Success(start, end);
    }
}

QSharedPointer<DelegateInterface> StarParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new StarParserDelegate(d1_),&DelegateInterface::deleter);
}


/**
*-------------------------------------------------
* @brief The PlusParserDelegate class
*/
PlusParserDelegate::PlusParserDelegate(QSharedPointer<DelegateInterface> delegate)
    :Delegate(plusParserDelegate,delegate){}

Result PlusParserDelegate::parseOn(Context context){
    const int start = context.position();
    int end = context.position();
    bool success = false;

    try {
        Result result = d1_->parse(context.buffer(), end);
        QString message("");
        while (result.isSuccess()) {
            end = result.success().end();
            if (!success) {
                success = true;
            }
            try {
                result = d1_->parse(context.buffer(), end);
            } catch (Error e) {
                end = result.failure().position();
                message = e.toString();
                break;
            }
        }
        if (success) {
            return Success(start, end);
        } else {
            return Failure(end,message);
        }
    } catch (Error e) {
        return Failure(context.position(),e.toString());
    }
}

QSharedPointer<DelegateInterface> PlusParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new PlusParserDelegate(d1_),&DelegateInterface::deleter);
}


/**
*-------------------------------------
* @brief The OptionalParserDelegate class
*/
OptionalParserDelegate::OptionalParserDelegate(QSharedPointer<DelegateInterface> delegate)
    :Delegate(optionalParserDelegate,delegate){}

Result OptionalParserDelegate::parseOn(Context context){
    const int start = context.position();
    int end = context.position();
    try {
        Result result = d1_->parse(context.buffer(), end);
        if (result.isSuccess()) {
            return Success(start, result.success().end());
        } else {
            return Success(start, end);
        }
    } catch (Error e) {
        return Success(start, end);
    }
}

QSharedPointer<DelegateInterface> OptionalParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new OptionalParserDelegate(d1_),&DelegateInterface::deleter);
}


/**
*--------------------------------------------------
* @brief The RepeatParserDelegate class
*/
RepeatParserDelegate::RepeatParserDelegate(QSharedPointer<DelegateInterface> delegate, int min, int max)
    :Delegate(repeatParserDelegate,delegate){
    i1_ = min;
    i2_ = max;
}

Result RepeatParserDelegate::parseOn(Context context){
    const int min = i1_;
    const int max = i2_;

    const QString buffer = context.buffer();
    const int start = context.position();
    int end = context.position();
    bool firstLoopEndedWithFailure = false;
    bool success = false;
    QString message("");

    for (int i = 0; i < min; i++) {
        try {
            const Result result = d1_->parse(buffer, end);
            if (result.isSuccess()) {
                end = result.success().end();
                if (!success) {
                    success = true;
                }
            } else {
                message = result.failure().message();
                firstLoopEndedWithFailure = true;
                break;
            }
        } catch (Error e) {
            message = e.toString();
            firstLoopEndedWithFailure = true;
            break;
        }
    }

    if (firstLoopEndedWithFailure || (!success)) {
        return Failure(start,message);
    } else {
        if ((max == -1) || (max <= min)) {
            return Success(start, end);
        } else {
            for (int i = 0; i < (max - min); i++) {
                try {
                    const Result result = d1_->parse(buffer, end);
                    if (result.isSuccess()) {
                        end = result.success().end();
                    }
                } catch (Error e) {
                    break;
                }
            }
            return Success(start, end);
        }
    }
}

QSharedPointer<DelegateInterface> RepeatParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new RepeatParserDelegate(d1_,i1_,i2_),&DelegateInterface::deleter);
}

/**
 *---------------------------------------------------
* @brief The SkipParserDelegate class
*/
SkipParserDelegate::SkipParserDelegate(QSharedPointer<DelegateInterface> delegate)
    :Delegate(skipParserDelegate,delegate){}

Result SkipParserDelegate::parseOn(Context context){
    const QString buffer = context.buffer();
    const int position = context.position();
    try {
        const Result result = d1_->parse(buffer, position);
        if (result.isSuccess()) {
            auto success = result.success();
            return Success(success.end(), success.end());
        } else {
            return Success(position, position);
        }
    } catch (Error e) {
        return Success(position, position);
    }
}

QSharedPointer<DelegateInterface> SkipParserDelegate::makeShared(){
    return QSharedPointer<DelegateInterface>(new SkipParserDelegate(d1_),&DelegateInterface::deleter);
}
