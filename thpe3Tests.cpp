#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "thpe3.h"

const bool RUNCATCH = false;

int main( int argc, char **argv )
{
    Catch::Session session;
    int result;

    //TEST CASE RUNCATCH

    if( RUNCATCH )
    {
        result = session.run( argc, argv );
        if( result != 0 )
        {
            cout << "Test cases didn't pass." << endl;
            return 0;
        }
    }

    //ARGUMENT CHECK

    if( argc != 4 )
    {
        cout << "Usage: thpe3.exe -s seedValue quantity" << endl;
        cout << "       seedValue - # is integer for random numbers" << endl;
        cout << "       quantity - # of hands to deal" << endl;
        cout << endl;
        cout << "       thpe3.exe -f inputfilename outputfilename" << endl;
        cout << "       inputfilename - filename containing the poker hands to classify" << endl;
        cout << "       outputfilename - filename to output the statistics in" << endl;

        exit(0);
    }

    int i;
    int hand[5]; //Array that holds cards of the hand
    int classification[10]; //Array that holds number of occurences of each hand
    int quantity = 0; //Integer that holds number of total hands dealt
    double chance[10]; //Array that holds percentage of occurences

    ifstream fin;
    ofstream fout;

    for( i=0; i<10; i++ ) //Initializing array values to 0
    {
        classification[i] = 0;
        chance[i] = 0.000000;
    }

    //CHECKING IF ARGV[1] IS "-S", "-F" OR NOT

    if( strcmp( argv[1], "-s" ) == 0 ) //If argv[1] is "-s"
    {
        int seedValue = stoi(argv[2]);
        quantity = stoi(argv[3]);

        for( i=0; i<quantity; i++ )
        {
            dealHand( seedValue, hand );
            classification[classifyHand( hand, 5 )]++;
        }
    }

    else if( strcmp( argv[1], "-f" ) == 0 ) //If argv[1] is "-f"
    {
        int count = 0;
        int x = 0;

        fin.open( argv[2] );
        fout.open( argv[3] );

        if( !fin.is_open() )
        {
            cout << "Unable to open the file: " << argv[2] << endl;
            exit(0);
        }

        if( !fout.is_open() )
        {
            cout << "Unable to open the file: " << argv[3] << endl;
            exit(0);
        }

        while( fin >> hand[x] )
        {
            x++;
            count++;

            if( count%5 == 0 )
            {
                classification[classifyHand( hand, 5 )]++;
                quantity++; //keeps track of number of hands dealt
                x = 0;
            }
        }
    }

    else //If argv[1] is not "-s" or "-f"
    {
        cout << "Invalid Option" << endl;
        exit(0);
    }

    //FINDING CHANCE VALUES

    for( i=0; i<10; i++ )
    {
        chance[i] = double( ( double(classification[i])*100 ) / double(quantity) );
    }

    //OUTPUT

    if( argv[1][1] == 's' )
    {
        cout << "Hand Name" << setw(21) << "Dealt" << setw(15) << "Chance" << endl;

        cout << "Royal Flush" << setw(19) << classification[9] << setw(15) << fixed << setprecision(6) << chance[9] << "%" << endl;
        cout << "Straight Flush" << setw(16) << classification[8] << setw(15) << fixed << setprecision(6) << chance[8] << "%" << endl;
        cout << "Four of a Kind" << setw(16) << classification[7] << setw(15) << fixed << setprecision(6) << chance[7] << "%" << endl;
        cout << "Full House" << setw(20) << classification[6] << setw(15) << fixed << setprecision(6) << chance[6] << "%" << endl;
        cout << "Flush" << setw(25) << classification[5] << setw(15) << fixed << setprecision(6) << chance[5] << "%" << endl;
        cout << "Straights" << setw(21) << classification[4] << setw(15) << fixed << setprecision(6) << chance[4] << "%" << endl;
        cout << "Three of a Kind" << setw(15) << classification[3] << setw(15) << fixed << setprecision(6) << chance[3] << "%" << endl;
        cout << "Two Pair" << setw(22) << classification[2] << setw(15) << fixed << setprecision(6) << chance[2] << "%" << endl;
        cout << "Two of a Kind" << setw(17) << classification[1] << setw(15) << fixed << setprecision(6) << chance[1] << "%" << endl;
        cout << "High Card" << setw(21) << classification[0] << setw(15) << fixed << setprecision(6) << chance[0] << "%" << endl;

        cout << endl;

        cout << "Total Hands Dealt" << setw(13) << quantity << endl;
    }

    else if( argv[1][1] == 'f' )
    {
        fout << "Hand Name" << setw(21) << "Dealt" << setw(15) << "Chance" << endl;

        fout << "Royal Flush" << setw(19) << classification[9] << setw(15) << fixed << setprecision(6) << chance[9] << "%" << endl;
        fout << "Straight Flush" << setw(16) << classification[8] << setw(15) << fixed << setprecision(6) << chance[8] << "%" << endl;
        fout << "Four of a Kind" << setw(16) << classification[7] << setw(15) << fixed << setprecision(6) << chance[7] << "%" << endl;
        fout << "Full House" << setw(20) << classification[6] << setw(15) << fixed << setprecision(6) << chance[6] << "%" << endl;
        fout << "Flush" << setw(25) << classification[5] << setw(15) << fixed << setprecision(6) << chance[5] << "%" << endl;
        fout << "Straights" << setw(21) << classification[4] << setw(15) << fixed << setprecision(6) << chance[4] << "%" << endl;
        fout << "Three of a Kind" << setw(15) << classification[3] << setw(15) << fixed << setprecision(6) << chance[3] << "%" << endl;
        fout << "Two Pair" << setw(22) << classification[2] << setw(15) << fixed << setprecision(6) << chance[2] << "%" << endl;
        fout << "Two of a Kind" << setw(17) << classification[1] << setw(15) << fixed << setprecision(6) << chance[1] << "%" << endl;
        fout << "High Card" << setw(21) << classification[0] << setw(15) << fixed << setprecision(6) << chance[0] << "%" << endl;

        fout << endl;

        fout << "Total Hands Dealt" << setw(13) << quantity << endl;
    }

    //CLOSE FILES

    fin.close();
    fout.close();

    exit(0);

    return 0;

}

