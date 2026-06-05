cmake_minimum_required(VERSION 3.16)
project(cpp_portfolio_management_system VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

find_package(SQLite3 REQUIRED)

set(COMMON_SOURCES
    src/utils/Database.cpp
    src/utils/CsvWriter.cpp
    src/repositories/ClientRepository.cpp
    src/repositories/PortfolioRepository.cpp
    src/repositories/InstrumentRepository.cpp
    src/repositories/TransactionRepository.cpp
    src/repositories/HoldingRepository.cpp
    src/services/ClientService.cpp
    src/services/PortfolioService.cpp
    src/services/InstrumentService.cpp
    src/services/TradeService.cpp
    src/services/ReportService.cpp
)

add_executable(portfolio_app src/main.cpp ${COMMON_SOURCES})
target_link_libraries(portfolio_app PRIVATE SQLite::SQLite3)

add_executable(portfolio_tests tests/test_portfolio.cpp ${COMMON_SOURCES})
target_link_libraries(portfolio_tests PRIVATE SQLite::SQLite3)

enable_testing()
add_test(NAME PortfolioCoreTests COMMAND portfolio_tests)
