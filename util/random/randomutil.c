//
// Created by LRieh on 19/10/2025.
//

#include "randomutil.h"

#include <stdlib.h>

int rand_int(int min, int max) {
    return min + rand() % (max - min);
}
