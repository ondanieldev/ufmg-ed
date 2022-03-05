#include <iostream>

using namespace std;

int main()
{
    int testCases;
    string input;

    // get number of test cases
    cin >> testCases;

    for (int i = 0; i < testCases; ++i)
    {
        // get each input
        cin >> input;

        // removing sands
        string fragments = "";
        for (int i = 0; i < input.length(); ++i)
        {
            if (input[i] != '.')
            {
                fragments += input[i];
            }
        }

        // collecting diamonds
        string aux = fragments;
        int diamonds = 0;
        int newDiamonds = 0;
        while (1)
        {
            fragments = aux;
            aux = "";
            for (int i = 0; i < fragments.length(); ++i)
            {
                if (fragments[i] == '<' && fragments[i + 1] == '>')
                {
                    newDiamonds++;
                    i++;
                }
                else
                {
                    aux += fragments[i];
                }
            }
            if (newDiamonds == 0)
            {
                break;
            }
            diamonds += newDiamonds;
            newDiamonds = 0;
        }

        // showing result for each input
        cout << diamonds << endl;
    }

    return 0;
}