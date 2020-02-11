/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#include "tests.h"


void QSimpleParserTests::initTestCase()
{
    qDebug() << ">>>>>  TESTS\n\n";
}

void QSimpleParserTests::null_delegate_tests(){
    qDebug("nullDelegate->isNull() should return \"true\"");
    QCOMPARE(nullDelegate->isNull(), true);

    qDebug("All NullDelegate Objects  should be the same even if they point to defferent point in memory");
    auto tmp = NullDelegate();
    DelegateInterface *myDelegate = &tmp;
    auto areEquals = (*const_cast<DelegateInterface*>(nullDelegate.data()) == *myDelegate);
    QVERIFY(areEquals);
}

void QSimpleParserTests::null_parser_tests()
{
    qDebug("NullParser().isNull() should return \"true\"");
    QCOMPARE(NullParser().isNull(), true);

    qDebug("All NullParser Objects  should be the same even if they point to defferent point in memory");
    auto null1 = NullParser();
    auto null2 = NullParser();
    auto areEquals = (null1 == null2);
    QVERIFY(areEquals);
}

void QSimpleParserTests::seq_parser_tests()
{
    auto a = chaR('a');
    auto b = chaR('b');
    auto c = chaR('c');
    auto d = chaR('d');

    qDebug("a.seq(b).seq(c).parse(\"abc\").success().value() should return \"abc\"");
    QCOMPARE(a.seq(b).seq(c).parse("abc").success().value(), "abc");

    qDebug("a.seq(b).seq(c).seq(d).parse(\"abc\") should fail at the end of input");
    QCOMPARE(a.seq(b).seq(c).seq(d).parse("abc").failure().position(), 3);
}

void QSimpleParserTests::or_parser_tests()
{
    auto c = chaR('c');
    auto f = chaR('f');

    qDebug("c.oR(f).allStringMatches(\"abcdef\") should return QStringList({\"c\",\"f\"})");
    QCOMPARE(c.oR(f).allStringMatches("abcdef"), QStringList({"c","f"}));

    qDebug("c.oR(f).allStringMatches(\"abcde\") should return QStringList({\"c\"})");
    QCOMPARE(c.oR(f).allStringMatches("abcde"), QStringList({"c"}));

}

void QSimpleParserTests::optional_parser_tests()
{
    qDebug("chaR('g').parse(\"f\") should fail at position 0");
    QCOMPARE(chaR('g').parse("f").failure().position(), 0);

    qDebug("chaR('g').optional().parse(\"f\").success().start() should succed at position 0");
    QCOMPARE(chaR('g').optional().parse("f").success().start(), 0);

}

void QSimpleParserTests::char_parsers_tests()
{
    qDebug("chaR('c').parse(\"abc\") should fail at position 0");
    QCOMPARE(chaR('c').parse("abc").failure().position(), 0);

    qDebug("chaR('c').parse(\"abc\",2).success().value() should return \"c\"");
    QCOMPARE(chaR('c').parse("abc",2).success().value(), "c");

    qDebug("chaR('c').firstStringMatch(\"abc\") should return \"c\"");
    QCOMPARE(chaR('c').firstStringMatch("abc"), "c");

    qDebug("chaR('a').allStringMatches(\"i am awesome\") should return \"QStringList({\"a\",\"a\"})\"");
    QCOMPARE(chaR('a').allStringMatches("i am awesome"), QStringList({"a","a"}));

    qDebug("chaR('a').seq(chaR('b')).seq(chaR('c')).parse(\"abc\").success().value() should return \"abc\"");
    QCOMPARE(chaR('a').seq(chaR('b')).seq(chaR('c')).parse("abc").success().value(),"abc");

    qDebug("chaR('a').oR(chaR('b')).seq(chaR('c')).parse(\"abc\") should fail at position 1");
    QCOMPARE(chaR('a').oR(chaR('b')).seq(chaR('c')).parse("abc").failure().position(),1);

    qDebug("chaR('a').oR(chaR('b')).seq(chaR('c')).firstStringMatch(\"abc\",1) should return \"bc\"");
    QCOMPARE(chaR('a').oR(chaR('b')).seq(chaR('c')).firstStringMatch("abc",1),"bc");

    qDebug("chaR('a').oR(chaR('b')).seq(chaR('c').star()).parse(\"abc\").success().value() should return \"a\"");
    QCOMPARE(chaR('a').oR(chaR('b')).seq(chaR('c').star()).parse("abc").success().value(),"a");

    qDebug("firstChar().firstStringMatch(\"abc\") should return \"a\"");
    QCOMPARE(firstChar().firstStringMatch("abc"),"a");

    qDebug("lastChar().firstStringMatch(\"abc\") should return \"c\"");
    QCOMPARE(lastChar().firstStringMatch("abc"),"c");

    qDebug("chaR('a').skip().seq(remainingChars()).firstStringMatch(\"abc\") should return \"bc\"");
    QCOMPARE(chaR('a').skip().seq(remainingChars()).firstStringMatch("abc"),"bc");

}

