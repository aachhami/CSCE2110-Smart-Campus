#include <iostream>
int main() {
	int choice = 0;
	do
	{
		std::cout << "1. View all facilities" << '\n';
		std::cout << "2. Search facility by ID" << '\n';
		std::cout << "3. View campus graph" << '\n';
		std::cout << "4. Display graph counts and degrees" << '\n';
		std::cout << "5. Find reachable buildings (BFS)" << '\n';
		std::cout << "6. Add department" << '\n';
		std::cout << "7. Search department" << '\n';
		std::cout << "8. Display department hierarchy" << '\n';
		std::cout << "9. Run preorder traversal" << '\n';
		std::cout << "10. Exit" << '\n' << '\n';
		std::cout << "Enter your choice: ";

		while (!(std::cin >> choice) || choice < 1 || choice > 10) {
			std::cout << "Invalid input. Please enter a number between 1 and 10: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		switch (choice) {
		case 1:
			std::cout << "Viewing all facilities..." << '\n';
			break;
		case 2:
			std::cout << "Searching facility by ID..." << '\n';
			break;
		case 3:
			std::cout << "Viewing campus graph..." << '\n';
			break;
		case 4:
			std::cout << "Displaying graph counts and degrees..." << '\n';
			break;
		case 5:
			std::cout << "Finding reachable buildings (BFS)..." << '\n';
			break;
		case 6:
			std::cout << "Adding department..." << '\n';
			break;
		case 7:
			std::cout << "Searching department..." << '\n';
			break;
		case 8:
			std::cout << "Displaying department hierarchy..." << '\n';
			break;
		case 9:
			std::cout << "Running preorder traversal..." << '\n';
			break;
		case 10:
			std::cout << "Exiting program..." << '\n';
			break;
		}
	} while (choice != 10);

	return 0;

}
