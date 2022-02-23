#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <float.h>
#include <fenv.h>
#include "Kvadrashka.h"



int main(void) {

    int request = NAN;

    Print_Intro ();

    switch(Lets_Start_Program (&request)) {
        case 1:
            Main_Part ();
            break;
        case 0:
            Print_Result_UnitTest (Run_UnitTest());
            break;
        default:
            return 0;
    }

    return 0;
}




/// This funtction function dropes introduction of the program
void Print_Intro (void) {
    printf("\n\t\t\t\t Solution of square equation\n"
           "\t\t\t\t (up to 3 decimal places)\n");
}
/*!
@breaf Function
*/

void Main_Part (void) {
    double a = NAN, b = NAN, c = NAN;
    double root_1 = NAN, root_2 = NAN;

    printf("\t Enter quotients of the equation:\n");

    Read_Input(&a, 0);
    Read_Input(&b, 1);
    Read_Input(&c, 2);
    Transfom_Coefs(&a, &b, &c);


    int nRoots = Solve_Square (a, b, c, &root_1, &root_2);

    If_Strive_To_Zero(&root_1, &root_2);

    Print_Roots(nRoots, &root_1, &root_2);

}

//! This function define the type of equation and solve it
//!
//! @param [in]    a     ( first coeficient)
//! @param [in]    b     (second coeficient)
//! @param [in]    c     (third coefficient)
//!
//! @param [out]   root_1      ( first root)
//! @param [out]   root_2      (second root)
//!
//! @return nRoots         (Number of roots)

int Solve_Square (const double a, const double b, const double c,
                  double *root_1, double *root_2) {


    assert(root_1 != NULL);
    assert(root_2 != NULL);
    assert(root_1 != root_2);


    if (Is_Equal(a, 0)) {

         if (Is_Equal(b , 0)) {
             return (Is_Equal(c, 0)) ? INF_ROOTS : NO_ROOTS;
         }

         else {
             *root_1 = -c / b ;
             return ONE_ROOT;
         }
    }
    else
    {
        double Diskriminant = b*b - 4*a*c;

        if (Diskriminant >= 0) {

            if (Is_Equal(Diskriminant , 0)) {
                *root_1 = *root_2 = -b / (2*a) ;
                return ONE_ROOT;
            }
            else
            {
                double double_a = 2 * a;
                *root_1 = (-b + sqrt(Diskriminant)) / double_a;
                *root_2 = (-b - sqrt(Diskriminant)) / double_a;

                double diff = *root_1 - *root_2;
                double max = NAN;

                if (diff > 0.0) {
                    max = *root_1;
                    *root_1 = *root_2;
                    *root_2 = max;
                }
                return TWO_ROOTS;
            }
        }
        else
        {
            return NO_ROOTS;
        }
    }

}

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//

void Transfom_Coefs (double * a, double * b, double * c) {

// сравнить наибольшее с нулем: если равен, то всем присваиваем ноль,
// если нет, то делим на наибольшее и получаем нормальные коэффициенты
    double max = 0;

    if ( *a - *b > 0) {  // a > b
        if ( *c - *a > 0) { // c - max
            max = *c;
        }
        else {
            max = *a;  // a - max
        }
    }
    else { // b > a
        if ( *b - *c > 0) { // b - max
            max = *b;
        }
        else { // c - max
            max = *c;
        }
    }

    *a = (double) *a / max;
    *b = (double) *b / max;
    *c = (double) *c / max;

}
//! @detailed This function prints the response depending on the value
//! of the function Solve_Square
//!
//! @param  [in]   nRoots  (Number of roots)
//!
//! @param [out]   root_1      ( first root)
//! @param [out]   root_2      (second root)

