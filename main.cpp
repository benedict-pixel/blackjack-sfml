// === Game.h ===
#pragma once
#include <SFML/Graphics.hpp>
#include "Deck.h"
#include "Player.h"
#include "GUI.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void resetGame();
    void dealerTurn();

    sf::RenderWindow window;
    Deck deck;
    Player player;
    Player dealer;
    GUI gui;

    bool playerTurn;
    bool gameOver;
    std::string resultText;
};

// === Game.cpp ===
#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Blackjack") {
    resetGame();
}

void Game::resetGame() {
    deck = Deck();
    deck.shuffle();
    player.reset();
    dealer.reset();

    player.addCard(deck.dealCard());
    player.addCard(deck.dealCard());
    dealer.addCard(deck.dealCard());
    dealer.addCard(deck.dealCard());

    resultText = "";
    gameOver = false;
    playerTurn = true;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && playerTurn) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (gui.isHitButtonClicked(mousePos)) {
                player.addCard(deck.dealCard());
                if (player.getTotal() > 21) {
                    resultText = "Player Busts! Dealer Wins!";
                    gameOver = true;
                    playerTurn = false;
                }
            }
            else if (gui.isStandButtonClicked(mousePos)) {
                playerTurn = false;
                dealerTurn();
            }
        }

        if (event.type == sf::Event::KeyPressed && gameOver) {
            if (event.key.code == sf::Keyboard::R) {
                resetGame();
            }
        }
    }
}

void Game::dealerTurn() {
    while (dealer.getTotal() < 17) {
        dealer.addCard(deck.dealCard());
    }

    int pTotal = player.getTotal();
    int dTotal = dealer.getTotal();

    if (dTotal > 21 || pTotal > dTotal)
        resultText = "Player Wins!";
    else if (pTotal < dTotal)
        resultText = "Dealer Wins!";
    else
        resultText = "It's a Tie!";

    gameOver = true;
}

void Game::update() {
    // Game logic processed in processEvents()
}

void Game::render() {
    window.clear(sf::Color::Green);

    gui.drawText(window, "Player Total: " + std::to_string(player.getTotal()), 50, 10);
    gui.drawText(window, "Dealer Total: " + std::to_string(dealer.getTotal()), 50, 110);

    gui.drawHand(window, player, 50);
    gui.drawHand(window, dealer, 150);

    if (!gameOver && playerTurn)
        gui.drawButtons(window);
    else if (gameOver)
        gui.drawText(window, resultText + " (Press R to restart)", 50, 300, 24);

    window.display();
}
