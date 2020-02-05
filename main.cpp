/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#include <QString>
#include <QDebug>
#include "tests.h"
#include <QtTest>
#include "q_simple_parser.h"

void run_tests();
void run_example();

int main()
{
    //tests
    run_tests();

    //example
    run_example();


    return  0;
}


void run_tests(){
    QSimpleParserTests test1;
    QTest::qExec(&test1);

}

void run_example(){
    qDebug() << ">>>>> EXAMPLE\n\n";

    QString str = ""
                  "<tag attr1=\"attribute1\"> Text </tag>"
                  "<TAG> TEXT </TAG>"
                  "<i></i>"
                  "<b/>"
                  "<v href=\"qwety\"/>"
                  "";

    Parser anyElement = (spaceOptional().seq(spaceOptional().seq(chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>'))).seq(spaceOptional()) & (spaceOptional().seq(spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>')))
                                                                                                                                                                      .seq(spaceOptional()).seq((spaceOptional().seq(spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>')))
                                                                                                                                                                                                                     .seq(spaceOptional()).seq(any(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>')))
                                                                                                                                                                                                                                                   .seq(spaceOptional()),"<>").plus()).seq(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>')))
                                                                                                                                                                                                                                                                                           .seq(spaceOptional()))).seq(spaceOptional()) | spaceOptional().seq(spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>'))).seq(spaceOptional()).seq(spaceOptional()).seq(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>')))
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          .seq(spaceOptional()))).seq(spaceOptional()) | spaceOptional().seq(chaR('<').seq(any(chaR('/').seq(chaR('>')),"<>").plus()).seq(chaR('/').seq(chaR('>'))))
                                                                                                                                                                                                 .seq(spaceOptional())).plus()).seq(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>'))).seq(spaceOptional()))).seq(spaceOptional())  | spaceOptional().seq(spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>')))
                                                                                                                                                                                                                                                                                                                                                                                                                                 .seq(spaceOptional()).seq(any(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>'))).seq(spaceOptional()),"<>").plus()).seq(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>'))).seq(spaceOptional())))
                                                                                                                                                  .seq(spaceOptional()) | spaceOptional().seq(spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>'))).seq(spaceOptional()).seq(spaceOptional()).seq(spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>'))).seq(spaceOptional())))
                                                                                                                                                  .seq(spaceOptional()) | spaceOptional().seq(chaR('<').seq(any(chaR('/').seq(chaR('>')),"<>").plus()).seq(chaR('/').seq(chaR('>')))).seq(spaceOptional()) | spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>'))).seq(spaceOptional()) | word().plus() | chaR('<').seq(chaR('!')).seq(chaR('-')).seq(chaR('-'))
                                                                                                                                                  .seq(any(chaR('-').seq(chaR('-')).seq(chaR('>'))).star()).seq(chaR('-').seq(chaR('-')).seq(chaR('>'))))
                                             .star() & spaceOptional().seq(chaR('<').seq(chaR('/')).seq(spaceOptional()).seq(word().plus()).seq(spaceOptional()).seq(chaR('>')))
                                             .seq(spaceOptional())).seq(spaceOptional())).oR(spaceOptional().seq(chaR('<').seq(any(chaR('/').seq(chaR('>')),"<>").plus()).seq(chaR('/').seq(chaR('>'))))
                                                                                             .seq(spaceOptional()) | spaceOptional().seq (chaR('<').seq(any(chaR('>'),"/").star()).seq(chaR('>'))).seq(spaceOptional()) | chaR('<').seq(chaR('!')).seq(chaR('-')).seq(chaR('-')).seq(any(chaR('-').seq(chaR('-')).seq(chaR('>'))).star()).seq(chaR('-').seq(chaR('-')).seq(chaR('>'))));


    qDebug() << anyElement.allStringMatches(str);  //prints ("<tag attr1=\"attribute1\"> Text </tag>", "<TAG> TEXT </TAG>", "<i></i>", "<b/>", "<v href=\"qwety\"/>")




    qDebug() << chaR('b').replaceInMapped("abc",[](QString match){
                return  match == "b"  ? "B" : match;
        }); //aBc



    qDebug() << "\n\n <<<<<";
}


