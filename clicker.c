#include "raylib.h" /* game code */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* defines */
#define MAX_HEARTS 50000

/* structs, typdefs, and enums */
struct Clicker {
	int lineNumber;
	int numClicks;
//	char lineContent[300];
};

typedef struct Heart {
	Vector2 position;
	Vector2 speed;
} Heart;

/* global vars */
char lineContent[344];

/* proto types */
void RemNewLine(char *str);
char* ImgParser(int lineNumber);

/* Remove trailing newlines to avoid borkages */
void RemNewLine(char *str) {
  if (str == NULL)
    return;
  int length = strlen(str);
  if (str[length-1] == '\n')
    str[length-1]  = '\0';
}

/* Parse the txt file to get file path of specfic line */
char*
ImgParser(int lineNumber)
{
	static const char filename[] = "images.txt";
	FILE *file = fopen(filename, "r");
	int count = 0;
	if(file != NULL) {
		char line[256]; /* or other suitable maximum line size */
		while (fgets(line, sizeof line, file) != NULL) {
			if (count == lineNumber){
				printf("LineContents: %s\n", line);
				memcpy(lineContent, line, sizeof(line));
				return NULL;
			} else {
				count++;
			}
		}
		fclose(file);
	} else {
		printf("Image Not Found\n");
	}

	printf("Program returned unexpectantly\n");
	return NULL;
}

/* Main driver */
int
main()
{
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "clicker!");

	/* Set up clicker struct */
	struct Clicker s_clicker;
	s_clicker.lineNumber = 0;
	s_clicker.numClicks = 0;

	/* gotonext */
	Texture2D gotonext = LoadTexture("gamedata/gotonext.png");
	Rectangle srcRectan = { 0, 0, (float)gotonext.width, (float)gotonext.height };
	Rectangle gtnBounds = { screenWidth/2.0f - gotonext.width/2.0f - 200, screenHeight/2.0f - gotonext.height/2.0f - 200, (float)gotonext.width, (float)gotonext.height };
	int gotoNextCnt = 1;


	/* Set up hearts */
	Image heartImg = LoadImage("gamedata/heart.png");
	ImageResize(&heartImg, 20, 20);
	Texture2D texHeart = LoadTextureFromImage(heartImg);
	Heart *heart = (Heart *)malloc(MAX_HEARTS*sizeof(Heart));
	UnloadImage(heartImg);
	int heartCount = 0;

	/* parse image */
	ImgParser(s_clicker.lineNumber);
	RemNewLine(lineContent);

	/* define clicker obj */
	Image clickerImg = LoadImage(lineContent);
	ImageResize(&clickerImg, 50, 50);
        Texture2D clicker = LoadTextureFromImage(clickerImg); // Load button texture  
	UnloadImage(clickerImg);
	float frameHeight = (float)clicker.height;
	Rectangle sourceRec = { 0, 0, (float)clicker.width, frameHeight };
	Rectangle btnBounds = { screenWidth/2.0f - clicker.width/2.0f, screenHeight/2.0f - clicker.height/2.0f, (float)clicker.width, frameHeight };

	/* define mouse object */
	Vector2 mousePoint = { 0.0f, 0.0f };
	int btnState = 0;

	SetTargetFPS(60);

	while(!WindowShouldClose()){

		mousePoint = GetMousePosition();

		/* Set up Mouse click action */
		if(CheckCollisionPointRec(mousePoint, gtnBounds)){
			if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
				s_clicker.lineNumber++; /* inc lineNumber */
				ImgParser(s_clicker.lineNumber); /* grab new line contents */
				RemNewLine(lineContent);
				UnloadTexture(clicker); /* Unload texture for reloading */
				Image clickerImg = LoadImage(lineContent);
				ImageResize(&clickerImg, 50, 50);
        			clicker = LoadTextureFromImage(clickerImg); // Load button texture  
				UnloadImage(clickerImg);
				gotoNextCnt++;
			}
		}
				
		if(CheckCollisionPointRec(mousePoint, btnBounds)){
			if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
				for(int i = 0; i < 1; i++){
					if(heartCount < MAX_HEARTS){
						heart[heartCount].position = GetMousePosition();
						heart[heartCount].speed.x = 0.0f; /* TODO: Add wobble */
						heart[heartCount].speed.y = (float)GetRandomValue(-250, -500)/60.0f;
						heartCount++;
					}
				}
			}
		}

		/* Update hearts */
		for(int i = 0; i < heartCount; i++){
			heart[i].position.x += (float)GetRandomValue(-1000, 1000)/600.0f;
			heart[i].position.y += heart[i].speed.y;

		}

		
		BeginDrawing();

			ClearBackground(RAYWHITE);

			for(int i = 0; i < heartCount; i++){
				DrawTexture(texHeart, (int)heart[i].position.x, (int)heart[i].position.y, RAYWHITE);
			}

			DrawText(TextFormat("%i", s_clicker.numClicks), 400, 200, 20, LIGHTGRAY);
			DrawText(TextFormat("heart count: %i", heartCount), 400, 200, 20, LIGHTGRAY);
			DrawTextureRec(clicker, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
			DrawTextureRec(gotonext, srcRectan, (Vector2){ gtnBounds.x, gtnBounds.y }, WHITE);

		
		EndDrawing();
	}

	memcpy(lineContent, "", 1);

	UnloadTexture(clicker);
	UnloadTexture(texHeart);
	CloseWindow();

	return 0;
}
