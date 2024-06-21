#include <iostream>
#include <vector>
#include <memory>
#include <string>


class Ticket {
public:
    Ticket(const std::string& type, double price) : type(type), price(price) {}

    std::string getType() const {
        return type;
    }

    double getPrice() const {
        return price;
    }

private:
    std::string type;
    double price;
};


class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual std::shared_ptr<Ticket> next() = 0;
};


class TicketIterator : public Iterator {
public:
    TicketIterator(const std::vector<std::shared_ptr<Ticket>>& tickets) : tickets(tickets), index(0) {}

    bool hasNext() const override {
        return index < tickets.size();
    }

    std::shared_ptr<Ticket> next() override {
        return tickets[index++];
    }

private:
    std::vector<std::shared_ptr<Ticket>> tickets;
    size_t index;
};


class TicketCollection {
public:
    void addTicket(const std::shared_ptr<Ticket>& ticket) {
        tickets.push_back(ticket);
    }

    std::unique_ptr<Iterator> createIterator() const {
        return std::make_unique<TicketIterator>(tickets);
    }

private:
    std::vector<std::shared_ptr<Ticket>> tickets;
};


void printTickets(const TicketCollection& collection) {
    auto iterator = collection.createIterator();
    while (iterator->hasNext()) {
        auto ticket = iterator->next();
        std::cout << "Ticket Type: " << ticket->getType() << ", Price: $" << ticket->getPrice() << std::endl;
    }
}


int main() {
    TicketCollection collection;
    collection.addTicket(std::make_shared<Ticket>("Regular Ticket", 50.0));
    collection.addTicket(std::make_shared<Ticket>("VIP Ticket", 200.0));
    collection.addTicket(std::make_shared<Ticket>("Student Ticket", 30.0));

    std::cout << "Available tickets:" << std::endl;
    printTickets(collection);

    return 0;
}