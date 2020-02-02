/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef TESTS_H
#define TESTS_H

#include "q_simple_parser.h"
#include <QtTest/QtTest>
#include <QObject>

/**
 * @brief The QSimpleParserTests class
 */
class QSimpleParserTests: public QObject
{
    Q_OBJECT

private:


private slots:
    void initTestCase();
    void null_delegate_tests();
    void null_parser_tests();
    void seq_parser_tests();
    void or_parser_tests();
    void optional_parser_tests();
    void char_parsers_tests();
    void any_character_parser_tests();
    void all_input_parser_tests();
    void pattern_parser_tests();
    void space_parser_tests();
    void string_parser_tests();

    void cleanupTestCase();
};

#endif // TESTS_H
