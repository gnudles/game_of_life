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
#include "board.h"
#include <iostream>
using namespace std;

board::board(unsigned int ux,unsigned int uy, bool utilable)
{
	x=ux;
	y=uy;
	tilable=utilable;
	data=new bool[x*y];
	databuf=new bool[x*y];
	clear();
}
void board::cellset(unsigned int ux,unsigned int uy,bool value)
{
	data[x*uy+ux]=value;
}
bool board::cellget(unsigned int ux,unsigned int uy)
{
	return data[x*uy+ux];
}
void board::clear()
{
	for (int i=0;i<x;i++)
		for (int j=0;j<y;j++)
			cellset(i,j,false);
}
board::board(unsigned int ux,unsigned int uy)
{
	board(ux,uy,true);
}
board::~board()
{
	delete data;
	delete databuf;
}
bool board::getcell(int ux,int uy)
{
	if (this->tilable)
	{
		while (ux<0)
			ux+=x;
		ux%=x;
		while (uy<0)
			uy+=y;
		uy%=y;
		return cellget(ux,uy);
	}
	else
	{
		if (uy>=y || ux>=x || uy<0 || ux<0)
			return false;
		else
			return cellget(ux,uy);
	}
}
int board::neighbors(unsigned int x,unsigned int y)
{
	int count=0;
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
			if (j!=0 || i!=0)
				if (getcell(x+i,y+j))
					count++;
	return count;
}
void board::print()
{
	for (int i=0;i<y;i++)
	{
		for(int j=0;j<x;j++)
			if (cellget(j,i))
				cout<<"O";
			else
				cout<<"_";
		cout<<endl;
	}
	cout<<"*******************"<<endl;
}
void board::generation()
{
	int cn;
	bool cb;
	bool *newdata=databuf;
	for(int i=0;i<this->x;i++)
		for(int j=0;j<this->y;j++)
		{
			cn=neighbors(i,j);
			if (cn==3)
				newdata[i+x*j]=true;
			else
			{
				cb=getcell(i,j);
				if( cb &&(cn>3 || cn<2))
					newdata[i+x*j]=false;
				else
					newdata[i+x*j]=cb;
			}
		}
	databuf=data;
	data=newdata;
}
void board::maketrue(unsigned int x,unsigned int y)
{
	cellset(x,y,true);
}
void board::makefalse(unsigned int x,unsigned int y)
{
	cellset(x,y,false);
}
void board::makeinvert(unsigned int x,unsigned int y)
{
	cellset(x,y,!cellget(x,y));
}
unsigned int board::getx()
{
	return this->x;
}
unsigned int board::gety()
{
	return this->y;
}
