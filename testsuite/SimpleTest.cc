// $Id$

#include <cppunit/extensions/HelperMacros.h>

#include <stx-string.h>

class SimpleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SimpleTest );
    CPPUNIT_TEST(test_prefix);
    CPPUNIT_TEST_SUITE_END();

protected:

    void test_prefix()
    {
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTest );
