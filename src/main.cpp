#include "../lib/GridCell.h"
#include <iostream>

int main() {
    // Create an Entry cell
    GridCell entryCell({0, 0}, GridCellType::Entry, new Entry(Direction::Up));

    // Print details
    std::cout << "Cell position: (" << entryCell.getPosition().first << ", " 
              << entryCell.getPosition().second << ")\n";
    std::cout << "Cell type: " << entryCell.toString() << "\n";

    // Check specific cell types
    if (entryCell.isActivatedBumper()) {
        std::cout << "This is an activated bumper.\n";
    } else {
        std::cout << "This is not an activated bumper.\n";
    }

    return 0;
}
