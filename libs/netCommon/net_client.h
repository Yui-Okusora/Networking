#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace olc
{
    namespace net
    {
        template<typename T>
        class client_interface
        {
        public:
            client_interface() : m_socket(m_context){}

            virtual ~client_interface()
            {
                Disconnect();
            }
        
            bool Connect(const std::string& host, const uint16_t port)
            {
                try
                {

                    asio::ip::tcp::resolver resolver(m_context);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                    m_connection = std::make_unique<connection<T>>(
                        connection<T>::owner::client,
                        m_context,
                        asio::ip::tcp::socket(m_context), m_qMessagesIn);

                    m_connection->ConnectToServer(endpoints);

                    thrContext = std::thread([this](){ m_context.run(); });
                }
                catch(std::exception& e)
                {
                    std::cerr << "Client Exception: " << e.what() << '\n';
                    return false;
                }
                return true;
            }

            void Disconnect()
            {
                if(IsConnected())
                {
                    m_connection->Disconnect();
                }
                
                m_context.stop();
                if(thrContext.joinable())
                {
                    thrContext.join();
                }

                m_connection.release();
            }

            bool IsConnected()
            {
                if(m_connection)
                {
                    return m_connection->IsConnected();
                }
                else return false;
            }

            tsqueue<owned_message<T>>& Incoming()
            {
                return m_qMessagesIn;
            }
            
        protected:
            asio::io_context m_context;

            std::thread thrContext;

            asio::ip::tcp::socket m_socket;

            std::unique_ptr<connection<T>> m_connection;
        private:
            tsqueue<owned_message<T>> m_qMessagesIn;
        };
    }
    
}