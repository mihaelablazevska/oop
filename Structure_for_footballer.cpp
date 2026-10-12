#include <iostream>
using namespace std;

struct date_of_birth
{
    int date;
    int month;
    int year;
};

struct footballer
{
    char name_and_surname[50];
    char club_name[20];
    date_of_birth db;
};


void copy_string(char *where, char *from)
{
    while(*from)
    {
        *where = *from;
        where++;
        from++;
    }
    *where  = '\0';
}

int main()
{
    footballer f;
    date_of_birth db;
    copy_string(f.name_and_surname, "Goran Pandev");
    copy_string(f.club_name, "Inter Milan");
    date_of_birth i;
    int d = 27;
    int m = 07;
    int y = 1983;
    f.db.date = d;
    f.db.month = m;
    f.db.year = y;

    footballer *p = &f;
    cout<< p->name_and_surname << endl;
    cout << p->club_name <<endl;
    cout << p->db.date<< " " << p->db.month << " " << p->db.year;
}