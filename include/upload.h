#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#ifndef UPLOAD_H
#define UPLOAD_H

int uploadFile(char const *fileLocation, char const *webhook);

int fileExists(const char *path);

int uploadText(char const *text, char const *webhook);

int uploadJSON(char const *json, char const *webhook);

int uploadAll(char const *text, char const * json, char const *fileLocation, char const *webhook);

#endif
