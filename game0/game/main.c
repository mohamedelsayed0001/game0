#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "cont.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font ;
SDL_Surface* text = NULL;
SDL_Surface* surface_1 = NULL;
SDL_Texture* texture_1 = NULL; 




struct ball {
	float x, y, wigth, length;
}ball;
struct player_1 {
	float x, y, wigth, length;
}player_1;
struct player_2 {
	float x, y, wigth, length;
}player_2;

int motion_1(void)
{
	ball.x += 120 * del_time;
	ball.y -= 155 * del_time;
	return 1;
}
int motion_2(void)
{
	ball.x += 130 * del_time;
	ball.y += 110 * del_time;
	return 2;
}
int motion_3(void)
{
	ball.x -= 100 * del_time;
	ball.y -= 120 * del_time;
	return 3;
} 
int motion_4(void)
{
	ball.x -= 130 * del_time;
	ball.y += 150 * del_time;
	return 4;
}


int open_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr,"samething went wrong!");
		return false;
	}
	if (TTF_Init() != 0 )
	{
		fprintf(stderr, "samething went worng!in ttf"); 
		return false; 
	}
	window = SDL_CreateWindow(
		"game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_LENGHT,
		SDL_WINDOW_BORDERLESS
		);

	if(!window)
	{
		fprintf(stderr, "error");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "error");
		return false;
	}

	SDL_Surface* surface_1 = SDL_GetWindowSurface(window); 

	return true;

}
 
void input(void)
{
	SDL_Event event; 
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		test = false;
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			test = false;
			
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			down_1 = true;
			up_1 = false;

		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			down_1 = false;
			up_1 = true; 
		}
		else if (event.key.keysym.sym == SDLK_w )
		{

			up_2 = true;
			down_2 = false; 
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			down_2 = true; 
			up_2 = false;  
		}
		break;
	}
}

void setup() {
	start_the_ball = true;
	ball.x = 400;
	ball.y = 400;
	ball.wigth = 20;
	ball.length = 20;

	player_1.x = 10;
	player_1.y = 400;
	player_1.wigth = 10;
	player_1.length = 90;

	player_2.x = 800-20;
	player_2.y = 400;
	player_2.wigth = 10;
	player_2.length = 90;

	 down_1 = false; 
	 down_2 = false; 
	 up_1 = false; 
	 up_2 = false; 
	
 }





void update(void)
{
	
	del_time = (SDL_GetTicks() - last_frame) / 1000.0f;
	last_frame = SDL_GetTicks();
	if (start_the_ball)
	{
		last_move = motion_4(); 
	}
	if (restart_the_ball)
	{
		if (last_move == 1) { last_move = motion_1(); }
		else if (last_move == 2) { last_move = motion_2(); }
		else if (last_move == 3) { last_move = motion_3(); }
		else if (last_move == 4) { last_move = motion_4(); }
	}
	if (ball.y <= 5.0f)
	{ 
		start_the_ball = false;
		restart_the_ball = false;
		if (last_move == 1)
		{
			last_move = motion_2();
		}
		else if (last_move == 3)
		{
			last_move = motion_4();
		}
		else if (last_move == 2) { last_move = motion_2(); }
		else if (last_move == 4) { last_move = motion_4(); } 
	}
	
	else if (ball.y >= 770.0f)
	{
		
		start_the_ball = false;
		restart_the_ball = false;
		if (last_move == 2)
		{
			last_move = motion_1();
		}
		else if (last_move == 4)
		{
			last_move = motion_3();
		}
		else if (last_move == 1) { last_move = motion_1(); }
		else if (last_move == 3) { last_move = motion_3(); }
	}
	else if (ball.x <= (15.0f) && ball.x > 0.0f)
	{
		
		start_the_ball = false; 
		restart_the_ball = false;
		if (ball.y >= player_1.y && ball.y <= (player_1.y + 90.0f))
		{
			
			
			if (last_move == 3)
			{
				last_move = motion_1();
			}
			else if (last_move==4)
			{ 
				last_move = motion_2(); 
			}
			else if (last_move == 1)
			{
				last_move = motion_1();
			}
			else if (last_move == 2)
			{
				last_move = motion_2();
			}
			
		}
		else {
			start_the_ball = false;
			restart_the_ball = false;
			if (last_move == 3) { last_move = motion_3(); }
			else if (last_move == 4) { last_move = motion_4(); } 
		}
	}
	else if (ball.x >= (760.0f) && ball.x <800.0f)
	{
		
		start_the_ball = false; 
		restart_the_ball = false;
		if (ball.y >= player_2.y && ball.y <= (player_2.y + 90.0f))
		{

			
			if (last_move == 1)
			{
				last_move = motion_3();
			}
			else if (last_move == 2)
			{
				last_move = motion_4();
			}
			else if (last_move == 3)
			{
				last_move = motion_3();
			}
			else if (last_move == 4)
			{
				last_move = motion_4();
			}

		}
		else {
			start_the_ball = false;
			restart_the_ball = false;
			if (last_move == 1) { last_move = motion_1(); }
			else if (last_move == 2) { last_move = motion_2(); }
		}
	}
	else {
		if (last_move == 1){last_move = motion_1();}
		else if (last_move == 2) {last_move = motion_2();}
		else if (last_move == 3) {last_move = motion_3();}
		else if (last_move == 4) {last_move = motion_4();}

	}
	if (ball.x < 0 )
	{
		restart_the_ball = true;
		setup();
		start_the_ball = false;
		SDL_Delay(600);
		s_2++;
		
	}
	if (ball.x > 800)
	{
		restart_the_ball = true; 
		setup();
		start_the_ball = false; 
		SDL_Delay(600); 
		s_1++;
	}
	
	while (down_1)
	{
		if (player_1.y < 710.0f)
		{
			player_1.y += 230.0f * del_time; 
		}
		break;
	}
	while (up_1) {
		if (player_1.y > 0.0f) {
			player_1.y -= 230.0f * del_time;
		}
		break;
	}
	while (down_2)
	{
		if (player_2.y < 710.0f)
		{
			player_2.y += 230.0f * del_time;
		}
		break;
	}
	while (up_2)
	{
		if (player_2.y > 0.0f)
		{
			player_2.y -= 230.0f * del_time;
		}
		break;
	}
}
void renderer_1(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {
		ball.x,
		ball.y,
		ball.wigth,
		ball.length
	}; 
	SDL_Rect player_01 = { 
		player_1.x, 
		player_1.y, 
		player_1.wigth, 
		player_1.length 
	}; 
	SDL_Rect player_02 = { 
		player_2.x,
		player_2.y,
		player_2.wigth,
		player_2.length
	};
	font = TTF_OpenFont("Bebas-Regular.ttf ", 36); 
	SDL_Color white = { 255,255,255 };
	if (font == NULL) { printf("font is not found\n"); } 
	text = TTF_RenderText_Solid( font,"test is wwwwwww", white);
	

	
    texture_1 = SDL_CreateTextureFromSurface(renderer, text); 

	SDL_Rect s_1 = { 
		s_1.x=0,
		s_1.y=0,
		s_1.w=100,
		s_1.h=100
	};
	SDL_RenderCopy(renderer, text, NULL, &s_1); 

	SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
	SDL_RenderFillRect(renderer, &ball_rect);
	SDL_RenderFillRect(renderer, &player_01);
	SDL_RenderFillRect(renderer, &player_02);
	SDL_RenderPresent(renderer);
}

void destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture_1);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv [])
{
	 test= open_window();
	 setup();

	
	while (test)
	{
		input();
		update();
		renderer_1();
	}
	
	 destroy_window();

	 return 0;

	
}