//TEST CASES OF CLASSIFYHAND

TEST_CASE( "classifyHand - RoyalFlush check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 13, 22, 23, 24, 25 };
        REQUIRE( classifyHand( hand, 5 ) == RoyalFlushX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 0, 9, 10, 11, 12 };
        REQUIRE( classifyHand( hand, 5 ) == RoyalFlushX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 39, 48, 49, 50, 51 };
        REQUIRE( classifyHand( hand, 5 ) == RoyalFlushX );
    }
}

TEST_CASE( "classifyHand - StraightFlush check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 44, 45, 46, 47, 48 };
        REQUIRE( classifyHand( hand, 5 ) == StraightFlushX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 0, 1, 2, 3, 4 };
        REQUIRE( classifyHand( hand, 5 ) == StraightFlushX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 11, 12, 13, 14, 15 };
        REQUIRE( classifyHand( hand, 5 ) == 0 ); //Invalid
    }
}

TEST_CASE( "classifyHand - FourOfAKind check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 7, 20, 33, 46, 0 };
        REQUIRE( classifyHand( hand, 5 ) == FourOfAKindX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 10, 1, 23, 36, 49 };
        REQUIRE( classifyHand( hand, 5 ) == FourOfAKindX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 3, 16, 13, 29, 42 };
        REQUIRE( classifyHand( hand, 5 ) == FourOfAKindX ); 
    }
}

TEST_CASE( "classifyHand - FullHouse check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 3, 42, 9, 35, 22 };
        REQUIRE( classifyHand( hand, 5 ) == FullHouseX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 4, 17, 11, 24, 50 };
        REQUIRE( classifyHand( hand, 5 ) == FullHouseX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 12, 7, 33, 51, 46 };
        REQUIRE( classifyHand( hand, 5 ) == FullHouseX ); 
    }
}

