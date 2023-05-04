#include <gtest/gtest.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

namespace dbo = Wt::Dbo;

std::vector<unsigned char> read_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return std::vector<unsigned char>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

TEST(DatabaseTest, CreateTableTest) {
    // Connect to the test database
    dbo::Session session;
    std::unique_ptr<dbo::backend::Postgres> pg {new dbo::backend::Postgres("host=localhost port=5432 dbname=for_project_ARKITAIL user=antiho password=qwerty")};
    session.setConnection(std::move(pg));
    dbo::Transaction transaction{session};


    session.mapClass<events>("events");
    session->mapClass<TestClass>("test_table");

    session->createTables();

    std::vector<std::string> tables;
    session->storage().tableNames(tables);
    EXPECT_NE(std::find(tables.begin(), tables.end(), "test_table"), tables.end());

    session->dropTables();
}
