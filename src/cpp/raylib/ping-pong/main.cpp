#include "raylib.h"
#include <iostream>
#include <string>

struct Ball {
	float posX;
	float posY;
	float radius;
	Color color;
	float speedX{ 200 };
	float speedY{ 200 };


	void reset() {
		posX = GetScreenWidth() / 2;
		posY = GetScreenHeight() / 2;
		speedX = 200;
		speedY = 200;
	}

	void update() {
		posX += speedX * GetFrameTime();
		posY += speedY * GetFrameTime();

		if (posY < 0) {
			posY = 0;
			speedY *= -1;
		}

		if (posY > GetScreenHeight()) {
			posY = GetScreenHeight();
			speedY *= -1;
		}

		//if (posX < 0) {
		//	posX = 0;
		//	speedX *= -1;
		//}

		//if (posX > GetScreenWidth()) {
		//	posX = GetScreenWidth();
		//	speedX *= -1;
		//}
	}

	void show() {
		DrawCircle(posX, posY, radius, color);
	}
};

struct Paddle {
	float posX;
	float posY;
	float width;
	float height;
	Color color;
	float speed {500};
	
	void reset() {

	}
	void moveUp() {
		posY -= speed * GetFrameTime();
		if (top() < 0) {
			posY = height/2;
		}
	}

	void moveDown() {
		posY += speed * GetFrameTime();
		if (bottom() > GetScreenHeight()) {
			posY = GetScreenHeight() - height / 2;
		}
	}

	float top() {
		return posY - height / 2;
	}

	float bottom() {
		return posY + height / 2;
	}

	Rectangle getRect() const {
		return Rectangle{ posX - width / 2, posY - height / 2, 10, 100 };
	}

	void show() {
		//DrawRectangle(posX - width/2, posY - height/2, width, height, color);
		DrawRectangleRec(getRect(), color);
	}
};

int main() {
	InitWindow(800, 600, "Ping-Pong");
	SetWindowState(FLAG_VSYNC_HINT);
	std::string winner{};
	bool isGameOver{ };
	bool showMsg{ false };

	Ball ball{ GetScreenWidth() / 2, GetScreenHeight() / 2, 5, WHITE};
	Paddle leftPaddle{50, GetScreenHeight() / 2, 10, 100, WHITE};
	Paddle rightPaddle{ GetScreenWidth() - 50, GetScreenHeight() / 2, 10, 100, WHITE};


	while (!WindowShouldClose()) {

		if (ball.posX < 0) {
			winner = "Right Player Wins!";
			isGameOver = true;
			showMsg = true;
		}

		if (ball.posX > GetScreenWidth()) {
			winner = "Left Player Wins!";
			isGameOver = true;
			showMsg = true;
		}

		BeginDrawing();

		ClearBackground(BLACK);
		ball.update();
		ball.show();

		if (IsKeyDown(KEY_W)) {
			leftPaddle.moveUp();
		}

		if (IsKeyDown(KEY_S)) {
			leftPaddle.moveDown();
		}

		if (IsKeyDown(KEY_UP)) {
			rightPaddle.moveUp();
		}

		if (IsKeyDown(KEY_DOWN)) {
			rightPaddle.moveDown();
		}

		leftPaddle.show();
		rightPaddle.show();

		if (CheckCollisionCircleRec(Vector2{ ball.posX, ball.posY }, ball.radius, rightPaddle.getRect())) {
			if (ball.speedX > 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.posY - rightPaddle.posY) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.posX, ball.posY }, ball.radius, leftPaddle.getRect())) {
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.posY - leftPaddle.posY) / (leftPaddle.height / 2) * ball.speedX;
			}
		}

		//if (!winner.empty()) {
		if (isGameOver) {
			if (showMsg) {
				int textWidth = MeasureText(winner.c_str(), 60);
				DrawText(winner.c_str(), GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}
			WaitTime(1.0);
			showMsg = !showMsg;
			
		}

		if (!winner.empty() && IsKeyPressed(KEY_SPACE)) {
			ball.reset();
			winner.clear();
			isGameOver = false;
			showMsg = false;
		}

		DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();
}