//
// Created by 20212 on 24-12-19.
//
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

class String
{
public:
    String(const char *str = "")
    {
        cout << "String(const char *str) - 普通构造" << endl;
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    String(const String &s)
    {
        cout << "String(const String &s) - 拷贝构造" << endl;
        _str = new char[strlen(s._str) + 1];
        strcpy(_str, s._str);
    }

    // 右值:将亡值
    String(String &&s) : _str(nullptr)
    {
        cout << "String(String &&s) - 移动构造" << endl;
        // 移动拷贝 代价小 效率高
        // 传过来的是一个将亡值，将亡值是一个临时对象，临时对象的生命周期即将结束
        // 将亡值的生命周期即将结束，我们可以将其资源移动过来
        swap(_str, s._str);
    }

    String &operator=(const String &s)
    {
        cout << "String& operator=(const String& s) - 拷贝赋值" << endl;
        if (this != &s)  // 如果不是自己给自己赋值
        {
            char *newstr = new char[strlen(s._str) + 1];
            strcpy(newstr, s._str);

            delete[] _str;
            _str = newstr;
        }
    }

    // 传入将亡值 - 进行移动拷贝
    String &operator=(String &&s)
    {
        cout << "String& operator=(String&& s) - 移动赋值" << endl;
        if (this != &s)
        {
            swap(_str, s._str);
        }
        return *this;
    }

    ~String()
    {
        delete[] _str;
    }

    String operator+(const String &s2)
    {
        String ret(*this);
        // ret.append(s2._str);
        return ret;
        // 返回的是一个将亡值
    }

    String &operator+=(const String &s2)
    {
        // this -> append(s2._str);
        return *this;
        // 返回的是一个左值
    }

    string f(const char *str)
    {
        string tmp(str);
        return tmp;
        // 返回的是一个将亡值
    }

private:
    char *_str;
};

int main()
{
    String s1("s1");
    String s2("s2");
    String s3 = s1 + s2;  // s1.operator+(s2)
    return 0;
}

// 结论右值引用本身没有很大的意义,右值引用实现移动拷贝和移动赋值
// 那么面对接收函数参数传值返回参数时,可以提高效率
// 左值引用进行深拷贝
// 右值引用进行移动拷贝