void QSimpleParserTests::any_character_parser_tests()
{
    qDebug("any(chaR('!')).firstStringMatch(\"Hellow!\") should return \"H\"");
    QCOMPARE(any(chaR('!')).firstStringMatch("Hellow!"),"H");


    qDebug("any(chaR('!')).star().firstStringMatch(\"Hellow!\") should return \"Hellow\"");
    QCOMPARE(any(chaR('!')).star().firstStringMatch("Hellow!"),"Hellow");

    qDebug("any(chaR('!'),\"o\").star().firstStringMatch(\"Hellow!\") should return \"\"");
    QCOMPARE(any(chaR('!'),"o").star().firstStringMatch("Hellow!"),"Hell");

    qDebug("any(chaR('!')).star().firstStringMatch(\"Hellow!\",3),\"low\") should return \"low\"");
    QCOMPARE(any(chaR('!')).star().firstStringMatch("Hellow!",3),"low");

    qDebug("any(space()).seq(remainingChars()).star().firstStringMatch(\"I am Awesome!\") should return \"I am Awesome!\"");
    QCOMPARE(any(space()).seq(remainingChars()).star().firstStringMatch("I am Awesome!"),"I am Awesome!");

    qDebug("any(chaR('A')).skip().seq(remainingChars()).firstStringMatch(\"I am Awesome!\") should return \" am Awesome!\" because skip fails at postion 0");
    QCOMPARE(any(chaR('A')).skip().seq(remainingChars()).firstStringMatch("I am Awesome!")," am Awesome!");

}

void QSimpleParserTests::all_input_parser_tests()
{
    qDebug("allInput().parse(\"I am Awesome!\") should return the whole input");
    QCOMPARE(allInput().parse("I am Awesome!").success().value(),"I am Awesome!");

}

void QSimpleParserTests::pattern_parser_tests()
{
    qDebug("pattern(\"A-Z\").allStringMatches(\"AbC\") should return \"AC\"");
    QCOMPARE(pattern("A-Z").allStringMatches("AbC"),QStringList({"A","C"}));

    qDebug("digit().firstMatch(\"A1C\") should return \"1\"");
    QCOMPARE(digit().firstStringMatch("A1C"),"1");

    qDebug("letter().firstMatch(\"A1C\") should return \"A\"");
    QCOMPARE(letter().firstStringMatch("A1C"),"A");

    qDebug("word().plus().firstStringMatch(\"A1C\") should return \"A1C\"");
    QCOMPARE(word().plus().firstStringMatch("A1C"),"A1C");
}

void QSimpleParserTests::space_parser_tests()
{
    qDebug("space().parse("") should fail");
    QCOMPARE(space().parse("").failure().position(),0);

    qDebug("spaceOptional().parse("") should successed");
    QCOMPARE(spaceOptional().parse("").success().start(),0);
}

void QSimpleParserTests::string_parser_tests()
{
    qDebug("string(\"chura\").plus().allStringMatches(\"chura CHURA\") should \"QStringList({\"chura\"})\"");
    QCOMPARE(string("chura").plus().allStringMatches("chura CHURA"),QStringList({"chura"}));

    qDebug("string(\"chura\",false).plus().allStringMatches(\"chura CHURA\") should \"QStringList({\"chura\",\"CHURA\"})\"");
    QCOMPARE(string("chura",false).plus().allStringMatches("chura CHURA"),QStringList({"chura","CHURA"}));

}

void QSimpleParserTests::text_replacement_test()
{
    qDebug("When orginal and replacement have equal length, A call to chaR('a').replaceIn(\"ab a\", \"-\"), return '-b -'");
    QCOMPARE(chaR('a').replaceIn("ab a", "-"), "-b -");


    qDebug("When replacement has greater length, A call to chaR('a').replaceIn(\"ab a\", \"--\") return '--b --'");
    QCOMPARE(chaR('a').replaceIn("ab a", "--"), "--b --");

    qDebug("When replacement has smaller length, A call to chaR('a').replaceIn(\"ab a\", "") return 'b '");
    QCOMPARE(chaR('a').replaceIn("ab a", ""), "b ");
}



void QSimpleParserTests::cleanupTestCase()
{
    qDebug() << "\n\n   <<<<<";
}
