#include <iostream>
#include <gtest/gtest.h>

#include "serializer.hpp"

class SerializerTests : public ::testing::Test
{
protected:
    struct Data1
    {
        uint64_t a;
        bool b;
        uint64_t c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b, c);
        }
    };
    struct Data2
    {
        uint64_t a;
        bool b;
        uint64_t c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b, c);
        }
    };
    struct Data3
    {
        uint64_t a;
        bool b;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b);
        }
    };
    struct Data4
    {
        uint64_t a;
        bool b;
        bool c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b, c);
        }
    };
    struct Data5
    {
        uint64_t a;
        bool b;
        double c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b, c);
        }
    };
    void SetUp()
    {
        data1 = {100, true, 200};
        data2 = {300, false, 400};
        data3 = {500, true};
        data4 = {600, true, false};

    }
    void TearDown()
    {
    }
    Data1 data1;
    Data2 data2;
    Data3 data3;
    Data4 data4;
};

TEST_F(SerializerTests, Serialize) {
    std::stringstream stream;
    Serializer serializer(stream);

    Error err = serializer.save(data2);
    EXPECT_EQ(err, Error::NoError);
    EXPECT_EQ(stream.str(), "300 false 400 ");
}

TEST_F(SerializerTests, Deserialize) {
    std::stringstream stream;
    stream.str("100 true 200 ");

    Data1 outputData = {0, false, 0};
    Deserializer deserializer(stream);

    Error err = deserializer.load(outputData);
    EXPECT_EQ(err, Error::NoError);
    EXPECT_EQ(outputData.a, 100);
    EXPECT_EQ(outputData.b, true);
    EXPECT_EQ(outputData.c, 200);
}

TEST_F(SerializerTests, SerializeData1ToData1) {
    std::stringstream stream;

    Serializer serializer(stream);
    auto err = serializer.save(data1);
    EXPECT_EQ(err, Error::NoError);

    Data1 y { 0, false, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(y);
    EXPECT_EQ(err, Error::NoError);

    EXPECT_EQ(data1.a, y.a);
    EXPECT_EQ(data1.b, y.b);
    EXPECT_EQ(data1.c, y.c);

}



TEST_F(SerializerTests, SerializeData1toData2) {
    std::stringstream stream;
    Data1 x {100, true, 200};
    Serializer serializer(stream);
    auto err = serializer.save(x);
    EXPECT_EQ(err, Error::NoError);

    Data2 y { 0, false, 0 };
    x = {1, false, 2};
    Deserializer deserializer(stream);
    err = deserializer.load(y);
    EXPECT_EQ(err, Error::NoError);

    EXPECT_EQ(100, y.a);
    EXPECT_EQ(true, y.b);
    EXPECT_EQ(200, y.c);
}

TEST_F(SerializerTests, SerializeData1ToData3) {
    std::stringstream stream;

    Serializer serializer(stream);
    auto err = serializer.save(data1);
    EXPECT_EQ(err, Error::NoError);

    Data3 y { 0, false };

    Deserializer deserializer(stream);
    err = deserializer.load(y);
    EXPECT_EQ(err, Error::NoError);

    EXPECT_EQ(data1.a, y.a);
    EXPECT_EQ(data1.b, y.b);

}

TEST_F(SerializerTests, DeserializeCorruptedArchive) {
    std::stringstream stream;

    Serializer serializer(stream);
    auto err = serializer.save(data1);
    EXPECT_EQ(err, Error::NoError);

    Data4 y { 0, false, false };

    Deserializer deserializer(stream);
    err = deserializer.load(y);
    EXPECT_EQ(err, Error::CorruptedArchive);

}

TEST_F(SerializerTests, DeserializeInvalidType) {
    std::stringstream stream;

    Serializer serializer(stream);
    auto err = serializer.save(data1);
    EXPECT_EQ(err, Error::NoError);

    Data5 y { 0, false, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(y);
    EXPECT_EQ(err, Error::InvalidType);

}

TEST_F(SerializerTests, SerializeInvalidType) {
    std::stringstream stream;

    Serializer serializer(stream);
    Data5 x { 0, false, 0 };
    auto err = serializer.save(x);
    EXPECT_EQ(err, Error::InvalidType);
}

TEST_F(SerializerTests, DeserializeTypeMismatch) {
    std::stringstream stream;

    Serializer serializer(stream);
    auto err = serializer.save(data3);
    EXPECT_EQ(err, Error::NoError);

    Data1 y { 0, false, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(y);
    EXPECT_EQ(err, Error::TypeMismatch);

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
