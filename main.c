#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "include/upload.h"

int main(int argc, char const *argv[]) {
    // Define help message string
    const char *helpString = "Usage: %s --file {pathToFile, optional} --json {jsonString, optional} "
                             "--text {textString, optional} --webhook {discordWebhook, required} --help {showsHelpMessage, optional}\n\n"
                             "NOTE: Must have at least a file, json string, or text. Do not have to have all.\n\n";

    // Variables for different options
    const char *pathToFile = "";
    int isFile = 0;
    const char *json = "";
    int isJson = 0;
    const char *text = "";
    int isText = 0;
    const char *webhook = "";
    int opt = 0;
    int success = 0; // Initialize success variable

    // Define long options
    struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"file", required_argument, NULL, 'f'},
        {"json", required_argument, NULL, 'j'},
        {"text", required_argument, NULL, 't'},
        {"webhook", required_argument, NULL, 'w'},
        {NULL, 0, NULL, 0}  // Null terminator for the array
    };

    // Parse the options
    while ((opt = getopt_long(argc, argv, "f::j::t::w:h", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                isFile = 1;
                pathToFile = optarg;
                break;

            case 'j':
                isJson = 1;
                json = optarg;
                break;

            case 't':
                isText = 1;
                text = optarg;
                break;

            case 'w':
                webhook = optarg;
                break;

            case 'h':
                printf(helpString, argv[0]);
                return 0;
        }
    }

    // If help is not requested and at least one of the required parameters is present, proceed with the upload
    if (isFile || isJson || isText) {
        // Perform appropriate upload based on the given options
        if (isFile && isJson && isText) {
            success = uploadAll(text, json, pathToFile, webhook);
        } else {
            if (isFile) {
                success = uploadFile(pathToFile, webhook);
            }
            if (isJson) {
                success = uploadJSON(json, webhook);
            }
            if (isText) {
                success = uploadText(text, webhook);
            }
        }
    } else {
        // No valid file, json, or text option provided
        printf(helpString, argv[0]);
        return -1;
    }

    // If upload failed, print error message
    if (success != 0) {
        printf("Failed to upload\n");
        return -1;
    }

    return 0;
}

