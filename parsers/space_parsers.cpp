/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "space_parsers.h"

static Parser _whitespaceChar = (chaR('\u0009') |
                                 chaR('\u000A') |
                                 chaR('\u000B') |
                                 chaR('\u000C') |
                                 chaR('\u000D') |
                                 chaR('\u0020') |
                                 chaR(85) |
                                 chaR(133) |
                                 chaR(160)) ;

Parser spaceOptional() { return _whitespaceChar .star();}

Parser space() {return _whitespaceChar.plus(); }
