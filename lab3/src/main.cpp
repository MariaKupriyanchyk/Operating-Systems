#include "marker_manager.h"
#include <iostream>

int main() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    MarkerManager mgr(size);

    int count;
    std::cout << "Enter marker count: ";
    std::cin >> count;

    mgr.launch(count);
    mgr.start_all();

    while (mgr.any_alive()) {
        mgr.wait_all_blocked();

        std::cout << "\nArray state:\n";
        mgr.print();

        int id;
        std::cout << "Enter marker id to terminate: ";
        std::cin >> id;

        mgr.terminate(id);

        std::cout << "\nAfter termination:\n";
        mgr.print();

        mgr.resume_all();
    }

    mgr.join_all();
    std::cout << "All markers finished\n";

    return 0;
}