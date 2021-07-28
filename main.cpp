#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

void compoundSetOps();

int * unite(int * cardinalities, int ** sets, int index, int cremant, int * result);
int * intersect(int * cardinality, int ** sets, int index, int cremant, int * result);

int * convert(int cardinality, int num);
void cartesian(int * cardinality, int ** sets);

void testCommutative(string op);
void testAssociative(string op);
void testDistributive(string op);

int main()
{
    cout << "This program computes following basic set operations. " << endl << endl;

    cout << "Which operation would you like to perform? " << endl << endl;
    cout << "(1) (A union B) intersection (C union D)" << endl;
    cout << "(2) Powerset " << endl;
    cout << "(3) Cartesian or Cross Product " << endl;
    cout << "(4) Commutative Property Proof: A union B = B union A  OR  A intersection B = B intersection A" << endl;
    cout << "(5) Associative Property Proof: (A union B) union C = A union (B union  C) " << endl;
    cout << "\t\t\t\t(A intersection B) intersection C = A intersection (B intersection C)" << endl;
    cout << "(6) Test Distributive Property: A union (B intersection C) = (A union B) intersection (A union C) " << endl;
    cout << "\t\t\t\tA intersection (B union C) = (A intersection B) union (B intersection C)" << endl;

    cout << endl << "Enter your choice: ";
    int choice;
    cin >> choice;

    cout << endl;

    int * cardinality; int * bits;
    int ** setting;
    char alpha;
    int num, count, counter;
    int * resultant;
    int * temp;

    switch(choice)
    {
        case 1:
            compoundSetOps();
            break;

        case 2:
            cout << endl << "Enter the number of elements in the set: ";

            cin >> num;

            cardinality = new int[1];
            cardinality[0] = num;

            resultant = new int[num];

            for(count = 0; count < cardinality[0]; count++)
            {
                cout << "Enter element#" << count+1 << ": ";

                for(cin >> num; num > 9; cin >> num)
                    cout << "Sorry! The element must range between 0-9. Try again!" << endl;

                resultant[count] = num;
            }

            bits = new int[cardinality[0]];

            cout << endl << "Powerset: " << endl << "{ {}, ";
            for(count = 1; count < pow(2, cardinality[0]); count++)
            {
                bits = convert(cardinality[0], count);

                cout << "{";
                for(counter = 0; counter < cardinality[0]; counter++)
                    if(bits[counter])
                        cout << resultant[counter] << ",";

                cout << "\b}, ";
            }

            cout << "\b\b }" << endl;
            break;

        case 3:
            setting = new int*[2];
            cardinality = new int[2];

            for(alpha = 'A'; alpha < 'C'; alpha++)
            {
                cout << endl << "Enter the cardinality for Set " << alpha << ": ";
                cin >> num;
                setting[ (int)(alpha - 65) ] = new int[num];

                cardinality[ (int)(alpha - 65) ] = num;

                for(count = 0; count < cardinality[ (int)(alpha - 65) ]; count++ )
                {
                    cout << "Enter element#" << count+1  << ": ";
                    cin >> num;

                    setting[ (int)(alpha - 65) ][count] = num;
                }
            }

            cartesian(cardinality, setting);

            break;

        case 4:
            cout << "Which set operation for the commutative property do you want to test? (1) Union (2) Intersection " << endl << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if(choice-1)
                testCommutative("intersection");
            else
                testCommutative("union");

            break;

        case 5:
            cout << "Which set operation for the associative property do you want to test? (1) Union (2) Intersection " << endl << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if(choice-1)
                testAssociative("intersection");
            else
                testAssociative("union");

            break;

        case 6:
            cout << "Which operation do you want to test for the distributive property? " << endl;
            cout << "(1) A union (B intersection C) = (A union B) intersection (A union C) " << endl;
            cout << "(2) A intersection (B union C) = (A intersection B) union (B intersection C)" << endl << endl;

            cout << "Enter your choice: ";
            cin >> choice;
            if(choice-1)
                testDistributive("intersection");
            else
                testDistributive("union");

            break;

        default:
            cout << "Sorry, there is an error in your choice of input. " << endl;
    }

    cout << endl << "Thank you for your using this program. " << endl;

    return 0;
}

