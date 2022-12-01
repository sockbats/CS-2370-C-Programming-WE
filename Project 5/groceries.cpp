// groceries_template.cpp: Stores Orders in a list.

#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <utility>
#include <utility>
#include <vector>
#include <algorithm>
#include "split.h"
//using namespace std;

//////////////////
// Customer code /
//////////////////
struct Customer {
    int cust_id;
    std::string name;
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
    std::string phone;
    std::string email;
    Customer(int id, std::string  name, std::string  street, std::string  city, std::string  state, std::string  zip, std::string  phone, std::string  email)
        : name(std::move(name)), street(std::move(street)), city(std::move(city)), state(std::move(state)), zip(std::move(zip)), phone(std::move(phone)), email(std::move(email))
    {
        cust_id = id;
    }
    [[nodiscard]] std::string print_detail() const {
        std::string out = "Customer ID #" + std::to_string(this->cust_id) + ":\n" + this->name + ", ph. " + this->phone + ", email: " + this->email + "\n" + this->street + "\n" + this->city + ", " + this->state + " " + this->zip;
        return out;
    }
};
std::vector<Customer> customers;

void read_customers(const std::string& fname) {
    std::vector<std::string> cust;
    std::ifstream customersFile(fname);
    if (customersFile.is_open()) {
        std::string line;
        while (std::getline(customersFile, line)) {
            cust = split(line, ',');
            customers.emplace_back(stoi(cust[0]), cust[1], cust[2], cust[3], cust[4], cust[5], cust[6], cust[7]);
        }
        customersFile.close();
    }
}

int find_cust_idx(int cust_id) {
    for (int i = 0; i < customers.size(); ++i)
        if (cust_id == customers[i].cust_id)
            return i;
    throw std::runtime_error("Customer not found");
}

//////////////
// Item code /
//////////////
struct Item {
    int item_id;
    std::string description;
    double price;
    Item(int id, std::string  desc, double pric) : description(std::move(desc)) {
        item_id = id;
        price = pric;
    }
};
std::vector<Item> items;

void read_items(const std::string& fname) {
    std::vector<std::string> item;
    std::ifstream itemsFile(fname);
    if (itemsFile.is_open()) {
        std::string line;
        while (std::getline(itemsFile, line)) {
            item = split(line, ',');
            items.emplace_back(std::stoi(item[0]), item[1], stod(item[2]));
        }
        itemsFile.close();
    }
}

int find_item_idx(int item_id) {
    for (int i = 0; i < items.size(); ++i)
        if (item_id == items[i].item_id)
            return i;
    throw std::runtime_error("Item not found");
}

class LineItem {
    int item_id;
    int qty;
    friend class Order;
public:
    LineItem(int id, int q) {
        item_id = id;
        qty = q;
    }
    [[nodiscard]] double sub_total() const {
        int idx = find_item_idx(item_id);
        return items[idx].price * qty;
    }
    friend bool operator<(const LineItem& item1, const LineItem& item2) {
        return item1.item_id < item2.item_id;
    }
};

/////////////////
// Payment code /
/////////////////
class Payment {
    friend class Order;
protected:
    double amount = 0.0;
public:
    Payment() = default;
    virtual ~Payment() = default;
    virtual std::string print_detail() {return "";};
};

class Credit : public Payment {
private:
    std::string cardNum;
    std::string expiration;
public:
    Credit(std::string cardNum, std::string expiration) : cardNum(std::move(std::move(cardNum))), expiration(std::move(std::move(expiration))) {};
    std::string print_detail() override {
        std::string stringAmount = std::to_string(amount);
        std::string out = "Amount: $" + stringAmount.substr(0, stringAmount.find('.') + 3) + ", Paid by Credit card " + cardNum + ", exp. " + expiration;
        return out;
    }
};

class Paypal : public Payment {
private:
    std::string id;
public:
    explicit Paypal(std::string id) : id(std::move(std::move(id))) {};
    std::string print_detail() override {
        std::string stringAmount = std::to_string(amount);
        std::string out = "Amount: $" + stringAmount.substr(0, stringAmount.find('.') + 3) + ", Paid by Paypal ID: " + id;
        return out;
    }
};

class WireTransfer : public Payment {
private:
    std::string id;
public:
    explicit WireTransfer(std::string id) : id(std::move(std::move(id))) {};
    std::string print_detail() override {
        std::string stringAmount = std::to_string(amount);
        std::string out = "Amount: $" + stringAmount.substr(0, stringAmount.find('.') + 3) + ", Paid by Wire transfer from Bank ID " + id;
        return out;
    }
};

///////////////
// Order code /
///////////////
class Order {
    int order_id;
    std::string order_date;
    int cust_id;
    std::vector<LineItem> line_items;
    Payment* payment;
public:
    Order(int id, std::string  date, int c_id, const std::vector<LineItem>& ytems, Payment* p)
    : order_date(std::move(date)), line_items(ytems) {
        order_id = id;
        cust_id = c_id;
        payment = p;
        sort(line_items.begin(), line_items.end());
        double total = 0.0;
        for (auto i: line_items) {
            total += i.sub_total();
        }
        p->amount = total;
    }
    ~Order() {
        delete payment;
    }
    [[nodiscard]] double total() const {
        return payment->amount;
    }
    [[nodiscard]] std::string print_order() const {
        std::string out = "===========================\nOrder #" + std::to_string(order_id) + ", Date: " + order_date +
                "\n" + payment->print_detail() + "\n\n" + customers[find_cust_idx(cust_id)].print_detail() +
                "\n\nOrder Detail:\n";
        for (auto i: line_items) {
            std::string itemPrice = std::to_string(items[find_item_idx(i.item_id)].price);
            out += "    Item " + std::to_string(i.item_id) + ": \"" + items[find_item_idx(i.item_id)].description + "\", " +
                    std::to_string(i.qty) + " @ " + itemPrice.substr(0, itemPrice.find('.') + 3) + "\n";
        }
        return out;
    }
};
std::list<Order> orders;

void read_orders(const std::string& fname) {
    std::ifstream orderf("./" + fname);
    std::string line;
    while (getline(orderf, line)) {
        auto lyne = split(line, ',');
        int cust_id = stoi(lyne[0]), order_id = stoi(lyne[1]);
        std::string date = lyne[2];
        std::vector<LineItem> line_items;
        for (int i = 3; i < size(lyne); i++) {
            auto ytem = split(lyne[i], '-');
            line_items.emplace_back(stoi(ytem[0]), stoi(ytem[1]));
        }

        sort(begin(line_items), end(line_items));

        getline(orderf, line);
        auto payment = split(line, ',');
        Payment* pmt;
        switch (stoi(payment[0])) {
            case 1:
                pmt = new Credit(payment[1], payment[2]);
                break;
            case 2:
                pmt = new Paypal(payment[1]);
                break;
            case 3:
                pmt = new WireTransfer(payment[1]);
                break;
        }
        orders.emplace_back(order_id, date, cust_id, line_items, pmt);
    }
}

int main() {
    read_customers("customers.txt");
    read_items("items.txt");
    read_orders("orders.txt");

    std::ofstream ofs("order_report.txt");
    for (const Order& order: orders)
        ofs << order.print_order() << "\n";
}
