#include <memory>

#include <gtest/gtest.h>

#include "../../common/player_command_types.h"
#include "../../common/queue.h"
#include "../../server/protocol/client_action.h"

TEST(PointerQueueTest, QueueWithClientActionDontHaveLeaks) {
    // Arrange
    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>> queue =
            std::make_shared<Queue<std::unique_ptr<ClientAction>>>(3);

    std::unique_ptr<ServerSpace::Move> move1 =
            std::make_unique<ServerSpace::Move>(1, MoveType::DOWN);
    std::unique_ptr<ServerSpace::Move> move2 =
            std::make_unique<ServerSpace::Move>(1, MoveType::DOWN);
    queue->push(std::move(move1));
    queue->push(std::move(move2));

    // Act & Assert
    ASSERT_FALSE(queue->empty());
    std::unique_ptr<ClientAction> action;
    while (queue->try_pop(action)) {}
    ASSERT_NE(action, nullptr);
    ASSERT_TRUE(queue->empty());
}

TEST(QueueTest, QueueWithGameImageDontHaveLeaks) {
    // Arrange
    std::shared_ptr<Queue<GameImage>> queue = std::make_shared<Queue<GameImage>>(3);

    GameImage img1;
    GameImage img2;

    queue->push(img1);
    queue->push(img2);

    // Act & Assert
    queue->close();
    ASSERT_FALSE(queue->empty());
    GameImage out;
    ASSERT_TRUE(queue->try_pop(out));
    ASSERT_TRUE(queue->try_pop(out));
    ASSERT_THROW(queue->try_pop(out), ClosedQueue);
    ASSERT_TRUE(queue->empty());
}

TEST(QueueTest, QueueWithGameImageDontHaveLeaksIfIDontPopElements) {
    // Arrange
    std::shared_ptr<Queue<GameImage>> queue = std::make_shared<Queue<GameImage>>(3);

    GameImage img1;
    GameImage img2;

    queue->push(img1);
    queue->push(img2);

    // Act & Assert
    queue->close();
    ASSERT_FALSE(queue->empty());
}
