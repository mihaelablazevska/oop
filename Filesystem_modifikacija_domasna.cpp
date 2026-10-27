#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct File 
{
    private:
    string name;
    string extension;
    uint64_t byteSize;

    public:
    File(string n, string e, uint64_t b)
    {
        name = n;
        extension = e;
        byteSize = b;
    }

    string getFullFilename() 
    { 
        return name + '.' + extension;
    }
    uint64_t getByteSize()
    {
        return byteSize;
    }

    void setName(string n, string e)
    {
        name = n;
        extension = e;
    }
};

struct Directory {
    private:
    string name;
    vector<File *> files;
    vector<Directory *> dirs;

    public:
    Directory(string n, vector<File*> f, vector<Directory*> d)
    {
        name = n;
        files = f;
        dirs = d;
    }
    string getName()
    {
        return name;
    }

    bool checkFilename(string filename)
    {
        for(size_t i = 0; i < files.size(); i++)
        {
            if(filename==files[i]->getFullFilename())
            {
                return true; 
            }
        }
        for(size_t i = 0; i < dirs.size(); i++)
        {
            if(filename == dirs[i]->getName())
            {
                return true;
            }
        }
        return false;
    }

    void addFile(File* f)
    {
        files.push_back(f);
    }

    void addDirectory(Directory* d)
    {
        dirs.push_back(d);
    }

    void DirectoryName(string newname)
    {
        if(checkFilename(newname))
        {
            cout << "The name is taken by another directory" << '\n';
        }
        else 
        {
            name = newname;
        }
    }

    void FileName(File &f, string newname, string ext)
    {
        string s = newname + "." + ext;
        if(checkFilename(s))
        {
            cout << "The name is taken by another file" << '\n';
        }
        else
        {
            f.setName(newname, ext);
        }
    }

    uint64_t getDirectorySize() 
    {
        uint64_t sz = 0;
        for (size_t i = 0; i < files.size(); i++) 
        {
            sz += files[i]->getByteSize();
        }
        for(size_t i = 0; i < dirs.size(); i++)
        {
            sz += dirs[i]->getDirectorySize();
        }
        return sz;
    }

    bool moveFile(const string &filename, Directory &to) 
    {
        File *file = nullptr;
        for (size_t i = 0; i < files.size(); i++) {
            if (filename == files[i]->getFullFilename()) 
            {
                file = files[i];
                for (size_t j = i; j < files.size() - 1; j++) 
                {
                    files[j] = files[j + 1];
                }
                files.pop_back();

                to.files.push_back(file);
                return true;
            }
        }
        return false;
    }

    void printDir() 
    {
        cout << "d: " << name << '\n';
        for (size_t i = 0; i < files.size(); i++) 
        {
            cout << " f " << files[i]->getFullFilename() << '\n';
        }
        for (size_t i = 0; i < dirs.size(); i++) 
        {
            dirs[i]->printDir();
        }
        cout << "Size: " << getDirectorySize() << " B\n";
    }

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

    bool Find(string find)
    {
        for(size_t i = 0; i < files.size(); i++)
        {
            if(find == files[i]->getFullFilename())
            {
                cout << "Found file" << find << " in " << name << " at position " << i << endl;
                return true;
            }
        }
        for(size_t i = 0; i < dirs.size(); i++)
            {
                if(find == dirs[i]->getName())
                {
                    cout << "Found directory " << find << " in " << name << " at position " << i << endl;
                    return true;
                }
                if(dirs[i]->Find(find))
                {
                    return true;
                }
            }
        return false;
    }
};


int main() 
{
    Directory my("documents", {} , {});
    File x("X", "txt", 1024);
    File y("Y", "jpeg", 56281022);
    File z("z", "mov", 1556281022);

    my.addFile(&x);
    my.addFile(&y);
    my.addFile(&z);

    my.FileName(y, "YYY", "jpeg");

    Directory child("Child One", {}, {});
    my.addDirectory(&child);

    my.printDir();

    my.Up(my, child);
    cout << endl;

    if (!my.Find("Child One"))
    {
        cout << "Not found" << endl;
    }

    cout << "Size of my: " << my.getDirectorySize() << " B" << endl;

    cout << "Size of child: " << child.getDirectorySize() << " B" << endl;

    my.moveFile(z.getFullFilename(), child);

    cout << "AFTER MOVE\n";

    my.printDir();
    child.printDir();

    return 0;
}