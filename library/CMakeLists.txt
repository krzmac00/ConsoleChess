cmake_minimum_required(VERSION 3.4)
project(library)

set(SOURCE_FILES
        src/Piece.cpp
        src/Game.cpp
        src/Player.cpp
        src/Players/ComputerPlayer.cpp
        src/Players/HumanPlayer.cpp
        src/Board.cpp
        src/Square.cpp
        src/View/ConsoleView.cpp
        src/Pieces/Bishop.cpp
        src/Pieces/Queen.cpp
        src/Pieces/Knight.cpp
        src/Pieces/King.cpp
        src/Pieces/Pawn.cpp
        src/Pieces/Rook.cpp
        src/Exceptions/InputException.cpp
        src/PiecesCreator.cpp
        src/Move.cpp
        src/Check.cpp
        src/View.cpp
        )

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/EnumTest.cpp
        test/Players/ComputerPlayerTest.cpp
        test/Players/HumanPlayerTest.cpp
        test/PiecesCreatorTest.cpp
        test/Pieces/PawnTest.cpp
        test/Pieces/BishopTest.cpp
        test/Pieces/KnightTest.cpp
        test/Pieces/RookTest.cpp
        test/Pieces/KingTest.cpp
        test/Pieces/QueenTest.cpp
        test/MoveTest.cpp
        test/BoardTest.cpp
        test/SquareTest.cpp
        test/CheckTest.cpp
        test/GameTest.cpp
        test/View/TestView.cpp
        test/Game/GameForTesting.cpp
        test/bugTest.cpp
        )

add_executable (LibraryTest ${SOURCE_TEST_FILES})

target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})