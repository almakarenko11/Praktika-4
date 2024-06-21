#include <iostream>
#include <vector>
#include <memory>
#include <string>


class RegularTicket;
class VIPTicket;

class TicketVisitor {
public:
    virtual ~TicketVisitor() = default;
    virtual void visit(RegularTicket& ticket) = 0;
    virtual void visit(VIPTicket& ticket) = 0;
};


class Ticket {
public:
    virtual ~Ticket() = default;
    virtual void accept(TicketVisitor& visitor) = 0;
};


class RegularTicket : public Ticket {
public:
    RegularTicket(double price) : price(price) {}

    double getPrice() const {
        return price;
    }

    void accept(TicketVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double price;
};


class VIPTicket : public Ticket {
public:
    VIPTicket(double price) : price(price) {}

    double getPrice() const {
        return price;
    }

    void accept(TicketVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double price;
};


class TotalPriceVisitor : public TicketVisitor {
public:
    void visit(RegularTicket& ticket) override {
        total += ticket.getPrice();
    }

    void visit(VIPTicket& ticket) override {
        total += ticket.getPrice();
    }

    double getTotal() const {
        return total;
    }

private:
    double total = 0;
};


class DescriptionVisitor : public TicketVisitor {
public:
    void visit(RegularTicket& ticket) override {
        description += "Regular Ticket: $" + std::to_string(ticket.getPrice()) + "\n";
    }

    void visit(VIPTicket& ticket) override {
        description += "VIP Ticket: $" + std::to_string(ticket.getPrice()) + "\n";
    }

    std::string getDescription() const {
        return description;
    }

private:
    std::string description;
};


int main() {
    std::vector<std::shared_ptr<Ticket>> tickets;
    tickets.push_back(std::make_shared<RegularTicket>(50.0));
    tickets.push_back(std::make_shared<VIPTicket>(200.0));
    tickets.push_back(std::make_shared<RegularTicket>(50.0));
    tickets.push_back(std::make_shared<VIPTicket>(200.0));

    TotalPriceVisitor priceVisitor;
    DescriptionVisitor descriptionVisitor;

    for (auto& ticket : tickets) {
        ticket->accept(priceVisitor);
        ticket->accept(descriptionVisitor);
    }

    std::cout << "Total Price: $" << priceVisitor.getTotal() << std::endl;
    std::cout << "Ticket Descriptions:\n" << descriptionVisitor.getDescription() << std::endl;

    return 0;
}