void Print_Roots (int nRoots,
                  double *root_1, double *root_2) {


    switch (nRoots) {
        case INF_ROOTS: {
            printf("\n\t\t\t\t ANSWER:\n"
                     "\t\t\t\t Any valid number\n\n");
            break;
            }
        case NO_ROOTS: {
            printf("\n\t\t\t\t ANSWER:\n"
                     "\t\t\t\t No valid roots\n\n");
            break;
            }
        case ONE_ROOT: {
            printf("\n\t\t\t\t ANSWER:\n"
                     "\t\t\t\t x = %.3lf\n\n", *root_1);
            break;
            }
        case TWO_ROOTS: {
            printf("\n\t\t\t\t ANSWER:\n"
                     "\t\t\t\t x1 = %.3lf\n"
                     "\t\t\t\t x2 = %.3lf\n\n", *root_1, *root_2);
            break;
            }
        default:
            printf("\n\t\t\t\t Unexpected situation in function %s."
                   " Error was catched on line %d\n", __FUNCTION__, __LINE__);
            break;
    }

}

//! This function compare 2 double numbers using their difference and
//! comparing this with small number like EPSILON(const)
//!
//! @param [in]  x
//! @param [in]  y
//!
//! @return 1 if x is almost y
//! @return 0 if they are very different from each other

int Is_Equal (double x, double y) {
    if (fabs(x - y) < EPSILON) {
        return 1;
    }
    else
        return 0;
}

//! @detailed This function compare values of *root_1 and *root_2 using
//! the function Is_Equal
//!
//! @param [in]   *root_1
//! @param [in]   *root_2
//!
//! Using the function Is_Equal on *root_1 and 0, on *root_2 and 0
//!
//! @param [out]  *root_1
//! @param [ous]  *root_2

void If_Strive_To_Zero (double *root_1, double *root_2) {
    if (Is_Equal(*root_1, DBL_EPSILON)) {
        *root_1 = 0;
    }
    if (Is_Equal(*root_2, DBL_EPSILON)) {
        *root_2 = 0;
    }
}

//! @breaf Function for checking the correctness of the entered data
//! @detailed The function prompts the user to enter data about
//!           the first coefficient, reads them and acts depending
//!           on the value that the function scanf returns.
//! @detailed If scanf returns 0 - program will ask user to enter the data again

//!           If scanf returns 1 - program will check next symbol of buffer
//!           using the function Clear_Buffer

//!           If next symbol will be '\n' - the function stop and correctly
//!           read the coeficient

//!           If next symbol will be any else - the function write about
//!           an input error and will ask user to enter the data again

void Read_Input (double *a, int coef_number) {

    char coef_symbols[3] = {'a', 'b', 'c'};
    bool error = true;


    printf("\t %c = ", coef_symbols[coef_number]);
    int result = scanf("%lf", a);
    while (error) {

        if (result != 1) { // неправильный ввод первого символа
            Clear_Buffer();
            printf("\tIncorrectly input of coefficient\n");
            printf("\t %c = ", coef_symbols[coef_number]);
            // Clear_Buffer();
            result = scanf("%lf", a);
        }
        else // ввод первого символа успешен
        {
            if (getchar() != '\n') {
                Clear_Buffer();
                printf("\tIncorrect input: please, enter number of double type:\n");
                printf("\t %c = ", coef_symbols[coef_number]);
                result = scanf("%lf", a);
            }
            else { // ввод произошел корректно
                error = false;
            }
        }
    }
}

//! @breaf This function clear the buffer input

void Clear_Buffer(void) {
    while(getchar() != '\n') {;}
}

//! @breaf The function that realize Unit_Test
//! @detailed The function will solve the equation using Solve_Square with
//! entered coeficients and compare expected roots with recieved roots
//!
//! @param [in]   a
//! @param [in]   b
//! @param [in]   c
//! @param [in]   nRootsRef   (expected number of roots)
//! @param [in]   root_1Ref       ( expected first root)
//! @param [in]   root_2Ref       (expected second root)
//!
//! @param [out]  root_1          ( recieved first root)
//! @param [out]  root_2          (recieved second root)

