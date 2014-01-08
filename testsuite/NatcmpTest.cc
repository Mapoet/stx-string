// $Id$

#include <stx-string.h>
#include <set>

#include "strnatcmp.h"
#include "check.h"

void test_static()
{
    CHECK( stx::string::natcmp("120g9el", "99") == 1 );
    CHECK( stx::string::natcmp("8", "665J319048") == -1 );
}

void test_random()
{
    for (unsigned int i = 0; i < 10000; ++i)
    {
        static const char* cset =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "01234567890123456789012345678901234567890123456789"
            "01234567890123456789012345678901234567890123456789"
            "     ";

        std::string sa = stx::string::random(rand() % 16, cset);
        std::string sb = stx::string::random(rand() % 16, cset);

        {
            int r1 = stx::string::natcmp(sa, sb);
            int r2 = strnatcmp(sa.c_str(), sb.c_str());

            if (r1 != r2) {
                std::cout << "\n"
                          << "mismatch: \"" << sa << "\" =? \"" << sb << "\"\n"
                          << "r1: " << r1 << " r2: " << r2 << "\n";
            }

            CHECK( r1 == r2 );
        }
        {
            int r1 = stx::string::natcmp_icase(sa, sb);
            int r2 = strnatcasecmp(sa.c_str(), sb.c_str());

            if (r1 != r2) {
                std::cout << "\n"
                          << "mismatch: \"" << sa << "\" =? \"" << sb << "\"\n"
                          << "r1: " << r1 << " r2: " << r2 << "\n";
            }

            CHECK( r1 == r2 );
        }
    }
}

void test_map()
{
    typedef std::set<std::string, stx::string::order_natless> natset_type;
    natset_type natset;

    natset.insert("rfc2086.txt");
    natset.insert("rfc1.txt");
    natset.insert("RFC2.txt");
    natset.insert("rfc822.txt");

    natset_type::const_iterator i = natset.begin();
    CHECK( *i++ == "RFC2.txt" );
    CHECK( *i++ == "rfc1.txt" );
    CHECK( *i++ == "rfc822.txt" );
    CHECK( *i++ == "rfc2086.txt" );
    CHECK( i == natset.end() );

    typedef std::set<std::string, stx::string::order_natless_icase_desc> natset_icase_type;
    natset_icase_type natset_icase(natset.begin(), natset.end());

    natset_icase_type::const_iterator j = natset_icase.begin();
    CHECK( *j++ == "rfc2086.txt" );
    CHECK( *j++ == "rfc822.txt" );
    CHECK( *j++ == "RFC2.txt" );
    CHECK( *j++ == "rfc1.txt" );
    CHECK( j == natset_icase.end() );
}

int main()
{
    test_static();
    test_random();
    test_map();

    return 0;
}
