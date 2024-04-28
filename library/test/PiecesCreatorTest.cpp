#include <boost/test/unit_test.hpp>
#include "PiecesCreator.h"
#include "Piece.h"
#include "Players/HumanPlayer.h"
#include "Square.h"


struct TestSuitePiecesCreatorFixture {
    PlayerPtr player;
    SquarePtr square;
    PiecePtr piece;

    TestSuitePiecesCreatorFixture() {
        player = std::make_shared<HumanPlayer>("Player", WHITE);
        square = std::make_shared<Square>(0, 0);
    }

    ~TestSuitePiecesCreatorFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePiecesCreator, TestSuitePiecesCreatorFixture)

    BOOST_AUTO_TEST_CASE(BishopTest) {
        piece = PiecesCreator::create(PieceType::Bishop, player, square);
        BOOST_REQUIRE_EQUAL(piece->getType(), PieceType::Bishop);
        BOOST_REQUIRE_EQUAL(piece->getPlayer(), player);
        BOOST_REQUIRE_EQUAL(piece->getSquare(), square);
    }

    BOOST_AUTO_TEST_CASE(QueenTest) {
        piece = PiecesCreator::create(PieceType::Queen, player, square);
        BOOST_REQUIRE_EQUAL(piece->getType(), PieceType::Queen);
        BOOST_REQUIRE_EQUAL(piece->getPlayer(), player);
        BOOST_REQUIRE_EQUAL(piece->getSquare(), square);
    }

    BOOST_AUTO_TEST_CASE(KingTest) {
        piece = PiecesCreator::create(PieceType::King, player, square);
        BOOST_REQUIRE_EQUAL(piece->getType(), PieceType::King);
        BOOST_REQUIRE_EQUAL(piece->getPlayer(), player);
        BOOST_REQUIRE_EQUAL(piece->getSquare(), square);
    }

    BOOST_AUTO_TEST_CASE(PawnTest) {
        piece = PiecesCreator::create(PieceType::Pawn, player, square);
        BOOST_REQUIRE_EQUAL(piece->getType(), PieceType::Pawn);
        BOOST_REQUIRE_EQUAL(piece->getPlayer(), player);
        BOOST_REQUIRE_EQUAL(piece->getSquare(), square);
    }

    BOOST_AUTO_TEST_CASE(KnightTest) {
        piece = PiecesCreator::create(PieceType::Knight, player, square);
        BOOST_REQUIRE_EQUAL(piece->getType(), PieceType::Knight);
        BOOST_REQUIRE_EQUAL(piece->getPlayer(), player);
        BOOST_REQUIRE_EQUAL(piece->getSquare(), square);
    }

    BOOST_AUTO_TEST_CASE(RookTest) {
        piece = PiecesCreator::create(PieceType::Rook, player, square);
        BOOST_REQUIRE_EQUAL(piece->getType(), PieceType::Rook);
        BOOST_REQUIRE_EQUAL(piece->getPlayer(), player);
        BOOST_REQUIRE_EQUAL(piece->getSquare(), square);
    }

BOOST_AUTO_TEST_SUITE_END()
