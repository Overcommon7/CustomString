#include <iostream>
#include "String.h"

using namespace nm;
using std::cout;
using std::cin;

int main()
{
    {
        string str("hello world");
        cout << str << ' ' << str.size() << '\n';
        auto pos = str.erase(1);
        cout << str << ' ' << str.size() << ' ' << str[pos] << '\n';
        cout << string(str) << '\n';
        cout << string(3343453214) << '\n';
        cout << string::ToString(890890) << '\n';

        string
            str2 = "hello space",
            str3 = "hello atmosphere",
            str4 = "hello galaxy";

        str.push_back(str2);
        cout << str << '\n';
        cout << str[5] << '\n';

        str.push_back('a');

        cout << str << '\n';

        str.sort();
        cout << str << '\n';
        str.sort<std::greater<char>>();
        cout << str << '\n';

        cout << str3.substr(0, 4) + '\n';
        str3 += " this was appended";
        if (str3.find('w') != string::npos)
            cout << "Found\n";

        cout << str3.substr(2, 5) << '\n';
        for (short i = 0; i < str3.size(); i++)
            cout << str3[i];
        cout << '\n';
        str2 += "jk";
        str.insert('j', 4, 8000);
        cout << str2 << ' ' << str2.max_capacity() << '\n';
        str2.insert("hsjkd", 7);
        cout << str2 << '\n';
        cout << str2[str2.find_first_of("hjk")];
        cin >> str2;
        cout << str2;
    }
    _CrtDumpMemoryLeaks();
}
