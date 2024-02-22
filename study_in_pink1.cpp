#include "study_in_pink1.h"
#define MAX_ELEMENT 10
bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    // TODO: Complete this function
    // handle edge cases
    ensureExpRange(exp1);
    ensureExpRange(exp2);
    // if e1 is not in range [0, 99], return -999
    if (e1 < 0 || e1 > 99)
        return -99;
    
    // in the case e1 is in range [0, 3], Sherlock explains how he knows Watson has 
    // been to Afghanistan, and the value of exp2 is updated as follows:
    if (e1 >= 0 && e1 <= 3)
    {
        switch (e1)
        {
            case 0:
                exp2 += 29;
                break;
            case 1:
                exp2 += 45;
                break;
            case 2:
                exp2 += 75;
                break;
            case 3:
                exp2 += 29 + 45 + 75;   // 149
                break;
            default:
                break;
        }
        // calculate Sherlock's decsion 
        int D = e1 * 3 + exp1 * 7;
        // if D is an even number, his EXP wll be updated as follows:
        if (D % 2 == 0)
        {
            double dou_exp1 = (double) exp1 + D / 200.0;
            exp1 = ceil(dou_exp1);
        }
        // if D is an odd number, his EXP wll be updated as follows:
        else
        {
            double dou_exp1 = (double) exp1 - D / 100.0;
            exp1 = ceil(dou_exp1);
        }
    }
    // in the case e1 is in range [4, 99], Sherlock explains how he knows Watson has
    // a brother, and the value of exp2 is updated as follows: 
    if (e1 >= 4 && e1 <= 99)
    {
        if (e1 >= 4 && e1 <= 19)
        {
            double dou_exp2 = (double) exp2 + ( e1 / 4.0 ) + 19;
            exp2 = ceil(dou_exp2);
        }    
        else if (e1 >= 20 && e1 <= 49)
        {
            double dou_exp2 = (double) exp2 + ( e1 / 9.0 ) + 21;
            exp2 = ceil(dou_exp2);
        }
        else if (e1 >= 50 && e1 <= 65)
        {
            double dou_exp2 = (double) exp2 + ( e1 / 16.0 ) + 17;
            exp2 = ceil(dou_exp2);
        } 
        else if (e1 >= 66 && e1 <= 79)
        {
            // Sherlock explain information 1
            double dou_exp2 = (double) exp2 + ( e1 / 4.0 ) + 19;
            exp2 = ceil(dou_exp2);
            if (exp2 > 200)
            {
                double dou_exp2 = (double) exp2 + ( e1 / 9.0 ) + 21;
                exp2 = ceil(dou_exp2);               
            }
        }
        else if (e1 >= 80 && e1 <= 99)
        {
            // Sherlock explain information 1 and 2
            double dou_exp2 = (double) exp2 + ( e1 / 4.0 ) + 19;
            exp2 = ceil(dou_exp2);   
            dou_exp2 = (double) exp2 + ( e1 / 9.0 ) + 21;
            exp2 = ceil(dou_exp2);            
            if (exp2 > 400)
            {
                // Sherlock explain information 3
                double dou_exp2 = (double) exp2 + ( e1 / 16.0 ) + 17;
                exp2 = ceil(dou_exp2);
                dou_exp2 = (double) exp2 * 1.15;
                exp2 = ceil(dou_exp2);
            }  
        }
        // reduce exp1 by an amount of e1
        exp1 -= e1;       
    }

    // ensure exp1 and exp2 are in range [0, 600]
    ensureExpRange(exp1);
    ensureExpRange(exp2);


    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    // TODO: Complete this function
    // handle edge cases
    if (E2 < 0 || E2 > 99)
        return -99;
    ensureExpRange(EXP1);
    ensureHPRange(HP1);
    ensureMRange(M1);
    // road 1
    int S = nearestPerfectSquare(EXP1);
    // probability for Sherlock to find the suitcase 
    double P1 = 0.0;    
    double P2 = 0.0;
    double P3 = 0.0;
    // probability for Sherlock to find the suitcase in road 1
    if (EXP1 >= S)
        P1 = 100.0;
    else
    {
        P1 = (((double) EXP1 / S + 80) / 123.0) * 100.0;
    }
        
    // road 2
    double dou_halfOfInitiM = (double) M1 / 2.0;
    int halfOfInitM = ceil(dou_halfOfInitiM);
    // if E2 is an odd number
    if (E2 % 2 != 0)
    {
        while (M1 > halfOfInitM)
        {
            // drink or eat
            if (HP1 < 200)
            {   // eat
                double dou_HP1 = (double) HP1 * 1.3;
                HP1 = ceil(dou_HP1);
                M1 -= 150;
            }
            else 
            {   // drink
                double dou_HP1 = (double) HP1 * 1.1;
                HP1 = ceil(dou_HP1);
                M1 -= 70;
            }        
            if (M1 < halfOfInitM)
                goto end;
            // rent a taxi or carriage
            if (EXP1 < 400)
                M1 -= 200; // take a taxi
            else 
                M1 -= 120; // take a carriage
            double dou_exp1 = (double) EXP1 * 1.13;
            EXP1 = ceil(dou_exp1);
            if (M1 < halfOfInitM)
                goto end;            
            // meet a homeless person
            if (EXP1 < 300)
                M1 -= 100;
            else 
                M1 -= 120;
            dou_exp1 = (double) EXP1 * 0.9;
            EXP1 = ceil(dou_exp1);
            if (M1 < halfOfInitM)
                goto end;
        }
        // cout << "M1: " << M1 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << endl;
    }
    else 
    {
        // just do the same thing as the previous case one time
            // drink or eat
            if (HP1 < 200) 
            {   // eat
                double dou_HP1 = (double) HP1 * 1.3;
                HP1 = ceil(dou_HP1);
                M1 -= 150;
            }
            else if (HP1 >= 200)
            {   // drink
                double dou_HP1 = (double) HP1 * 1.1;
                HP1 = ceil(dou_HP1);
                M1 -= 70;
            }
            if (M1 <= 0)
                goto end;

            // rent a taxi or carriage
            if (EXP1 < 400 && M1 >= 200)
                M1 -= 200; // take a taxi
            else if (EXP1 >= 400 && M1 >= 120)
                M1 -= 120; // take a carriage
            double dou_exp1 = (double) EXP1 * 1.13;
            EXP1 = ceil(dou_exp1);
            if (M1 <= 0)
                goto end;

            // meet a homeless person
            if (EXP1 < 300 && M1 >= 100)
                M1 -= 100;
            else if (EXP1 >= 300 && M1 >= 120)
                M1 -= 120;
            dou_exp1 = (double) EXP1 * 0.9;
            EXP1 = ceil(dou_exp1);       
    }
