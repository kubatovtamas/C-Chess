//
// Created by gigi on 6/17/20.
//

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "utest-piece.h"

void test_load_from_file() {

}
void test_save_to_file() {

}


CU_TestInfo filehandler_tests[] = {
        {"load_test",               test_load_from_file},
        {"save_test",               test_save_to_file},
        CU_TEST_INFO_NULL
};