int Unit_Test_Solve_Square (struct test_data Mass) {
    double root_1 = NAN, root_2 = NAN;

    // test_data Mass[test_number].a
    int nRoots = Solve_Square(  Mass.a,
                                Mass.b,
                                Mass.c,
                                &root_1, &root_2);

    switch (nRoots) {
        case INF_ROOTS:
            if (nRoots != Mass.nRootsRef) {
                printf("\n\tTest FAILED\n"
                "\t For a = %.3lf, b = %.3lf, c = %.3lf\n"
                "\t Expected situation: any valid roots\n"
                "\t But number of roots: %d\n"
                "\t x1 = %lf, x2 = %lf\n\n",
                Mass.a,
                Mass.b,
                Mass.c,
                Mass.nRootsRef, root_1, root_2);
            }
        ;
        case NO_ROOTS:
            if (nRoots != Mass.nRootsRef)
            {
                printf("\n\tTest FAILED\n"
                "\t For a = %.3lf, b = %.3lf, c = %.3lf\n"
                "\t Expected situation: no valid roots\n"
                "\t But number of roots: %d\n"
                "\t x1 = %lf, x2 = %lf\n\n",
                Mass.a,
                Mass.b,
                Mass.c,
                Mass.nRootsRef, root_1, root_2);
            }
            break;

        case ONE_ROOT:
            if (Is_Equal(root_1, Mass.root_1Ref) != 1 ||
                        (nRoots != Mass.nRootsRef) )
            {
                printf("\n\tTest FAILED\n"
                "\t x = %.3lf , Number of roots: %d\n"
                "\t Should be: x = %.3lf, Number of roots: %d\n\n",
                root_1, nRoots, Mass.root_1Ref,
                                Mass.nRootsRef);

                return 0;
            }

            break;

        case TWO_ROOTS:
            if (Is_Equal(root_1, Mass.root_1Ref) != 1 ||
                Is_Equal(root_2, Mass.root_2Ref) != 1 ||
                (nRoots != Mass.nRootsRef))
            {
                printf("\n\tTest FAILED\n"
                "\t x1 = %.3lf , x2 = %.3lf, Number of roots: %d\n"
                "\t Should be: x1 = %.3lf, x2 = %.3lf, Number of roots: %d\n\n",
                root_1, root_2, nRoots,
                Mass.root_1Ref,
                Mass.root_2Ref,
                Mass.nRootsRef);

                return 0;
            }

    }

    return 1;
}

//! The function run the Unit_Test_Solve_Square with different coeficients
//! and if a test will be failed a number (var int failed) of failded will be
//! more on 1
//! If failed tests will be more than 0 the function write that
//! Unit_Test_Solve_Square was failed.
//! If failed is 0 then the function will print about successful runnin of tests

int Run_UnitTest (void) {
    int failed = 0;

    for (int test_number = 0; test_number < 8; test_number++) {
        if (Unit_Test_Solve_Square( Mass[test_number]) == 0){
            failed++;
        }
    }

    return failed;
}

//! @breaf The function asks user about run the Unit_Test and print resilts of
//! that if he want it. If user doesn't want see result of Unit_Test then
//! the function will not print if

void Print_Result_UnitTest (int result) {
    if (result == 0) {
        printf("\n\t TESTS are successfully completed\n\n");
    }
    else
        printf("\n\t There are %d ERRORS in tests\n", result);
}


int Lets_Start_Program (int *request) {

    bool error = true;

    printf("\t What do you want?\n\n"
    "\t Enter 1 - to solve your equation,\n"
    "\t Enter 0 - to run unit test of program,\n"
    "\t Enter any else integer number - to leave the program\n\n"
    "\t Your choice: ");

    while (error) {

        int choice = scanf("%d", request);

        if (choice != 1) { // неправильный ввод первого символа
            Clear_Buffer();
            printf("\t INPUT ERROR. Your choice: ");
        }
        else // ввод первого символа успешен
        {
            if (getchar() != '\n') {
                printf("\t INPUT ERROR. Your choice: ");
                scanf("%d", request);
                Clear_Buffer();
            }
            else { // ввод произошел корректно
                if (*request == 1) {
                    return 1;
                }
                if (*request == 0) {
                    return 0;
                }
                if ((*request != 0)&&(*request != 1)) {
                    error = false;
                    return -1;
                }
            }
        }
    }

    return 0;

}
