/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#include "parser.h"
#include <QDebug>


static const char *skipParserDelegate = "SkipParserDelegate";
static const char *debugParser = "DebugParser";
static const char *wrapParser = "WrapParser";

static const char *skipParser = "SkipParser";
static const char *optionalParser = "OptionalParser";
static const char *starParser = "StarParser";
static const char *plusParser = "PlusParser";
static const char *repeatParser = "RepeatParser";

/**
 *--------------------------------------------------
 * @brief The Parser class
 */
Parser::Parser(QSharedPointer<DelegateInterface> delegate, QString name)
    :Delegate(name,delegate){}

Parser::Parser(QString name, QSharedPointer<DelegateInterface> d1, QSharedPointer<DelegateInterface> d2)
    :Delegate(name,d1,d2)

{
}

/**
 * @brief   Parser::Parser , A very important method that helps assigning example: Parser p = CharParser() works,
 *          it make it possible for the appropriate parserOn method to be called
 * @param other
 */
Parser::Parser(const Parser &other)
    :Delegate(other.name()){
    d1_ = (other.d1_->name() == nullDelegate->name()) ? const_cast<Parser&>(other).makeShared() : other.d1_;
}

bool Parser::operator ==(const Parser &other){
    return Delegate::operator==(other);
}

bool Parser::operator !=(const Parser &other){
    return Delegate::operator!=(other);
}

Delegate &Parser::operator =(const Delegate &other){
    Delegate::operator=(other);
    return *this;
}

Parser Parser::seq(const Parser &parser)
{
    auto newParser = Parser(SeqParserDelegate(makeShared(),const_cast<Parser&>(parser).makeShared()).makeShared(),"SeqParser");
    newParser.copySkippers(*this);
    return  newParser;
}

Parser Parser::operator &(const Parser &parser){
    return seq(parser);
}

Parser Parser::oR(const Parser &parser){
    auto newParser = Parser(OrParserDelegate(makeShared(),const_cast<Parser&>(parser).makeShared()).makeShared(),"OrParser");
    newParser.copySkippers(*this);
    return  newParser;

}

Parser Parser::operator |(const Parser &other){
    return oR(other);
}

Parser Parser::optional() {
    auto newParser = Parser(OptionalParserDelegate(makeShared()).makeShared(),optionalParser);
    newParser.copySkippers(*this);
    return  newParser;

}

Parser Parser::star(){
    auto newParser = Parser(StarParserDelegate(makeShared()).makeShared(),starParser);
    newParser.copySkippers(*this);
    return  newParser;

}

Parser Parser::plus(){
    auto newParser = Parser(PlusParserDelegate(makeShared()).makeShared(),plusParser);
    newParser.copySkippers(*this);
    return  newParser;

}

Parser Parser::repeat(int min, int max){
    auto newParser = Parser(RepeatParserDelegate(makeShared(),min,max).makeShared(),repeatParser);
    newParser.copySkippers(*this);
    return  newParser;
}

bool Delegate::isSkipParser() {
    return (name() == skipParser || (name() == skipParserDelegate));
}

Parser Parser::skip(){
    auto skipper = SkipParserDelegate(makeShared()).makeShared();
    auto newParser = Parser(skipper,skipParser);
    newParser.skippers_->append(QSharedPointer<Delegate>(new SkipParserDelegate(makeShared())));
    return newParser;
}

/**
 * @brief removeFrom ,removes success parser results from @param input
 * @param input
 * @param start
 * @param count , if set -1 ,it removes until end of @param input
 * @return
 */

QString Parser::removeFrom(QString input, int start, int count) {
    return replaceIn(input,"",start,count);
}

/**
 * @brief Parser::replaceIn
 * @param input
 * @param replacement
 * @param start
 * @param count , if set -1 ,it removes until end of @param input
 * @return
 */
QString Parser::replaceIn(QString input,QString replacement, int start, int count) {
    QString output = input;
    int offset = 0;
    if ((start >= 0) && (start < output.length())) {
        auto results = allMatches(output, start);
        if (results.isEmpty()) {
            return output;
        }
        int c = 0;
        for (auto result : results) {

            output =
                    output.replace((result.start() - offset), ((result.end() - offset) - (result.start() - offset)), replacement);
            c++;
            offset += (result.value().length() - replacement.length());
            if ((count != -1) && (count == c)) {
                break;
            }
        }
        return output;
    } else {
        return output;
    }
}

QString Parser::replaceInMapped(QString input, Replace replace, int start, int count) {
    QString output = input;
    int offset = 0;
    if ((start >= 0) && (start < output.length())) {
        auto results = allMatches(output, start);
        if (results.isEmpty()) {
            return output;
        }
        int c = 0;
        for (auto result : results) {
            QString replacement = replace(result.value());
            output =
                    output.replace((result.start() - offset), ((result.end() - offset) - (result.start() - offset)), replacement);
            c++;
            offset += (result.value().length() - replacement.length());
            if ((count != -1) && (count == c)) {
                break;
            }
        }
        return output;
    } else {
        return output;
    }
}

bool Parser::hasMatch(QString input, int start)
{
    return firstMatch(input,start).isSuccess();
}

bool Parser::isNull(){
    return Delegate::isNull();
}

Result Parser::parseOn(Context context){
    try {
        if((d1_.isNull()) && (nullDelegate->name() != name())){
            return Failure(context.position(),QString("Could not parse because either"
                                                      "\n 1: a '%1' instance was "
                                                      "returned from a method/function as a base class 'Parser' instance."
                                                      "\n 2: a 'Parser' variable was used to hold an instance of %2"
                                                      "\nTo fix this ,Change that return type or variable type from "
                                                      "'Parser' to '%3'").arg(name()).arg(name()).arg(name()));
        }else{
            return d1_->parse(context.buffer(),context.position());
        }
    } catch (Error e) {
        return Failure(context.position(),e.toString());
    }
}

QSharedPointer<DelegateInterface> Parser::makeShared(){
    return QSharedPointer<DelegateInterface>(new Parser(name(),d1_,d2_),&DelegateInterface::deleter);
}



/**
 *---------------------------
 * @brief The NullParser class
 */
NullParser::NullParser(){}


/**
  *--------------------------------------
 * @brief The DebugParser class
 */
DebugParser::DebugParser(): Parser(debugParser){}

Result DebugParser::parseOn(Context context){
    qDebug() << QString(">>> DebugParser:\n input = %1\n\nposition = %2 <<<")
                .arg(context.buffer()).arg(context.position());
    return Success(context.position(), context.position());

}

QSharedPointer<DelegateInterface> DebugParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new DebugParser(),&DelegateInterface::deleter);
}


DebugParser debug() {return DebugParser();}



/**
 *-----------------------------------
 * @brief The WrapParser class
 */
WrapParser::WrapParser(QSharedPointer<DelegateInterface> d):Parser(wrapParser,d){

}

QSharedPointer<DelegateInterface> WrapParser::makeShared(){
    return QSharedPointer<DelegateInterface>(new WrapParser(d1_),&DelegateInterface::deleter);
}

Result WrapParser::parseOn(Context context){
    try {
        return d1_->parse(context.buffer(),context.position());
    } catch (Error e) {
        return  Failure(context.position(),e.toString());
    }
}

WrapParser wrap(const Parser &another){
    return WrapParser(const_cast<Parser&>(another).makeShared());
}
