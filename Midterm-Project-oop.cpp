#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Item {
private:
    int productID;
    string name;
    int quantity;
    float price;
    string category;

public:
    Item(int id, string name, int quantity, float price, string category)
        : productID(id), name(name), quantity(quantity), price(price), category(category) {}

    int getID() const { return productID; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    string getCategory() const { return category; }

    void updateQuantity(int newQuantity) { quantity = newQuantity; }
    void updatePrice(float newPrice) { price = newPrice; }
};

class Inventory {
private:
    vector<Item> items;
    int nextID;

public:
    Inventory() : nextID(1) {}

    void addItem(string name, int quantity, float price, string category) {
        items.emplace_back(nextID, name, quantity, price, category);
        nextID++;
        cout << "Item added successfully!" << endl;
    }

    void updateItem(int id, string updateType, float newValue) {
        for (auto& item : items) {
            if (item.getID() == id) {
                if (updateType == "quantity") {
                    int oldQuantity = item.getQuantity();
                    item.updateQuantity(static_cast<int>(newValue));
                    cout << "Quantity of Item " << item.getName() << " is updated from " << oldQuantity << " to " << static_cast<int>(newValue) << endl;
                } else if (updateType == "price") {
                    float oldPrice = item.getPrice();
                    item.updatePrice(newValue);
                    cout << "Price of Item " << item.getName() << " is updated from " << oldPrice << " to " << newValue << endl;
                }
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void removeItem(int id) {
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].getID() == id) {
                cout << "Item " << items[i].getName() << " has been removed from the inventory" << endl;
                items.erase(items.begin() + i);
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void displayAllItems() const {
        cout << "ID    Name          Quantity   Price       Category" << endl;
        for (const auto& item : items) {
            cout << item.getID() << "     " << item.getName() << "     " << item.getQuantity() << "         "
                 << item.getPrice() << "       " << item.getCategory() << endl;
        }
    }

    void searchItem(int id) const {
        for (const auto& item : items) {
            if (item.getID() == id) {
                cout << "ID: " << item.getID() << ", Name: " << item.getName() << ", Quantity: " << item.getQuantity()
                     << ", Price: " << item.getPrice() << ", Category: " << item.getCategory() << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void sortItems(string sortBy, string order) {
        if (sortBy == "quantity") {
            for (size_t i = 0; i < items.size() - 1; i++) {
                for (size_t j = 0; j < items.size() - i - 1; j++) {
                    bool shouldSwap = false;
                    if (order == "ascending") {
                        shouldSwap = items[j].getQuantity() > items[j+1].getQuantity();
                    } else {
                        shouldSwap = items[j].getQuantity() < items[j+1].getQuantity();
                    }
                    if (shouldSwap) {
                        swap(items[j], items[j+1]);
                    }
                }
            }
        } else if (sortBy == "price") {
            for (size_t i = 0; i < items.size() - 1; i++) {
                for (size_t j = 0; j < items.size() - i - 1; j++) {
                    bool shouldSwap = false;
                    if (order == "ascending") {
                        shouldSwap = items[j].getPrice() > items[j+1].getPrice();
                    } else {
                        shouldSwap = items[j].getPrice() < items[j+1].getPrice();
                    }
                    if (shouldSwap) {
                        swap(items[j], items[j+1]);
                    }
                }
            }
        }
        displayAllItems();
    }

    void displayLowStockItems() const {
        cout << "ID    Name          Quantity   Price       Category" << endl;
        for (const auto& item : items) {
            if (item.getQuantity() <= 5) {
                cout << item.getID() << "     " << item.getName() << "     " << item.getQuantity() << "         "
                     << item.getPrice() << "       " << item.getCategory() << endl;
            }
        }
    }
};

// Example Menu Function
void menu() {
    Inventory inventory;
    while (true) {
        cout << "\nMenu\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display All Items\n";
        cout << "5 - Search Item\n";
        cout << "6 - Sort Items\n";
        cout << "7 - Display Low Stock Items\n";
        cout << "8 - Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, category;
                int quantity;
                float price;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter category: ";
                cin >> category;
                inventory.addItem(name, quantity, price, category);
                break;
            }
            case 2: {
                int id;
                string updateType;
                float newValue;
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter update type (quantity/price): ";
                cin >> updateType;
                cout << "Enter new value: ";
                cin >> newValue;
                inventory.updateItem(id, updateType, newValue);
                break;
            }
            case 3: {
                int id;
                cout << "Enter product ID: ";
                cin >> id;
                inventory.removeItem(id);
                break;
            }
            case 4:
                inventory.displayAllItems();
                break;
            case 5: {
                int id;
                cout << "Enter product ID: ";
                cin >> id;
                inventory.searchItem(id);
                break;
            }
            case 6: {
                string sortBy, order;
                cout << "Sort by (quantity/price): ";
                cin >> sortBy;
                cout << "Order (ascending/descending): ";
                cin >> order;
                inventory.sortItems(sortBy, order);
                break;
            }
            case 7:
                inventory.displayLowStockItems();
                break;
            case 8:
                cout << "Exiting... Goodbye!" << endl;
                return;
            default:
                cout << "Invalid option! Try again." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}