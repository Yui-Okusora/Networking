#include <iostream>
#include "D:\Code\C++\Networking\libs\net\olc_net.h"

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDenied,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class CustomServer : public olc::net::server_interface<CustomMsgTypes>
{
public:
    CustomServer(uint16_t nport) : olc::net::server_interface<CustomMsgTypes>(nport)
    {

    }
protected:
    virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
    {
        return true;
    }

    virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
    {
        
    }

    virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& msg)
    {
        switch (msg.header.id)
        {
        case CustomMsgTypes::ServerPing:
        {
            std::cout << "[" << client->GetID() << "]: Server Ping\n";

            client->Send(msg);
        }
        break;
        }
    }
};

int main()
{
    CustomServer server(60000);
    server.Start();
    while (1)
    {
        server.Update();
    }
    return 0;
}