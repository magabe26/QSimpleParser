/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#include "space_parsers.h"


Parser spaceOptional() { return chaR('\u0020').star();}

Parser space() {return chaR('\u0020').plus(); }
