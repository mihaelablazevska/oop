#include <iostream>
using namespace std;

class MyVec
{
    private:

    unsigned int calc_capacity(unsigned int size)
    {
        unsigned int result = 1;
        return result << size;

    }
    unsigned int v_size;
    unsigned int v_capacity;
    int *array;


    public:

    MyVec(unsigned int size = 0, int value = 0)
    {
        v_size = size;
        int c = calc_capacity(size);
        v_capacity = ((c < 8) ? 8 : c);
        array = new int[v_capacity];
        for(int i = 0; i < v_size; i++)
        {
            array[i] = value;
        }
    }

    int size()
    {
        return v_size;
    }
    int capacity()
    {
        return v_capacity;
    }

    void info()
    {
        cout << "c: " << v_capacity << "s: " << v_size << '\n' << "[ ";
        for(int i = 0; i< v_size; i++)
        {
            cout << array[i] << " ";
        }
        cout << "]" << '\n';
    }

    int& at(unsigned int index)
    {
        return array[index];
    }

    void change(unsigned int index, int value)
    {
        if(index < v_size && index >= 0)
        {
            array[index] = value;
        }
    }

    int back()
    {
        return array[size() - 1];
    }

    void pop()
    {
        if(v_size >= 1)
        {
            v_size --;
        }
    }
};

int main()
{
    MyVec v1(4, 2);
    cout << v1.at(1) << endl;
    MyVec v2(7);
    v1.at(1) = 9;
    cout << v1.at(1) << endl;
    cout << v2.capacity() << endl;
    v1.pop();
    cout << v1.size() << endl;
}