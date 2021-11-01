/*
 * Minimal Testing Framework based on
 * https://github.com/siu/minunit
 */

#ifndef MINUNIT_MINUNIT_H
#define MINUNIT_MINUNIT_H

#include "common/printf.h"
#include "common/stddef.h"

/*  Misc. counters */
static int minunit_run    = 0;
static int minunit_assert = 0;
static int minunit_fail   = 0;
static int minunit_status = 0;

/*  Test setup and teardown function pointers */
static void (*minunit_setup) (void)    = NULL;
static void (*minunit_teardown) (void) = NULL;

/*  Definitions */
#define MU_TEST(method_name)      static void method_name (void)
#define MU_TEST_SUITE(suite_name) static void suite_name (void)

#define MU__SAFE_BLOCK(block) \
    do {                      \
        block                 \
    } while (0)

#define MU_RUN_SUITE(suite_name) MU__SAFE_BLOCK ( \
        suite_name ();                            \
        minunit_setup    = NULL;                  \
        minunit_teardown = NULL;)

/*  Configure setup and teardown functions */
#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) MU__SAFE_BLOCK ( \
        minunit_setup    = setup_fun;                                \
        minunit_teardown = teardown_fun;)

/*  Test runner */
#define MU_RUN_TEST(test) MU__SAFE_BLOCK (      \
        if (minunit_setup) (*minunit_setup) (); \
        minunit_status = 0;                     \
        test ();                                \
        minunit_run++;                          \
        if (minunit_status) {                   \
            minunit_fail++;                     \
            printf ("F");                       \
        } if (minunit_teardown) (*minunit_teardown) ();)

/*  Report */
#define MU_REPORT() MU__SAFE_BLOCK (                              \
        printf ("\r\n\n%d tests, %d assertions, %d failures\r\n", \
                minunit_run, minunit_assert, minunit_fail);)
#define MU_EXIT_CODE minunit_fail

/*  Assertions */
#define mu_check(test) MU__SAFE_BLOCK (                  \
        minunit_assert++;                                \
        if (!(test)) {                                   \
            printf ("%s failed:\n\t%s:%d: %s",           \
                    __func__, __FILE__, __LINE__, test); \
            minunit_status = 1;                          \
            return;                                      \
        } else {                                         \
            printf (".\r\n");                            \
        })

#define mu_fail(message) MU__SAFE_BLOCK (               \
        minunit_assert++;                               \
        printf ("%s failed:\n\t%s:%d: %s",              \
                __func__, __FILE__, __LINE__, message); \
        minunit_status = 1;                             \
        return;)

#define mu_assert(test, message) MU__SAFE_BLOCK (           \
        minunit_assert++;                                   \
        if (!(test)) {                                      \
            printf ("%s failed:\n\t%s:%d: %s",              \
                    __func__, __FILE__, __LINE__, message); \
            minunit_status = 1;                             \
            return;                                         \
        } else {                                            \
            printf (".");                                   \
        })

#define mu_assert_int_eq(expected, result) MU__SAFE_BLOCK (                      \
        int minunit_tmp_e;                                                       \
        int minunit_tmp_r;                                                       \
        minunit_assert++;                                                        \
        minunit_tmp_e = (expected);                                              \
        minunit_tmp_r = (result);                                                \
        if (minunit_tmp_e != minunit_tmp_r) {                                    \
            printf ("%s failed:\n\t%s:%d: %d expected but was %d",               \
                    __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r); \
            minunit_status = 1;                                                  \
            return;                                                              \
        } else {                                                                 \
            printf (".");                                                        \
        })

// This one requires a strcmp() funktion
/* #define mu_assert_string_eq(expected, result) MU__SAFE_BLOCK (                   \ */
/*         const char * minunit_tmp_e = expected;                                   \ */
/*         const char * minunit_tmp_r = result;                                     \ */
/*         minunit_assert++;                                                        \ */
/*         if (!minunit_tmp_e) {                                                    \ */
/*             minunit_tmp_e = "<null pointer>";                                    \ */
/*         } if (!minunit_tmp_r) {                                                  \ */
/*             minunit_tmp_r = "<null pointer>";                                    \ */
/*         } if (strcmp (minunit_tmp_e, minunit_tmp_r)) {                           \ */
/*             printf ("%s failed:\n\t%s:%d: '%s' expected but was '%s'",           \ */
/*                     __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r); \ */
/*             minunit_status = 1;                                                  \ */
/*             return;                                                              \ */
/*         } else {                                                                 \ */
/*             printf (".");                                                        \ */
/*         }) */


#endif /* MINUNIT_MINUNIT_H */
