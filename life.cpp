/***************************************************************************
 *   Copyright (C) 2008 by or   *
 *   or@or-desktop   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <stdlib.h>
#include "board.h"
#include "SDL.h"
#define CELLSIZE 10
using namespace std;

void putpixel(SDL_Surface *surface,int x, int y,unsigned int color)
{
	unsigned int *ptr = (unsigned int*)surface->pixels;
	int lineoffset = y * (surface->pitch / 4);
	ptr[lineoffset + x] = color;
}
void drawcell(SDL_Surface *surface,unsigned int x,unsigned int y,unsigned int color)
{
	for(int i=0;i<CELLSIZE;i++)
	{
		for(int j=0;j<CELLSIZE;j++)
		{
			putpixel(surface,x*CELLSIZE+i,y*CELLSIZE+j,color);
		}
	}
}
void makecell(SDL_Surface *surface,unsigned int x,unsigned int y,bool full)
{
	if(full)
		drawcell(surface, x, y,2515);
	else
		drawcell(surface, x, y,0);
}

void drawboard(SDL_Surface *surface,board * brd)
{
	for (int i=0;i<brd->getx();i++)
		for (int j=0;j<brd->gety();j++)
			makecell(surface,i,j,brd->getcell(i,j));
}

int main(int argc, char *argv[])
{
	cout <<"Initializing SDL." << endl;
	/* Initializes Audio and the CDROM, add SDL_INIT_VIDEO for Video */
	if(SDL_Init(0)< 0)
	{
		cout <<"Could not initialize SDL:" << SDL_GetError() << endl;
		SDL_Quit();
	}

	SDL_Surface *screen;
	int bw=30,bh=30;
	screen = SDL_SetVideoMode(bw*CELLSIZE, bh*CELLSIZE, 32, SDL_SWSURFACE);
	board *life_board=new board(bw,bh,true);
	drawboard(screen,life_board);
	SDL_Event event;
	int ccx,ccy;
	bool play=false;
	while (1)
	{
		SDL_Delay(32);
		if (play)
		{
			life_board->generation();
			drawboard(screen,life_board);
			SDL_UpdateRect(screen, 0, 0, screen->w,screen->h);
		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_SPACE:
							life_board->generation();
							drawboard(screen,life_board);
							SDL_UpdateRect(screen, 0, 0, screen->w,screen->h);
							break;
						case SDLK_RETURN:
							play=!play;
							break;
						case SDLK_ESCAPE:
							SDL_Quit();
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					ccx=event.button.x/CELLSIZE;
					ccy=event.button.y/CELLSIZE;
					life_board->makeinvert(ccx,ccy);
					makecell(screen,ccx,ccy,life_board->getcell(ccx,ccy));
					SDL_UpdateRect(screen, 0, 0, screen->w,screen->h);
					break;
				case SDL_QUIT:
					return(0);
			}
		}
	}
}