int * unite(int * cardinality, int ** sets, int index, int cremant, int * result)
{
    int count;
    int temp[ cardinality[index] + cardinality[index+cremant] ];

    for(count = 0; count < cardinality[index]; count++)
        temp[count] = sets[index][count];

    int counting = count;
    for(count = 0; count < cardinality[index+cremant]; count++)
    {
        bool existence = false;

        for(int counter = 0; counter < cardinality[index]; counter++)
        {
            if(sets[index+cremant][count] == sets[index][counter])
            {
                existence = true;
                break;
            }
        }
        if(!existence)
            temp[counting++] = sets[index+cremant][count];
    }

    result = new int[counting];

    for(count = 0; count < counting; count++)
        result[count] = temp[count];

    return result;
}

int * intersect(int * cardinality, int ** sets, int index, int cremant, int * result)
{
    int count, counter, counting = 0;
    result = new int[ (cardinality[0] < cardinality[1]) ? cardinality[0]: cardinality[1] ];

    for(count = 0; count < cardinality[index]; count++)
        for(counter = 0; counter < cardinality[index + cremant]; counter++)
            if(sets[index][count] == sets[index + cremant][counter])
                result[counting++] = sets[index][count];

    return result;
}

int * convert(int cardinality, int num)
{
    int * bits = new int[cardinality];
    int count;
    for(count = 0; num != 0; num / 2)
    {
        bits[count++] = num % 2;
        num /= 2;
    }

    for(int counter = count; counter < cardinality; counter++)
        bits[counter] = 0;

    return bits;
}

void cartesian(int * cardinality, int ** sets)
{
    int * resultant = new int[ (cardinality[0] * cardinality[1]) ];

    cout << endl << "Cartesian Product - A x B: " << endl << "{ ";
    for(int count = 0; count < cardinality[0]; count++)
    {
        for(int counter = 0; counter < cardinality[1]; counter++)
            cout << "{" << sets[0][count] << ", " << sets[1][counter] << "}, ";
    }
    cout << "\b\b } " << endl;
}

void testCommutative(string op)
{
    int ** setting = new int*[3];
    int send;
    setting[0] = new int[4];
    setting[1] = new int[5];

    setting[0][0] = 1; setting[0][1] = 3; setting[0][2] = 5; setting[0][3] = 2;
    setting[1][0] = 1; setting[1][1] = 4; setting[1][2] = 6; setting[1][3] = 8; setting[1][4] = 5;

    int cardinality[2] = {4, 5};

    cout << "Testing Commutative Property: A " << op << " B = " << " B " << op << " A " << endl;
    cout << "Set A: {1, 3, 5, 2}\tSet B: {1, 4, 6, 8, 5}" << endl << endl;

    cout << "Solving for A " << op << " B as Set AB" << endl;

    int sz = (op == "union" ? 7 : 2);

    //Solving for AB
    int * result;
    if( op == "union")
        result = unite(cardinality, setting, 0, 1, result);
    else
        result = intersect(cardinality, setting, 0, 1, result);

    setting[2] = new int[7]; int count;

    for(count = 0; count < sz; count++)
        setting[2][count] = result[count];

    cout << "AB = {";
    for(count = 0; count < sz; count++)
        cout << setting[2][count] << ",";
    cout << "\b}" << endl << endl;
    //Solved for AB

    //Solving for BA
    cout << "Solving for B " << op << " A as Set BA" << endl;
    if( op == "union" )
        result = unite(cardinality, setting, 1, -1, result);
    else
        result = intersect(cardinality, setting, 1, -1, result);

    cout << "BA = {";
    for(count = 0; count < sz; count++)
        cout << result[count] << ",";
    cout << "\b}" << endl << endl;
    //Solved for BA

    cout << "Showing that AB = BA ..." << endl << endl << "AB = {";
    for(count = 0; count < sz; count++)
        cout << result[count] << ", ";

    cout << "\b\b}" << endl << "BA = {";
    for(count = 0; count < sz; count++)
        cout << setting[2][count] << ", ";

    cout << "\b\b}" << endl << endl;

    cout << "Commutative property of " << op << " has been proven. " << endl;
}

