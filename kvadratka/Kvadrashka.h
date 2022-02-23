struct test_data {

    double a;
    double b;
    double c;
    int nRootsRef;
    double root_1Ref;
    double root_2Ref;

};

//! Constant for comparing of double numbers
const double EPSILON = 10E-12;

//! An enum CASES.
/*! Description: contain value for every case of number of roots*/
enum CASES {
    INF_ROOTS = -1,
    NO_ROOTS  = 0,
    ONE_ROOT  = 1,
    TWO_ROOTS = 2
};


struct test_data Mass[8] = {
    {1.0,-5.0, 6.0, TWO_ROOTS, 2.0, 3.0},
    {1.0, -3.0, 2.0, TWO_ROOTS, 1.0, 2.0},
    {1.0, -2.0, 1.0, ONE_ROOT, 1.0, 1.0},
    {1.0, 2.0, 5.0, NO_ROOTS, 0, 0},
    {0.0, 2.0, 1.0, ONE_ROOT, -0.5, 0},
    {0.0, 1.0, 3.0, ONE_ROOT, -3.0, 0},
    {0.0, 0.0, 1.0, NO_ROOTS, 0, 0},
    {0.0, 0.0, 0.0, INF_ROOTS, 0, 0}
};


int Is_Equal(double, double);
int Lets_Start_Program (int *request);
int Solve_Square(double a, double b, double c, double *root_1, double *root_2);
int Run_UnitTest(void);
int Unit_Test_Solve_Square( struct test_data Mass);

void If_Strive_To_Zero(double *, double *);
void Clear_Buffer(void);
void Print_Result_UnitTest(int);
void Print_Roots(int nRoots, double *root_1, double *root_2);
void Print_Intro(void);
void Main_Part(void);
void Read_Input(double *a, int coef_number);
void Transfom_Coefs (double * a, double * b, double * c);
