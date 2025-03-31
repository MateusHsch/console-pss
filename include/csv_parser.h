#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "list.h"
#include "defines.h"

List* load_process_from_csv(List *list, char* path);

#endif