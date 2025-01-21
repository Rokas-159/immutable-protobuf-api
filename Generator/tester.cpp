#include <bits/stdc++.h>
#include "taskas.mypb.h"

using namespace std;

int main() {
    Taskas::Builder taskas_builder;
    taskas_builder.set_x(1);
    taskas_builder.set_y(2);
    taskas_builder.set_z(3);
    taskas_builder.set_name("Taskas");
    taskas_builder.add_numbers(1);
    taskas_builder.add_numbers(2);
    taskas_builder.add_numbers(3);
    Taskas taskas = move(taskas_builder).Build();

    cout << "Taskas1: " << taskas.get_x() << " " << taskas.get_y() << " " << taskas.get_z() << " " << taskas.get_name() << endl;
    cout << "Numbers size: " << taskas.numbers_size() << endl;
    for (size_t i = 0; i < taskas.numbers_size(); i++) {
        cout << "Numbers[" << i << "]: " << taskas.get_numbers(i) << endl;
    }

    return 0;
}