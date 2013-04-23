
#include <datastore.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

struct TPerson
{
    char m_name[20];
    int m_age;
    bool m_sex;
};

int main()
{
    DataStore ds(sizeof(TPerson), 200);
    TPerson p;

    std::cout << "MaxNum=" << ds.getMaxNum() << std::endl;

    for (int i = 0; i < 10; ++i) {
        sprintf(p.m_name, "name is [%d]", i);
        p.m_age = 20 + i;
        p.m_sex = (i%2 == 0);
        ds.putIn(&p, sizeof(p));
        std::cout << "Num=" << ds.getNum() << std::endl;
    }
    TPerson p1;
    for (int i = 0; i < 10; ++i) {
//        ds.fetch(&p1, sizeof(p1));
        ds.readAt(&p1, sizeof(p1), i);
        std::cout << p1.m_name << "," << p1.m_age << "," << p1.m_sex << std::endl;
        std::cout << "Num=" << ds.getNum() << std::endl;
        memset(&p1, 0, sizeof(p1));
    }
}