end:
    // reduce HP by 17% and increase EXP by 17%
    double dou_HP1 = (double) HP1 * 0.83;
    HP1 = ceil(dou_HP1);
    double dou_exp1 = (double) EXP1 * 1.17;
    EXP1 = ceil(dou_exp1);

    // probability for Sherlock to find the suitcase in road 2
    int S2 = nearestPerfectSquare(EXP1);
    if (EXP1 >= S2)
        P2 = 100.0;
    else
    {
        P2 = ((double) EXP1 / S2 + 80) / 123.0;
    }
        
    // road 3
    int P[] = {32,47,28,79,100,50,22,83,64,11};
    int i = caltIndexRoad3(E2);
    // probability for Sherlock to find the suitcase in road 3
    P3 = P[i];

    if (P1 == 100.0 && P2 == 100.0 && P3 == 100.0)
    {
        double dou_exp1 = (double) EXP1 * 0.75;
        EXP1 = ceil(dou_exp1);
    }
    else 
    {
        cout << "P1: " << P1 << ", P2: " << P2 << ", P3: " << P3 << endl;
        double avgProb = (P1 + P2 + P3) / 3.0;
        cout << avgProb << endl;
        if (avgProb < 50.0)
        {
            double dou_hp = (double) HP1 * 0.85;
            HP1 = ceil(dou_hp);
            double dou_exp1 = (double) EXP1 * 1.15;
            EXP1 = ceil(dou_exp1);
        }
        else 
        {
            double dou_hp = (double) HP1 * 0.90;
            HP1 = ceil(dou_hp);
            double dou_exp1 = (double) EXP1 * 1.20;
            EXP1 = ceil(dou_exp1);          
        }
    } 
    // Ensure HP1, EXP1, M1 are in range
    ensureHPRange(HP1);
    ensureExpRange(EXP1);
    ensureMRange(M1);

    return HP1 + EXP1 + M1;
}

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
    int taxiScore[MAX_ELEMENT][MAX_ELEMENT] = {0};
    int snwScore[MAX_ELEMENT][MAX_ELEMENT] = {0};
    // handle edge cases
    ensureExpRange(EXP1);
    ensureHPRange(HP1);
    ensureHPRange(HP2);
    ensureExpRange(EXP2);
    if (E3 < 0 || E3 > 99)
        return -99;
    // calculate taxiScore
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        for (int j = 0; j < MAX_ELEMENT; j++)
        {
            taxiScore[i][j] = ((E3 * j) + (i * 2)) * (i-j);
        }
    }
    // calculate snwScore
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        for (int j = 0; j < MAX_ELEMENT; j++)
        {
            snwScore[i][j] = maxDiagonal(taxiScore, i, j, taxiScore[i][j]);
        }
    }
    // calculate meeting point 
    int meetX = 0, meetY = 0;
    // meetX equals to number of points that has value greater than E3 * 2
    // meetY equals to # of points that has value smaller than - E3
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        for (int j = 0; j < MAX_ELEMENT; j++)
        {
            if (taxiScore[i][j] > E3 * 2)
                meetX++;
            if (taxiScore[i][j] < -E3)
                meetY++;
        }
    }
    // if meetX and meetY is two-digit nums, keep repeating summing two digits
    // until its a single-digit number
    from1To2Digits(meetX);
    from1To2Digits(meetY);

    // they don't catch the taxi 
    if (abs(taxiScore[meetX][meetY]) > snwScore[meetX][meetY])
    {   // Sherlock and Watson will be decreased by 10% of their HP
        // and 12% of their EXP
        double dou_exp1 = (double) EXP1 * 0.88;
        EXP1 = ceil(dou_exp1 - 0.0000001);  // to avoid the floating point error, subtract a small value
        double dou_exp2 = (double) EXP2 * 0.88;
        EXP2 = ceil(dou_exp2 - 0.0000001);
        double dou_hp1 = (double) HP1 * 0.90;
        HP1 = ceil(dou_hp1 - 0.0000001);
        double dou_hp2 = (double) HP2 * 0.90;
        HP2 = ceil(dou_hp2 - 0.0000001);

        // ensure HP1, EXP1, HP2, EXP2 are in range
        ensureExpRange(EXP1);
        ensureExpRange(EXP2);
        ensureHPRange(HP1);
        ensureHPRange(HP2);

        return taxiScore[meetX][meetY];
    }
    else 
    {   // they catch the taxi
        // Sherlock and Watson will be increased by 10% of their HP
        // and 12% of their EXP
        double dou_exp1 = (double) EXP1 * 1.12;
        EXP1 = ceil(dou_exp1 - 0.0000001);  // to avoid the floating point error, subtract a small value
        double dou_exp2 = (double) EXP2 * 1.12;
        EXP2 = ceil(dou_exp2 - 0.0000001);
        double dou_hp1 = (double) HP1 * 1.10;
        cout << dou_hp1 << endl;
        HP1 = ceil(dou_hp1 - 0.0000001);
        double dou_hp2 = (double) HP2 * 1.10;
        HP2 = ceil(dou_hp2 - 0.0000001);    

        // ensure HP1, EXP1, HP2, EXP2 are in range
        ensureExpRange(EXP1);
        ensureExpRange(EXP2);
        ensureHPRange(HP1);
        ensureHPRange(HP2);

        return snwScore[meetX][meetY];
    }
    return -1;
}

