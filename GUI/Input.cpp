#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		
		if ( y >= 0 && y < UI.ToolBarHeight && x <= 15 * UI.MenuItemWidth)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_LINE: return DRAW_LINE;
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_TRI :return DRAW_TRI;
			case ITM_SEL :return SELECT;
			case ITM_DRAW_CLR:return CHNG_DRAW_CLR;
			case ITM_FILL_CLR:return CHNG_FILL_CLR;
			case ITM_DEL:return DEL;
			case ITM_ROTATE:return ROTATE;
			case ITM_COPY :return COPY;
			case ITM_CUT :return CUT;
			case ITM_PASTE :return PASTE;
			case ITM_SAVE:return SAVE;
			case ITM_LOAD:return LOAD;
			case ITM_PLAY:return TO_PLAY;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}
		if (y >= 0 && y < UI.ToolBarHeight && x > 15 * UI.MenuItemWidth && x < 16 * UI.MenuItemWidth)
		{
			if (y < UI.ToolBarHeight / 2)
				return RESIZE_BIG;
			return RESIZE_SMALL;
		}
		if ( y >= 0 && y < UI.ToolBarHeight && x > 16 * UI.MenuItemWidth && x < 35 * UI.MenuItemWidth / 2)
		{
			x -= 16 * UI.MenuItemWidth;
			if ( y < UI.ToolBarHeight / 2)
			{
				if (x < UI.MenuItemWidth / 2)
					return DRAW_RED;
				if (x < UI.MenuItemWidth)
					return DRAW_GREEN;
				if (x < UI.MenuItemWidth * 3 / 2)
					return DRAW_BLUE;
			}
			if (x < UI.MenuItemWidth / 2)
					return DRAW_BLACK;
			if (x < UI.MenuItemWidth)
					return DRAW_WHITE;
			return DRAW_GREY;
		}
		if (y >= 0 && y < UI.ToolBarHeight && x >= 35 * UI.MenuItemWidth / 2 && x < 37 * UI.MenuItemWidth / 2 )
			return EXIT;
		
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	if(UI.InterfaceMode == MODE_PLAY)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				case ITM_PICKBYTPYE:return PICKTYPE;
				case ITM_PICKBYCOLOR:return PICKCOLOR;
				case ITM_PICKBYTYPEANDCOLOR:return PICKTYPECOLOR;
				case ITM_DRAW:return TO_DRAW;
				case ITM_EXIT2:return EXIT;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}

}
/////////////////////////////////
	
Input::~Input()
{
}
ActionType Input::GetUserAction2(int x,int y)
{
	if(UI.InterfaceMode == MODE_PLAY)
	{
					//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				case ITM_PICKBYTPYE:return PICKTYPE;
				case ITM_PICKBYCOLOR:return PICKCOLOR;
				case ITM_PICKBYTYPEANDCOLOR:return PICKTYPECOLOR;
				case ITM_DRAW:return TO_DRAW;
				case ITM_EXIT2:return EXIT;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
}