TEST_CASE( "classifyHand - Flush check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 27, 30, 33, 35, 38 };
        REQUIRE( classifyHand( hand, 5 ) == FlushX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 14, 24, 13, 25, 19 };
        REQUIRE( classifyHand( hand, 5 ) == FlushX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 51, 39, 43, 41, 46 };
        REQUIRE( classifyHand( hand, 5 ) == FlushX ); 
    }
}

TEST_CASE( "classifyHand - Straight check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 0, 14, 15, 29, 43 };
        REQUIRE( classifyHand( hand, 5 ) == StraightX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 4, 18, 19, 20, 34 };
        REQUIRE( classifyHand( hand, 5 ) == StraightX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 0, 22, 23, 37, 51 };
        REQUIRE( classifyHand( hand, 5 ) == StraightX ); 
    }
}

TEST_CASE( "classifyHand - ThreeOfAKind check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 0, 13, 26, 7, 35 };
        REQUIRE( classifyHand( hand, 5 ) == ThreeOfAKindX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 11, 1, 24, 36, 50 };
        REQUIRE( classifyHand( hand, 5 ) == ThreeOfAKindX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 18, 16, 13, 31, 44 };
        REQUIRE( classifyHand( hand, 5 ) == ThreeOfAKindX ); 
    }
}

TEST_CASE( "classifyHand - TwoPair check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 15, 41, 7, 20, 51 };
        REQUIRE( classifyHand( hand, 5 ) == TwoPairX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 35, 1, 27, 36, 48 };
        REQUIRE( classifyHand( hand, 5 ) == TwoPairX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 18, 25, 13, 31, 51 };
        REQUIRE( classifyHand( hand, 5 ) == TwoPairX ); 
    }
}

TEST_CASE( "classifyHand - TwoOfAKind check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 9, 49, 32, 41, 15 };
        REQUIRE( classifyHand( hand, 5 ) == TwoOfAKindX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 11, 1, 24, 36, 51 };
        REQUIRE( classifyHand( hand, 5 ) == TwoOfAKindX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 18, 16, 13, 31, 43 };
        REQUIRE( classifyHand( hand, 5 ) == TwoOfAKindX ); 
    }
}

TEST_CASE( "classifyHand - HighCard check" )
{
    SECTION( "#1" )
    {
        int hand[5] = { 0, 1, 16, 17, 34 };
        REQUIRE( classifyHand( hand, 5 ) == HighCardX );
    }
    SECTION( "#2" )
    {
        int hand[5] = { 27, 3, 18, 33, 51 };
        REQUIRE( classifyHand( hand, 5 ) == HighCardX );
    }
    SECTION( "#3" )
    {
        int hand[5] = { 6, 21, 29, 31, 43 };
        REQUIRE( classifyHand( hand, 5 ) == HighCardX ); 
    }
}

//TEST CASE FOR DEALHAND

TEST_CASE( "dealHand - Generate Hand using Seed value" )
{
    int seed = 59;
    int hand[5];

    SECTION( "#1" )
    {
        dealHand( seed, hand );
        REQUIRE( hand[0] == 13 );
        REQUIRE( hand[1] == 4 );
        REQUIRE( hand[2] == 17 );
        REQUIRE( hand[3] == 15 );
        REQUIRE( hand[4] == 23 );
    }
    SECTION( "#2" )
    {
        dealHand( seed, hand );
        REQUIRE( hand[0] == 43 );
        REQUIRE( hand[1] == 45 );
        REQUIRE( hand[2] == 49 );
        REQUIRE( hand[3] == 4 );
        REQUIRE( hand[4] == 51 );
    }
    SECTION( "#3" )
    {
        dealHand( seed, hand );
        REQUIRE( hand[0] == 27 );
        REQUIRE( hand[1] == 48 );
        REQUIRE( hand[2] == 23 );
        REQUIRE( hand[3] == 7 );
        REQUIRE( hand[4] == 5 );
    }
}