// Task 4
int checkPassword(const char * s, const char * email) {
    // TODO: Complete this function
    bool containedSpecialChar = false;
    size_t found = string(email).find("@");
    // find the substring before the @ character
    string se = string(email, 0, found);
    // length of s violations
    if (strlen(s) < 8)
        return -1;
    if (strlen(s) > 20)
        return -2;
    // se violations
    if (string(s).find(se) != string::npos)
        return -(300 + string(s).find(se));
    // 2 consecutive characters violations
    if (moreThan2ConsecutiveChar(s) != -1)
        return -(400 + moreThan2ConsecutiveChar(s));

    // each character in s can only be a number or a lowercase or
    // uppercase letter or a special character: @ # $ % !
    for (int i = 0, n = strlen(s); i < n; i++)
    {   
        // if s[i] is not a number or a letter or a special character
        if (!isdigit(s[i]) || !isalpha(s[i]) || s[i] != '@' || s[i] != '#' || s[i] != '$' || s[i] != '%' || s[i] != '!')
            return i;
        // if s[i] is a special character
        if (s[i] == '@' || s[i] == '#' || s[i] == '$' || s[i] == '%' || s[i] == '!')
            containedSpecialChar = true;
    }

    // special characters violations
    if (!containedSpecialChar)
        return -5;
    // no violation i.e valid password
    return -10;
}

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    int mostFrequentPw = 0;
    int numOFrequentPw = 1;
    string mostFrequentPwStr = "";
    // TODO: Complete this function
    for (int i = 0; i < num_pwds; i++)
    {
        for (int j = 0; j < num_pwds; j++)
        {
            if (strcmp(arr_pwds[i], arr_pwds[j]) == 0 && i != j)
                numOFrequentPw++;
        }
        if (numOFrequentPw > mostFrequentPw)
        {
            mostFrequentPw = numOFrequentPw;
            mostFrequentPwStr = arr_pwds[i];
        }
        else if (numOFrequentPw == mostFrequentPw)
        {
            // if two passwords have the same frequency, take the one that is longer
            if (strlen(arr_pwds[i]) > mostFrequentPwStr.length())
                mostFrequentPwStr = arr_pwds[i];
        }
        numOFrequentPw = 1;
    }
    // return the first occure of the most frequent password
    for (int i = 0; i < num_pwds; i++)
    {
        if (strcmp(arr_pwds[i], mostFrequentPwStr.c_str()) == 0)
            return i;
    }
    return -1;
}

