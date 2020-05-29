#pragma once
#include <stdlib.h>
#include <stdio.h>

char* fget_string(FILE* file_books_csv) {
    char* s = (char*) calloc(1024, sizeof(char));
    int pos = 0;
    for(char c = getc(file_books_csv); c != '\n' && c != EOF; c = getc(file_books_csv)) {
        s[pos++] = c;
    }
    s[pos++] = '\0';
    return s;
}

char* parse_csv(char* s) {
    char* t = (char *) calloc(255, sizeof(char));
    if (s[0] == '"') { // Р•СЃР»Рё Сѓ РЅР°СЃ РІ РєР°РІС‹С‡РєР°С… РІСЃРµ
        if(strstr(s, ",")==NULL) {
            strncpy(t,s+1, strstr(s+1, "\"")-s-1);
            t[strstr(s+1, "\"")-s-1] = '\0';
            strncpy(s, "", 1);
            return t;
        }
        strncpy(t, s+1, strstr(s, "\",")-s-1); // РўРѕ РёС‰РµРј РґРѕ ", - РєРѕРЅРµС† С‚РѕРіРѕ, С‡С‚Рѕ РІС‹СЂР·Р°РµРј
        t[strstr(s, "\",")-s-1] = '\0';
        strcpy(s, strstr(s, "\",")+2);
        return t;   
    } else if(strstr(s, ",")!=NULL) { // РРЅР°С‡Рµ РµСЃР»Рё РµС‰Рµ РµСЃС‚СЊ Р·Р°РїСЏС‚Р°СЏ
        strncpy(t, s, strstr(s, ",")-s); //РІС‹СЂРµР·Р°РµРј РґРѕ РЅРµРµ
        t[strstr(s, ",")-s] = '\0';
        strcpy(s, strstr(s, ",")+1);
        return t;     
    }
    strncpy(t, s, strlen(s));
    t[strlen(s)] = '\0';
    strncpy(s, "", 1);
    return t;
}
