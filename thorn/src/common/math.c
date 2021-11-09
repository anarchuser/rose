#include "common/math.h"

long abs (long n) {
    return n < 0 ? -n : n;
}

// based on binary search from https://helloacm.com/coding-exercise-implement-integer-square-root-c-online-judge/
long sqrt (long n) {
    long l = 0, r = n;
    while (l <= r) {
        long mid    = l + (r - l) / 2;// (l + r) / 2;
        long midmid = mid * mid;
        // check if n falls into [mid^2, (mid + 1)^2)
        if ((midmid <= n) && (n < (mid + 1) * (mid + 1)))
            return mid;
        if (midmid > n) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}
