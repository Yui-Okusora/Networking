#pragma once
#include "net_common.h"

namespace olc
{
    namespace net
    {
        template<typename T>
        struct message_header
        {
            T id{};
            uint32_t size=0;
        };

        template<typename T>
        struct message
        {
            message_header<T> header{};
            std::vector<uint8_t> body;

            size_t size() const
            {
                return body.size();
            }

            friend std::ostream& operator<<(std::ostream& out, const message<T>& msg)
            {
                out << " ID: " << int(msg.header.id) << " Size: " << msg.header.size;
                return out;
            }

            template<typename DataType>
            friend message<T>& operator<<(message<T>& msg, const DataType& data)
            {
                static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

                size_t i = msg.body.size();

                msg.body.resize(msg.body.size()+sizeof(DataType));

                std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

                msg.header.size = msg.size();

                return msg;
            }

            template<typename DataType>
            friend message<T>& operator>>(message<T>& msg, DataType& data)
            {
                static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled into vector");

                size_t i = msg.body.size() - sizeof(DataType);

                std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

                msg.body.resize(i);

                msg.header.size = msg.size();

                return msg;
            }
        };

        template<typename T>
        class connection;

        template<typename T>
        struct owned_message
        {
            std::shared_ptr<connection<T>> remote = nullptr;
            message<T> msg;

            friend std::ostream& operator<<(std::ostream& out, const owned_message<T>& msg)
            {
                out << msg.msg;
                return out;
            }
        };
    }
}