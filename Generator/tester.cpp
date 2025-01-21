#include <bits/stdc++.h>
#include "taskas.mypb.h"

using namespace std;

int main() {
    Taskai::Builder taskai_builder;

    for (int i = 0; i < 3; i++) {
        Taskas::Builder taskas_builder;
        taskas_builder.set_x(3*i+1);
        taskas_builder.set_y(3*i+2);
        taskas_builder.set_z(3*i+3);
        taskas_builder.set_name("Taskas " + to_string(i));
        taskas_builder.add_numbers(i);
        taskas_builder.add_numbers(i);
        taskas_builder.add_numbers(i);
        taskai_builder.add_taskai(move(taskas_builder).Build());
    }

    Taskai taskai = move(taskai_builder).Build();

    for (int i = 0; i < taskai.taskai_size(); i++) {
        Taskas taskas = taskai.get_taskai(i);
        cout << taskas.get_name() << ": " << taskas.get_x() << " " << taskas.get_y() << " " << taskas.get_z() << endl;
        cout << "Numbers size: " << taskas.numbers_size() << endl;
        for (size_t j = 0; j < taskas.numbers_size(); j++) {
            cout << "Numbers[" << j << "]: " << taskas.get_numbers(j) << endl;
        }
    }

    return 0;
}