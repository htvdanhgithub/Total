#ifndef COMMON_H
#define COMMON_H

#define DEBUG      0
#define UNITTEST   0

#include <Arduino.h>

#if (DEBUG)
#define MAX_MSG_LEN   40
#else
#define MAX_MSG_LEN   256
#endif
#define MAX_PHONE_LEN   20
#endif // COMMON_H
