#include <iostream>
#include <vector>

using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

/*
GIVEN: A, B, C, D, four integers in 0-9
WANTED: the number of unique possible times in 24 hour format formed using A, B, C, D
CONDITIONS:
    - Each variable can only be used once in each combination
    - If two variable are the same, they can both be used in the combination
    - The combination must be a valid 24 hour time
    - If the first number of the combination is 0 or 1
        - the second number can be anyting
    - If the first number of the combination is 2
        - the second number is less than 4
    - the third digit is always less than 4
    - the fourth digit can be anything
ALGORITHM:
    - Create a list called digits[4] to hold A, B, C, D
    - Create an array called used_times [4][4][4][4]
    - Iterate through digits, with first_digit_loc, and check if the number is less than 3
        - Iterate through the digits, with second_digit_loc, and check if the number is not first_digit_loc and
            - if first_digit is 2 check if the second_digit is less than 4
                - Iterate through the digits, with third_digit_loc, and check if the number is not first_digit_loc_ or second_digit_loc
                  and the third_digit is less than 6
                    - Iterate through the digits, with fourth_digit_loc, and check if the number is not first, second, third digit_loc
                        - Check if this is a new time
                            - Add to used_times
    - Find the size of used_times and return
*/
const int NUMBER_OF_INPUTS = 4;
int solution(int A, int B, int C, int D)
{
    int digits[] = {A, B, C, D};
    // create an array to hold the times that we have visited
    bool used_times[NUMBER_OF_INPUTS][NUMBER_OF_INPUTS][NUMBER_OF_INPUTS][NUMBER_OF_INPUTS];
    int number_of_times = 0;

    for (int loc_1 = 0; loc_1 < NUMBER_OF_INPUTS; loc_1++)
    {
        //the 10s hour digit must be less than 3 as there are only 24 hours in a day, also the digits can't be reused
        bool valid_1 = digits[loc_1] < 3;
        for (int loc_2 = 0; loc_2 < NUMBER_OF_INPUTS && valid_1; loc_2++)
        {
            // the hours digit must be less than 4 if the 10s hour digit is 2 as before hour 20, the hour can be 0-9
            // but at hour 20 it can only be 0-3, also the digits can't be reused
            bool valid_2 = digits[loc_1] < 2 || (digits[loc_1] == 2 && digits[loc_2] < 4);
            valid_2 = valid_2 && loc_2 != loc_1;

            for (int loc_3 = 0; loc_3 < NUMBER_OF_INPUTS && valid_2; loc_3++)
            {
                // the 10s minute digit must not the first or second digit reused, and must be less than 60 as its maximum is 59
                bool valid_3 = loc_3 != loc_1 && loc_3 != loc_2 && digits[loc_3] < 6;

                for (int loc_4 = 0; loc_4 < NUMBER_OF_INPUTS && valid_3; loc_4++)
                {
                    // minutes digit just can't be reused first, second or third digit
                    bool valid_4 = loc_4 != loc_1 && loc_4 != loc_2 && loc_4 != loc_3;
                    // check that this time hasn't already been used
                    valid_4 = valid_4 && !used_times[digits[loc_1]][digits[loc_2]][digits[loc_3]][digits[loc_4]];

                    if (valid_4)
                    {
                        //if this time is new increase the number of times we have seen and remember that we have seen this
                        number_of_times++;
                        used_times[digits[loc_1]][digits[loc_2]][digits[loc_3]][digits[loc_4]] = true;
                    }
                }
            }
        }
    }

    return number_of_times;
}

int main()
{
    int A = 1, B = 2, C = 3, D = 4;
    int result = 0;
    // test cases: 
    //all digits are greater than 3, no valid time
    A = 3, B = 4, C = 5, D = 6;
    // expected: 0, result 0
    result = solution(A, B, C, D);

    //two digits are greater than 5, one digit is less than two, one is less than 5,
    A = 9, B = 8, C = 2, D = 1;
    // expected: 2, result 2
    result = solution(A, B, C, D);

    //all digits are less than 2, and the same
    A = 1, B = 1, C = 1, D = 1;
    // expected: 1, result 22, 1
    result = solution(A, B, C, D);

    //all digits are less than 2, and the same
    A = 1, B = 1, C = 1, D = 1;
    // expected: 1, result 22, 1
    result = solution(A, B, C, D);

    //all digits are less than 2, three are equal one is different
    A = 2, B = 1, C = 1, D = 1;
    // expected: 4, result 22, 1
    result = solution(A, B, C, D);

    // some times are less than 19:59 and some are greater but less than 24:59
    A = 2, B = 4, C = 5, D = 1;
    // expected: 4, result 22, 1
    result = solution(A, B, C, D);

    cout << result << endl;
    return result;
}
/*
g++ number_of_times.cpp (converts c++ code to machine readable code(compiles))
./a.out (runs the machine readable code)
g++ number_of_times.cpp; ./a.out
*/