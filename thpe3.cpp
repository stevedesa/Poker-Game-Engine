/** **************************************************************************
 * @file 
 ****************************************************************************/

#include "thpe3.h"

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To deal a Hand if seed value is provided. The function generates 5 unique
 * values into the hand array and returns it back to the user for classification.
 * 
 * @param[in] seedValue - holds seed value.
 * @param[in,out] hand - hand array that stores hand cards.
 * 
 * @par Example
 * @verbatim
   int seed = 59;
   int hand[5];

   dealHand( seed, hand );

   REQUIRE( hand[0] == 13 );
   REQUIRE( hand[1] == 4 );
   REQUIRE( hand[2] == 17 );
   REQUIRE( hand[3] == 15 );
   REQUIRE( hand[4] == 23 );
   @endverbatim
 *****************************************************************************/
void dealHand( int seedValue, int hand[] )
{
    int i;
    int lookup[52] = {};
    bool done = false;

    static default_random_engine engine( seedValue );
    uniform_int_distribution<int> deck(0,51);

    for( i=0; i<5; i++ )
    {
        done = false;
        while( done == false )
        {
            hand[i] = deck( engine );
            if( lookup[hand[i]] == 0 )
            {
                lookup[hand[i]]++;
                done = true;
            }
        }
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify the type of hand the hand array holds. The hand array sorts array
 * into lookup arrays for face values and suit values and passes these to individual
 * functions that identifies the type of hand and accordingly returns what type of 
 * hand the array holds.
 * 
 * @param[in] hand - hand array that stores hand cards.
 * @param[in] size - holds size of array hand.
 * 
 * @returns number that corresponds to hand.
 * 
 * @par Example
 * @verbatim
   int hand[5];
   int size = 5;

   hand[5] = { 13, 22, 23, 24, 25 };
   REQUIRE( classifyHand( hand, 5 ) == 9 ); //Royal Flush

   hand[5] = { 44, 45, 46, 47, 48 };
   REQUIRE( classifyHand( hand, 5 ) == 8 ); //Straight Flush
   @endverbatim
 *****************************************************************************/
int classifyHand( int hand[], int size )
{
    int i;
    int face_lookup[13] = {};
    int suit_lookup[4] = {};

    for( i=0; i<size; i++ ) //Filling lookup array 
    {
        int face = hand[i]%13;
        int suit = hand[i]/13;

        face_lookup[face]++;
        suit_lookup[suit]++;
    }

    if ( RoyalFlush( face_lookup, suit_lookup ) == true )
    {
        return RoyalFlushX;
    }
    else if ( StraightFlush( face_lookup, suit_lookup ) == true )
    {
        return StraightFlushX;
    }
    else if ( FourOfAKind( face_lookup ) == true )
    {
        return FourOfAKindX;
    }
    else if ( FullHouse( face_lookup ) == true )
    {
        return FullHouseX;
    }
    else if ( Flush( suit_lookup ) == true )
    {
        return FlushX;
    }
    else if ( Straight( face_lookup ) == true )
    {
        return StraightX;
    }
    else if ( ThreeOfAKind( face_lookup ) == true )
    {
        return ThreeOfAKindX;
    }
    else if ( TwoPair( face_lookup ) == true )
    {
        return TwoPairX;
    }
    else if ( TwoOfAKind( face_lookup ) == true )
    {
        return TwoOfAKindX;
    }
    else
    {
        return HighCardX;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Royal Flush Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * @param[in] suit - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Royal Flush else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };
   int suit[4] = { 5, 0, 0, 0 }

   bool x = RoyalFlush( face, suit ); //true
   @endverbatim
 *****************************************************************************/
bool RoyalFlush( int face[], int suit[] )
{
    if( suit[0] == 5 || suit[1] == 5 || suit[2] == 5 || suit[3] == 5 )
    {
        if( face[0] == 1 && face[9] == 1 && face[10] == 1 && face[11] == 1 && face[12] == 1 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Straight Flush Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * @param[in] suit - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Straight Flush else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
   int suit[4] = { 5, 0, 0, 0 }

   bool x = StraightFlush( face, suit ); //true
   @endverbatim
 *****************************************************************************/
bool StraightFlush( int face[], int suit[] )
{
    int i;

    if( suit[0] == 5 || suit[1] == 5 || suit[2] == 5 || suit[3] == 5 )
    {
        for( i=0; i<13 && face[i] == 0; i++ )
        { }

        if( face[i+1] == 1 && face[i+2] == 1 && face[i+3] == 1 && face[i+4] == 1 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Four of a Kind Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Four of a Kind else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };

   bool x = FourOfAKind( face ); //true
   @endverbatim
 *****************************************************************************/
bool FourOfAKind( int face[] )
{
    int i;

    for( i=0; i<13; i++ )
    {
        if( face[i] == 4 )
        {
            return true;
        }
    }
    return false;
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Full House Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Full House else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   bool x = FullHouse( face ); //true
   @endverbatim
 *****************************************************************************/
bool FullHouse( int face[] )
{
    int i;
    bool one = false, two = false;

    for( i=0; i<13; i++ )
    {
        if( face[i] == 2 )
        {
            one = true;
        }
        if( face[i] == 3 )
        {
            two = true;
        }
    }

    if( one == true && two == true )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Flush Hand
 * 
 * @param[in] suit - lookup array that stores suit values.
 * 
 * @returns true if array corresponds to Flush else false
 * 
 * @par Example
 * @verbatim
   int suit[4] = { 5, 0, 0, 0 };

   bool x = Flush( suit ); //true
   @endverbatim
 *****************************************************************************/
bool Flush( int suit[] )
{
    if( suit[0] == 5 || suit[1] == 5 || suit[2] == 5 || suit[3] == 5 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Straight Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Straight else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };

   bool x = Straight( face ); //true
   @endverbatim
 *****************************************************************************/
bool Straight( int face[] )
{
    int i;

    for( i=0; i<13 && face[i] == 0 ; i++ )
    { }

    if( i == 0 && face[9] == 1 && face[10] == 1 && face[11] == 1 && face[12] == 1 )
    {
        return true;
    }
    else if( i < 9 && face[i+1] == 1 && face[i+2] == 1 && face[i+3] == 1 && face[i+4] == 1 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Three of a Kind Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Three of a Kind else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 };

   bool x = ThreeOfAKind( face ); //true
   @endverbatim
 *****************************************************************************/
bool ThreeOfAKind( int face[] )
{
    int i, x=0;
    int extras[5];
    bool kind = false;

    for( i=0; i<13; i++ )
    {
        if( face[i] == 3 )
        {
            kind = true;
        }
        if( face[i] == 1 )
        {
            extras[x] = i;
            x++;
        }
    }

    if( kind == true && ( extras[0] != extras[1] ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Two Pair Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Four of a Kind else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 2, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };

   bool x = TwoPair( face ); //true
   @endverbatim
 *****************************************************************************/
bool TwoPair( int face[] )
{
    int i, x=0;
    int extras[5];
    bool kind = false;

    for( i=0; i<13; i++ )
    {
        if( face[i] == 2 )
        {
            kind = true;
            extras[x] = i;
            x++;
        }
    }

    if( kind == true && x == 2 && ( extras[0] != extras[1] ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * To classify if the face and suit lookup arrays provided correspond to the 
 * Two of a Kind Hand
 * 
 * @param[in] face - lookup array that stores face values.
 * 
 * @returns true if array corresponds to Two of a Kind else false
 * 
 * @par Example
 * @verbatim
   int face[13] = { 2, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0 };

   bool x = TwoOfAKind( face ); //true
   @endverbatim
 *****************************************************************************/
bool TwoOfAKind( int face[] )
{
    int i, x=0;
    int extras[5];
    bool kind = false;

    for( i=0; i<13; i++ )
    {
        if( face[i] == 2 )
        {
            kind = true;
        }
        if( face[i] == 1 )
        {
            extras[x] = i;
            x++;
        }
    }

    if( kind == true && ( extras[0] != extras[1] != extras[2] ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}