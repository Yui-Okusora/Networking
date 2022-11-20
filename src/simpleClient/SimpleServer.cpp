#include <iostream>
#include "D:\Code\C++\Networking\libs\netCommon\olc_net.h"

enum class CustomMsgType : uint32_t
{
    ServerAccept,
    ServerDenied,
    ServerPing,
    MessageAll,
    ServerMessage
};

class CustomServer : public olc::net::server_interface<CustomMsgType>
{
public:
    CustomServer(uint16_t nport) : olc::net::server_interface<CustomMsgType>(nport)
    {

    }
protected:
    virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgType>> client)
    {
        return true;
    }

    virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgType>> client)
    {
        
    }

    virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgType>> client, olc::net::message<CustomMsgType> msg)
    {

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