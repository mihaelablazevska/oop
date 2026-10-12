//Oddelenie zadaca od cas 30.09.2026
#include <bits/stdc++.h>
using namespace std;

struct Ucenik
{
    char ime[50];
    uint8_t ocenki[5];
};

int main()
{
    Ucenik u[5];
    char s[50];
    int k;
    float max = 0;
    uint8_t idx = -1;
    for(int i = 0; i < 5; i++)
    {
        cin >> s;
        strcpy(u[i].ime, s);
        int prosek = 0;
        for(int j = 0; j < 5; j++)
        {
            cin >> k;
            u[i].ocenki[j] = k;
        }
    }
    
    for(int i = 0; i < 5; i++)
    {
        float prosek = 0;
        for(int j = 0; j < 5; j++)
        {
            prosek += u[i].ocenki[j];
        }
        prosek /= 5;
        if(prosek > max)
        {
            max = prosek;
            idx = i;
        }
    }
    cout << "Najdobriot ucenik e " << u[idx].ime << " so prosek " << max;
}