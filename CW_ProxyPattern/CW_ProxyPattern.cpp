
#include <iostream>
#include <string>

class ServiceIntf
{
public:
    virtual void SendMassage(std::string masg) = 0;
};

class Service : public ServiceIntf
{
public:
    void SendMassage(std::string masg) override
    {
        std::cout << "Massege: \"" << masg << "\" - sent\n";
    }
};

class Proxy : public ServiceIntf
{
private:
    Service* serv_;
    bool CheckInternen() const
    {
        std::cout << "checking internet\n";
        std::cout << "succes\n";
        return true;
    }
public:
    Proxy(Service* serv) : serv_(new Service(*serv))
    {}

    void SendMassage(std::string masg)
    {
        if (CheckInternen())
        {
            this->serv_->SendMassage(masg);
        }
    }

    ~Proxy()
    {
        delete serv_;
    }
};

void Client(ServiceIntf* serv, std::string masg)
{
    serv->SendMassage(masg);
}

int main()
{
    Service* serv = new Service;
    Proxy* proxy = new Proxy(serv);
    Client(proxy, "ABCDEFG");
    delete serv;
    delete proxy;
}