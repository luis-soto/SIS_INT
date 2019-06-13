#include <iostream>
#include <string>

using namespace std;

int main()
{
    const int count = 3;
    string dist[3] = {"P", "M", "L"};

    cout << "D\tC\tE" << endl;

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            for (int k = 0; k < count; k++)
            {
                cout << dist[i] << "\t" <<  dist[j]<< "\t"  << dist[k] << "\t=>\t" << endl;
            }
        }
    }
    return 0;
}