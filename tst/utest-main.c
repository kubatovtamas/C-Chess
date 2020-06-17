//
// Created by gigi on 6/17/20.
//

// Main tests
#include "libsakk.h"

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

CU_SuiteInfo mainsakk_suites[] = {
        { "main", NULL, NULL, /*TEST SETUP*/, /*TEST TEARDOWN*/, mainsakk_tests },
        CU_SUITE_INFO_NULL      // this is needed at the end
};

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return -1;
    };
    if (CU_register_suites(mainsakk_suites) != CUE_SUCCESS) {
        return -1;
    };
    CU_basic_set_mode(CU_BRM_NORMAL);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
