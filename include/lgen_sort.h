/******************************************************************************
*                                                                             *
*  Library    : libgen                                                        *
*                                                                             *
*  Filename   : lgen_sort.h                                                   *
*                                                                             *
*  Created    : June 20th 1996                                                *
*                                                                             *
*  Purpose    : Functions for the gen_qsort function argument.                *
*                                                                             *
*  Author(s)  : Peter Baker                                                   *
*                                                                             *
*  This file is the confidential and proprietary product of The Regents of    *
*  the University of California.  Any unauthorized use, reproduction or       *
*  transfer of this file is strictly prohibited.                              *
*                                                                             *
*  Copyright (1996-2014) The Regents of the University of California.         *
*                                                                             *
*  All rights reserved.                                                       *
*                                                                             *
******************************************************************************/

#ifndef __lgen_sort_h
#define __lgen_sort_h

#include <cstring>
#include <vector>
#include <string>
// The following notice applies to the strcasecmp function below
/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
 */
static unsigned char charmap[] = {
	000, 001, 002, 003, 004, 005, 006, 007,
	010, 011, 012, 013, 014, 015, 016, 017,
	020, 021, 022, 023, 024, 025, 026, 027,
	030, 031, 032, 033, 034, 035, 036, 037,
	040, 041, 042, 043, 044, 045, 046, 047,
	050, 051, 052, 053, 054, 055, 056, 057,
	060, 061, 062, 063, 064, 065, 066, 067,
	070, 071, 072, 073, 074, 075, 076, 077,
	0100, 0141, 0142, 0143, 0144, 0145, 0146, 0147,
	0150, 0151, 0152, 0153, 0154, 0155, 0156, 0157,
	0160, 0161, 0162, 0163, 0164, 0165, 0166, 0167,
	0170, 0171, 0172, 0133, 0134, 0135, 0136, 0137,
	0140, 0141, 0142, 0143, 0144, 0145, 0146, 0147,
	0150, 0151, 0152, 0153, 0154, 0155, 0156, 0157,
	0160, 0161, 0162, 0163, 0164, 0165, 0166, 0167,
	0170, 0171, 0172, 0173, 0174, 0175, 0176, 0177,
	0200, 0201, 0202, 0203, 0204, 0205, 0206, 0207,
	0210, 0211, 0212, 0213, 0214, 0215, 0216, 0217,
	0220, 0221, 0222, 0223, 0224, 0225, 0226, 0227,
	0230, 0231, 0232, 0233, 0234, 0235, 0236, 0237,
	0240, 0241, 0242, 0243, 0244, 0245, 0246, 0247,
	0250, 0251, 0252, 0253, 0254, 0255, 0256, 0257,
	0260, 0261, 0262, 0263, 0264, 0265, 0266, 0267,
	0270, 0271, 0272, 0273, 0274, 0275, 0276, 0277,
	0300, 0341, 0342, 0343, 0344, 0345, 0346, 0347,
	0350, 0351, 0352, 0353, 0354, 0355, 0356, 0357,
	0360, 0361, 0362, 0363, 0364, 0365, 0366, 0367,
	0370, 0371, 0372, 0333, 0334, 0335, 0336, 0337,
	0340, 0341, 0342, 0343, 0344, 0345, 0346, 0347,
	0350, 0351, 0352, 0353, 0354, 0355, 0356, 0357,
	0360, 0361, 0362, 0363, 0364, 0365, 0366, 0367,
	0370, 0371, 0372, 0373, 0374, 0375, 0376, 0377,
};

inline int genStrcasecmp ( const char *s1, const char *s2, char c )
{
    register unsigned char u1, u2;

    for (;;) {
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (charmap[u1] != charmap[u2]) {
			return charmap[u1] - charmap[u2];
		}
		if ( u1 == c ) {
			return 0;
		}
    }
}
inline int genStrcasecmp ( const char *s1, const char *s2 )
{
    register unsigned char u1, u2;

    for (;;) {
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (charmap[u1] != charmap[u2]) {
			return charmap[u1] - charmap[u2];
		}
		if ( u1 == '\0' ) {
			return 0;
		}
    }
}
inline int genStrncasecmp ( const char *s1, const char *s2, register size_t n )
{
	register unsigned char u1, u2;

	for (; n != 0; --n) {
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (charmap[u1] != charmap[u2]) {
			return charmap[u1] - charmap[u2];
		}
		if (u1 == '\0') {
			return 0;
		}
	}
	return 0;
}
inline int genStrcasecmp ( const std::string& s1, const std::string& s2 )
{
	return genStrcasecmp ( s1.c_str (), s2.c_str () );
}
inline int genStrncasecmp ( const std::string& s1, const std::string& s2, register size_t n )
{
	return genStrncasecmp ( s1.c_str (), s2.c_str (), n );
}

