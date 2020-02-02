/**
 * Copyright 2020 - MagabeLab (Tanzania). All Rights Reserved.
 * Author Edwin Magabe    edyma50@yahoo.com
 */


#ifndef UTIL_H
#define UTIL_H

#include "QString"

struct _{
    static  QString getSubstring(QString input,int start,int end = -1){
        return  input.mid(start,(end != -1) ? end - start : input.length() - start);
    }
};



#endif // UTIL_H
