// $Id$

#ifndef _STX_STRING_H_ 
#define _STX_STRING_H_

#include <string>
#include <cctype>

namespace stx {

class string : public std::string
{
public:

    /** Default constructor. Creates an empty string. */
    string()
	: std::string()
    {
    }

    /** Copy-Constructor. Duplicates the enclosed STL string. */
    string(const string &s)
	: std::string(s)
    {
    }

    /** Automatic Type-cast Constructor. Duplicates the given STL string. */
    string(const std::string &s)
	: std::string(s)
    {
    }

    /** Repeating constructor. Creates a string which contains the charater ch
     * repeated length times. */
    string(size_type length, const char& ch)
	: std::string(length, ch)
    {
    }

    /** C-style string constructor. Fills the new string with the given C-style
     * string. */
    string(const char* str)
	: std::string(str)
    {
    }

    /** C-style string constructor with length. Fills the new string with data
     * of length bytes. */
    string(const char* str, size_type length)
	: std::string(str, length)
    {
    }

    /** Substring constructor. Creates a new string containing the substring
     * specified by index and length. */
    string(const string& str, size_type index, size_type length)
	: std::string(str, index, length)
    {
    }
    
    /** Template-Iterator range constructor. Fills the new string with the
     * character in the start-end range. */
    template <typename input_iterator>
    string(input_iterator start, input_iterator end)
	: std::string(start, end)
    {
    }

    /*
     * --- Trim Functions ---
     */

    /** Trims the contained string on the left and right. Removes all
     * characters in the given drop array, which defaults to " ". Returns a
     * copy of this string.
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim(const string& drop = " ") const
    {
	size_type pos1 = find_first_not_of(drop);
	if (pos1 == npos) return string();

	size_type pos2 = find_last_not_of(drop);
	if (pos2 == npos) return string();

	return substr(pos1 == npos ? 0 : pos1,
		      pos2 == npos ? (size() - 1) : (pos2 - pos1 + 1));
    }

    /** Trims the contained string only on the left. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_left(const string& drop = " ") const
    {
	size_type pos = find_first_not_of(drop);
	if (pos == npos) return string();

	return substr(pos, npos);
    }

    /** Trims the contained string only on the right. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_right(const string& drop = " ") const
    {
	size_type pos = find_last_not_of(drop);
	if (pos == npos) return string();

	return substr(0, pos + 1);
    }

    /** Trims this string in-place on the left and right. Removes all
     * characters in the given drop array, which defaults to " ".
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_inplace(const string& drop = " ")
    {
	size_type pos = find_last_not_of(drop);
	if (pos != npos) {
	    erase(pos + 1);
	    pos = find_first_not_of(drop);
	    if (pos != npos) erase(0, pos);
	}
	else
	    erase(begin(), end());

	return *this;
    }

    /** Trims this string in-place only on the left. Removes all characters in
     * the given drop array, which defaults to " ".
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_left_inplace(const string &drop = " ")
    {
	erase(0, find_first_not_of(drop));
	return *this;
    }

    /** Trims this string in-place only on the right. Removes all characters in
     * the given drop array, which defaults to " ".
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_right_inplace(const string &drop = " ")
    {
	erase(find_last_not_of(drop) + 1, npos);
	return *this;
    }

    /*
     * --- Upper and Lower Case Functions ---
     */

    /** toupper() functional for std::transform with correct signature. */
    static char char_toupper_functional(char c)
    {
	return std::toupper(c);
    }

    /** tolower() functional for std::transform with correct signature. */
    static char char_tolower_functional(char c)
    {
	return std::tolower(c);
    }

    /** Returns a copy of the enclosed string converted to uppercase. */
    string toupper() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_toupper_functional);
	return strcopy;
    }

    /** Returns a copy of the enclosed string converted to lowercase. */
    string tolower() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_tolower_functional);
	return strcopy;
    }

    /** Transforms the enclosed string to uppercase and returns a reference to
     * this. */
    string& toupper_inplace()
    {
	std::transform(begin(), end(), begin(), char_toupper_functional);
	return *this;
    }

    /** Transforms the enclosed string to lowercase and returns a reference to
     * this. */
    string& tolower_inplace()
    {
	std::transform(begin(), end(), begin(), char_tolower_functional);
	return *this;
    }
};

} // namespace stx

#endif // _STX_STRING_H_
