/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */

#include "all_input_parser.h"

Parser allInput() {return firstChar().seq(any(lastChar()).star().seq(lastChar())); }

