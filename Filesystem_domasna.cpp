// Homework for 21.10.2026
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct File 
{
    string name;
    string extension;
    uint64_t byteSize;
};

string getFullFilename(File &f) 
{ 
    return f.name + '.' + f.extension;
}

struct Directory {
    string name;
    vector<File *> files;
    vector<Directory *> dirs;
};

// 0. Enforce that no file/directory with the same nameext can be created in the same dir.
bool checkFilename(string filename, Directory &where)
{
    for(size_t i = 0; i < where.files.size(); i++)
    {
        if(filename==getFullFilename(*where.files[i]))
        {
            return false; 
        }
    }
    for(size_t i = 0; i < where.dirs.size(); i++)
    {
        if(filename == where.dirs[i]->name)
        {
            return false;
        }
    }
    return true;
}

// 4. DirectorySize function includes the size of child directories
uint64_t getDirectorySize(Directory &d) 
{
    uint64_t sz = 0;
    for (size_t i = 0; i < d.files.size(); i++) {
        sz += d.files[i]->byteSize;
    }
    for(size_t i = 0; i < d.dirs.size(); i++)
    {
        sz += getDirectorySize(*d.dirs[i]);
    }

    return sz;
}

bool moveFile(const string &filename, Directory &from, Directory &to) 
{
    File *file = nullptr;
    for (size_t i = 0; i < from.files.size(); i++) {
        if (filename == getFullFilename(*from.files[i])) {
            file = from.files[i];
            for (size_t j = i; j < from.files.size() - 1; j++) {
                from.files[j] = from.files[j + 1];
            }
            from.files.pop_back();

            to.files.push_back(file);
            return true;
        }
    }
    return false;
}

// 1. When printing the directory, print the contents of all child directories!!!
void printDir(Directory &d) 
{
    cout << "d: " << d.name << '\n';
    for (size_t i = 0; i < d.files.size(); i++) {
        cout << " f " << getFullFilename(*d.files[i]) << '\n';
    }
    for (size_t i = 0; i < d.dirs.size(); i++) 
    {
        printDir(*d.dirs[i]);
    }
    cout << "Size: " << getDirectorySize(d) << " B\n";
}

// 2. Implement 'Up' function that return the parent directory of the current directory
//    If no parent is available, print '/(root)'
bool Up(Directory &general, Directory &current)
{
    if(&current == &general)
    {
        cout << "/(root)";
        return true;
    }
    else
    {
        for(size_t i = 0; i < general.dirs.size(); i++)
        {
            if(general.dirs[i] == &current)
            {
                cout << general.name;
                return true;
            }
            if(Up(*general.dirs[i], current))
            {
                return true;
            }
        }
    }
    return false;
}

// 3. Implement "Find" that searches for a file or directory inside a specific directory.
//    The file/directory can be nested inside a subdirectory
bool Find(Directory &d, string find)
{
    for(size_t i = 0; i < d.files.size(); i++)
    {
        if(find == getFullFilename(*d.files[i]))
        {
            cout << "Found file" << find << " in " << d.name << " at position " << i << endl;
            return true;
        }
    }
    for(size_t i = 0; i < d.dirs.size(); i++)
        {
            if(find == d.dirs[i]->name)
            {
                cout << "Found directory " << find << " in " << d.name << " at position " << i << endl;
                return true;
            }
            if(Find(*d.dirs[i], find))
            {
                return true;
            }
        }
    return false;
}


int main() 
{
    Directory my;
    my.name = "documents";
    File x, y, z;
    x.name = "X";
    x.extension = "txt";
    x.byteSize = 1024;

    y.name = "Y";
    y.extension = "jpeg";
    y.byteSize = 56281022;

    z.name = "z";
    z.extension = "mov";
    z.byteSize = 1556281022;

    my.files.push_back(&x);
    my.files.push_back(&y);
    my.files.push_back(&z);

    string filename = "X.txt";
    if (checkFilename(filename, my))
    {
        cout << "Available" << endl;
    }
    else
    {
        cout << "Cannot use this name" << endl;
    }

    y.name = "YYY";

    Directory child;
    child.name = "Child One";

    my.dirs.push_back(&child);

    printDir(my);

    Up(my, child);
    cout << endl;

    if(Find(my, "Child One") == false)
    {
        cout << "Not found"<< endl;
    }

    cout << "Size of my: "<< getDirectorySize(my) << " B" << endl;
    cout << "Size of child: "<< getDirectorySize(child) << " B" << endl;


    moveFile(getFullFilename(z), my, child);
    cout << "AFTER MOVE\n";
    printDir(my);

    printDir(child);
    return 0;
}