// implement additional functions
void ensureExpRange(int & exp)
{
    if (exp < 0)
        exp = 0;
    else if (exp > 600)
        exp = 600;
}
void ensureHPRange(int & hp)
{
    if (hp < 0)
        hp = 0;
    else if (hp > 666)
        hp = 666;
}   
void ensureMRange(int & m)
{
    if (m < 0)
        m = 0;
    else if (m > 3000)
        m = 3000;

}
int nearestPerfectSquare(int n)
{
    if (isPerfectSquare(n))
        return n;
    
    int aboveN = -1, belowN = -1;
    int i = 0;
    // finding first square number greater than N
    i = n + 1;
    while (true)
    {
        if (isPerfectSquare(i))
        {
            aboveN = i;
            break;
        }
        i++;
    }
    // finding first square number less than N
    i = n - 1;
    while (true)
    {
        if (isPerfectSquare(i))
        {
            belowN = i;
            break;
        }
        i--;
    }

    int diff1 = aboveN - n;
    int diff2 = n - belowN;
    if (diff1 < diff2)
        return aboveN;
    return belowN;
}
bool isPerfectSquare(int n)
{
    if (sqrt(n) - floor(sqrt(n)) == 0)
        return true;
    return false;
}
int caltIndexRoad3(const int & E2)
{
    if (E2 >= 0 && E2 <= 9)
        return E2;
    int firstNum = E2 / 10;
    int secondNum = E2 % 10;
    return (firstNum + secondNum) % 10;
}
int maxDiagonal(int arr[10][10], int i, int j, int maxVal)
{
    // current index
    int ci = i, cj = j;
    // North - West direction
    while (ci >= 0 && ci < MAX_ELEMENT && cj >= 0 && cj < MAX_ELEMENT)
    {
        if (arr[ci][cj] > maxVal)
            maxVal = arr[ci][cj];
        ci--;
        cj--;
    }
    // reset ci, cj
    ci = i, cj = j;
    // North - East direction 
    while (ci >= 0 && ci < MAX_ELEMENT && cj >= 0 && cj < MAX_ELEMENT)
    {
        if (arr[ci][cj] > maxVal)
            maxVal = arr[ci][cj];
        ci--;
        cj++;
    }
    // reset ci, cj
    ci = i, cj = j;
    // South - West direction
    while (ci >= 0 && ci < MAX_ELEMENT && cj >= 0 && cj < MAX_ELEMENT)
    {
        if (arr[ci][cj] > maxVal)
            maxVal = arr[ci][cj];
        ci++;
        cj--;
    }  
    // reset ci, cj
    ci = i, cj = j;
    // South - East direction
    while (ci >= 0 && ci < MAX_ELEMENT && cj >= 0 && cj < MAX_ELEMENT)
    {
        if (arr[ci][cj] > maxVal)
            maxVal = arr[ci][cj];
        ci++;
        cj++;
    }

    return abs(maxVal);
}
void from1To2Digits(int & n)
{
    if (n < 10)
        return;
    int sum = 0;
    while (n >= 10)
    {
        sum = n % 10 + n / 10;
        n = sum;
    }
}
int moreThan2ConsecutiveChar(string s)
{
    int count = 1;
    for (int i = 0, n = s.length(); i < n; i++)
    {
        if (s[i] == s[i+1])
            count++;
        else 
            count = 1;
        if (count > 2)
        // return the index of the first character of the first 3 consecutive characters
            return i - 1;
    }
    return -1;
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
/////////////////////   ///////////////////////////

