#include "../include/upload.h"

int fileExists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int uploadFile(const char *fileLocation, const char *webhook) {
    if (!fileExists(fileLocation)) {
        fprintf(stderr, "File does not exist: %s\n", fileLocation);
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    CURLcode res;
    struct curl_mime *mime;
    struct curl_mimepart *part;

    mime = curl_mime_init(curl);
    part = curl_mime_addpart(mime);
    curl_mime_name(part, "file");
    curl_mime_filedata(part, fileLocation);

    curl_easy_setopt(curl, CURLOPT_URL, webhook);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_mime_free(mime);

    return (res == CURLE_OK) ? 0 : -1;
}

int uploadText(const char *text, const char *webhook) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    CURLcode res;
    char postFields[1024];
    snprintf(postFields, sizeof(postFields), "{\"content\": \"%s\"}", text);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, webhook);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return (res == CURLE_OK) ? 0 : -1;
}

int uploadJSON(const char *json, const char *webhook) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    CURLcode res;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, webhook);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return (res == CURLE_OK) ? 0 : -1;
}

int uploadAll(const char *text, const char *json, const char *fileLocation, const char *webhook) {
    if (text && uploadText(text, webhook) != 0) return -1;
    if (json && uploadJSON(json, webhook) != 0) return -1;
    if (fileLocation && uploadFile(fileLocation, webhook) != 0) return -1;
    return 0;
}