void testAssociative(string op)
{
    int ** setting = new int*[6];

    setting[0] = new int[4];
    setting[1] = new int[5];
    setting[2] = new int[4];

    setting[0][0] = 1; setting[0][1] = 3; setting[0][2] = 5; setting[0][3] = 2;
    setting[1][0] = 1; setting[1][1] = 4; setting[1][2] = 6; setting[1][3] = 8; setting[1][4] = 5;
    setting[2][0] = 1; setting[2][1] = 4; setting[2][2] = 6; setting[2][3] = 8;

    int cardinality[6] = {4, 5, 4};

    cout << "Testing Associative Property: A " << op << " B = " << " B " << op << " A " << endl;
    cout << "Set A: {1, 3, 5, 2}\t\tSet B: {1, 4, 6, 8, 5}\t\tSet C: {1, 4, 6, 8}" << endl << endl;

    int sz = (op == "union" ? 7 : 2);
    int count;

    cout << "Solving for A " << op << " B as Set AB" << endl << "AB = {";
    int * result;

    if( op == "union" )
        result = unite(cardinality, setting, 0, 1, result);
    else
        result = intersect(cardinality, setting, 0, 1, result);

    setting[3] = new int[sz];
    cardinality[3] = sz;

    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[3][count] = result[count];
    }
    cout << "\b\b}" << endl << endl;

    cout << "Solving for AB " << op << " C as AB-C" << endl << "AB-C = {";
    if( op == "union" )
        result = unite(cardinality, setting, 3, -1, result);
    else
    {
        result = intersect(cardinality, setting, 3, -1, result);
        sz = 1;
    }

    setting[5] = new int[sz];
    cardinality[5] = sz;
    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[5][count] = result[count];
    }
    cout << "\b\b}" << endl << endl;

    cout << "Solving for B " << op << " C as Set BC" << endl << "BC = {";
    if(op == "union")
    {
        sz = 5;
        result = unite(cardinality, setting, 1, 1, result);
    }
    else
    {
        sz = 4;
        result = intersect(cardinality, setting, 1, 1, result);
    }

    setting[4] = new int[sz];
    cardinality[4] = sz;
    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[4][count] = result[count];
    }

    cout << "\b\b}" << endl << endl << "Solving for BC " << op << " A as Set BC-A" << endl << "BC-A = {";
    //What goes on here?

    if(op == "union")
    {
        sz = 7;
        result = unite(cardinality, setting, 0, 4, result);
    }
    else
    {
        sz = 1;
        result = intersect(cardinality, setting, 0, 4, result);
    }

    for(count = 0; count < sz; count++)
        cout << result[count] << ", ";

    cout << "\b\b}" << endl << endl << "Showing ABC = BCA ... " << endl << endl << "AB-C = {";
    for(count = 0; count < sz; count++)
        cout << setting[5][count] << ", ";

    cout << "\b\b}" << endl << "BC-A = {";

    for(count = 0; count < sz; count++)
        cout << result[count] << ", ";

    cout << "\b\b}" << endl << endl << "Associative property of " << op << " has been proven. " << endl << endl;
}