struct IndexedInt {
	int number;
	int index;
	bool operator== ( const IndexedInt& rhs ) const
	{
		return number == rhs.number && index == rhs.index;
	}
};
typedef std::vector <IndexedInt> VectorIndexedInt;
typedef VectorIndexedInt::const_iterator VectorIndexedIntConstIterator;
typedef VectorIndexedInt::size_type VectorIndexedIntSizeType;

struct IndexedDouble {
	double number;
	int index;
};

struct IndexedConstCString {
	const char* name;
	int index;
};
typedef std::vector <IndexedConstCString> VectorIndexedConstCString;
typedef VectorIndexedConstCString::const_iterator VectorIndexedConstCStringConstIterator;
typedef VectorIndexedConstCString::size_type VectorIndexedConstCStringSizeType;

struct IndexedCString {
	char* name;
	int index;
};

struct IndexedString {
	std::string name;
	int index;
};

struct DoubleString {
	char* array;
	double number;
};

class SortDoubleStringAscending {
	public:
		int operator () ( const DoubleString& a, const DoubleString& b ) const
		{
			return ( a.number < b.number );
		}
};
class SortIndexedIntAscending {
	public:
		int operator () ( const IndexedInt& a, const IndexedInt& b ) const
		{
			return ( a.number == b.number ) ? a.index < b.index : a.number < b.number;
		}
		int operator () ( const IndexedInt& a, const int b ) const
		{
			return a.number < b;
		}
};
class SortIndexedDoubleAscending {
	public:
		int operator () ( const IndexedDouble& a, const IndexedDouble& b ) const
		{
			return ( a.number == b.number ) ? a.index < b.index : a.number < b.number;
		}
};
class SortIndexedStrcasecmpAscending {
	public:
		bool operator () ( const IndexedConstCString& a, const IndexedConstCString& b ) const
		{
			int ret = genStrcasecmp ( a.name, b.name );

			if ( ret == 0 ) {
				return ( a.index < b.index );
			}
			return ( ret < 0 );
		}	
		bool operator () ( const IndexedConstCString& a, const char* b ) const
		{
			return genStrcasecmp ( a.name, b ) < 0;
		}	
};
class SortIndexedStrcmpAscending {
	public:
		bool operator () ( const IndexedConstCString& a, const IndexedConstCString& b ) const
		{
			int ret = strcmp ( a.name, b.name );

			if ( ret == 0 ) {
				return ( a.index < b.index );
			}
			return ( ret < 0 );
		}	
};
class SortStrcmpAscending {
	public:
		bool operator () ( const char* a, const char* b ) const
		{
			return ( strcmp ( a, b ) < 0 );
		}	
};

class genStrcasecmpAscending {
public:
	bool operator () ( const char* a, const char* b ) const
	{
		return genStrcasecmp ( a, b ) < 0;
	}
	bool operator () ( std::string const& a, std::string const& b ) const
	{
		return genStrcasecmp ( a.c_str (), b.c_str () ) < 0;
	}
};

class genStrcasecmpAscendingDelim {
	char delim;
public:
	genStrcasecmpAscendingDelim ( char delim ) :
		delim ( delim ) {}
	bool operator () ( const char* a, const char* b ) const
	{
		return genStrcasecmp ( a, b, delim ) < 0;
	}
};

class genNumberStringAscending {
public:
	bool operator () ( const std::string& a, const std::string& b ) const
	{
		return atof ( a.c_str () ) < atof ( b.c_str () );
	}
};

class CheckStrcasecmpEquality {
	std::string ss;
public:
	CheckStrcasecmpEquality ( const std::string& ss ) :
		ss ( ss ) {}
	bool operator () ( const std::string& s )
	{
		return genStrcasecmp ( s.c_str (), ss.c_str () ) == 0;
	}
};

#endif /* ! __lgen_sort_h */
