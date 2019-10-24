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
#ifndef BOARD_H_
#define BOARD_H_

class board
{
	private:
		bool tilable;
		bool *data;
		bool *databuf;
		unsigned int x,y;
	public:
		board(unsigned int x,unsigned int y, bool tileble);
		board(unsigned int x,unsigned int y);
		void cellset(unsigned int ux,unsigned int uy,bool value);
		bool cellget(unsigned int ux,unsigned int uy);
		int neighbors(unsigned int x,unsigned int y);
		unsigned int getx();
		unsigned int gety();
		void maketrue(unsigned int x,unsigned int y);
		void makefalse(unsigned int x,unsigned int y);
		void makeinvert(unsigned int x,unsigned int y);
		bool getcell(int x,int y);
		void generation();
		void clear();
		void print();
		~board();
	
};
#endif