void testDistributive(string op)
{
    int ** setting = new int*[7];
    string secop = (op == "union" ? "intersection" : "union");

    setting[0] = new int[4];
    setting[1] = new int[5];
    setting[2] = new int[4];

    setting[0][0] = 1; setting[0][1] = 3; setting[0][2] = 5; setting[0][3] = 2;
    setting[1][0] = 1; setting[1][1] = 4; setting[1][2] = 6; setting[1][3] = 8; setting[1][4] = 5;
    setting[2][0] = 1; setting[2][1] = 4; setting[2][2] = 6; setting[2][3] = 8;

    int cardinality[7] = {4, 5, 4};

    cout << "Testing Distributive Property: (1) A " << op << "(B " << secop << " C) = (A " << op << " B) " << secop << " (A " << op << " C) " << endl;
    cout << "Set A: {1, 3, 5, 2}\t\tSet B: {1, 4, 6, 8, 5}\t\tSet C: {1, 4, 6, 8}" << endl << endl;

    int sz = (op == "union" ? 4 : 5);
    int count;

    //First test commence
    cout << "Solving for B " << secop << " C as Set BC" << endl << "BC = {";
    int * result;

    if( secop == "union" )
        result = unite(cardinality, setting, 1, 1, result);
    else
        result = intersect(cardinality, setting, 1, 1, result);

    setting[3] = new int[sz];
    cardinality[3] = sz;

    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[3][count] = result[count];
    }
    cout << "\b\b}" << endl << endl;
    //First test complete

    //Second test commence
    cout << "Solving for A " << op << " BC as Set A-BC" << endl << "A-BC = {";
    if( op == "union" )
    {
        sz = 7;
        result = unite(cardinality, setting, 0, 3, result);
    }
    else
    {
        sz = 2;
        result = intersect(cardinality, setting, 0, 3, result);
    }

    setting[4] = new int[sz];
    cardinality[4] = sz;

    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[4][count] = result[count];
    }
    cout << "\b\b}" << endl << endl;
    //Second test complete

    //Third test commence
    cout << "Solving for A " << op << " B as Set AB" << endl << "AB = {";

    if( op == "union" )
    {
        sz = 7;
        result = unite(cardinality, setting, 0, 1, result);
    }
    else
    {
        sz = 2;
        result = intersect(cardinality, setting, 0, 1, result);
    }
    setting[5] = new int[sz];
    cardinality[5] = sz;

    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[5][count] = result[count];
    }
    cout << "\b\b}" << endl << endl;
    //Third test complete

    //Fourth test commence
    cout << "Solving for A " << op << " C as Set AC" << endl << "AC = {";

    if( op == "union" )
    {
        sz = 7;
        result = unite(cardinality, setting, 0, 2, result);
    }
    else
    {
        sz = 1;
        result = intersect(cardinality, setting, 0, 2, result);
    }
    setting[6] = new int[sz];
    cardinality[6] = sz;

    for(count = 0; count < sz; count++)
    {
        cout << result[count] << ", ";
        setting[6][count] = result[count];
    }
    cout << "\b\b}" << endl << endl;
    //Fourth test complete

    //Fifth test commence
    cout << "Solving for AB " << secop << " AC as Set AB-AC" << endl << "AB-AC = {";
    if( op == "union" )
    {
        sz = 7;
        result = unite(cardinality, setting, 5, 1, result);
    }
    else
    {
        sz = 2;
        result = intersect(cardinality, setting, 5, 1, result);
    }

    for(count = 0; count < sz; count++)
        cout << result[count] << ", ";
    cout << "\b\b}" << endl << endl;
    //Fifth test complete

    //Proof commence
    cout << endl << "Showing that A-BC = AB-AC ... " << endl << "A-BC = {";

    for(count = 0; count < sz; count++)
        cout << setting[4][count] << ", ";

    cout << "\b\b}" << endl << "AB-AC = {";

    for(count = 0; count < sz; count++)
        cout << result[count] << ", ";

    cout << "\b\b}" << endl << endl;
    //Proof complete

    cout << "The distributive property has been proven. " << endl << endl;
}

void compoundSetOps()
{
    int ** setting = new int*[6];

    setting[0] = new int[4];
    setting[1] = new int[5];
    setting[2] = new int[4];
    setting[3] = new int[4];
    setting[4] = new int[7];
    setting[5] = new int[6];

    int cardinality[6] = {4, 5, 4, 5, 7, 6};

    setting[0][0] = 1; setting[0][1] = 3; setting[0][2] = 5; setting[0][3] = 2;
    setting[1][0] = 1; setting[1][1] = 4; setting[1][2] = 6; setting[1][3] = 8; setting[1][4] = 5;
    setting[2][0] = 1; setting[2][1] = 4; setting[2][2] = 6; setting[2][3] = 8;
    setting[3][0] = 1; setting[3][1] = 2; setting[3][2] = 6; setting[3][3] = 10;

    cout << "Set A: {1, 3, 5, 2}\t\tSet B: {1, 4, 6, 8, 5}\t\tSet C: {1, 4, 6, 8}\t\tSet D: {1, 2, 6, 10}" << endl << endl;

    cout  << "Solving for (A union C) intersection (A union D) " << endl << endl;

    int * result;
    int count;

    cout << "A union C = {";

    result = unite(cardinality, setting, 0, 2, result);
    for(count = 0; count < 7; count++)
    {
        cout << result[count] << ", ";
        setting[4][count] = result[count];
    }
    cout << "\b\b}" << endl;

    cout << "A union D = {";
    result = unite(cardinality, setting, 0, 3, result);
    for(count = 0; count < 6; count++)
    {
        cout << result[count] << ", ";
        setting[5][count] = result[count];
    }
    cout << "\b\b}" << endl;

    cout << endl;

    cout << "(A union C) intersection (A union D) = {";

    result = intersect(cardinality, setting, 4, 1, result);
    for(count = 0; count < 5; count++)
        cout << result[count] << ", ";

    cout << "\b\b}" << endl << endl;
}
