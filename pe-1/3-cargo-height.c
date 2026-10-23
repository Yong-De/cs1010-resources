#include "student.h"

/*
    For your reference. Do not uncomment this!

    typedef struct {
        int left;
        int right;
    } Cargo;

*/

int height(int num_cargo, Cargo const cargo_list[]) {
    Cargo last_cargo = cargo_list[num_cargo - 1];

    int return_height = 1;
    for (int i = 0; i < num_cargo - 1; i++) {
        Cargo cargo = cargo_list[i];
        bool is_overlap =
            cargo.left < last_cargo.right && last_cargo.left < cargo.right;
        if (is_overlap) {
            int cur_height = 1 + height(i + 1, cargo_list);
            return_height =
                (cur_height > return_height) ? cur_height : return_height;
        }
    }

    return return_height;
}
